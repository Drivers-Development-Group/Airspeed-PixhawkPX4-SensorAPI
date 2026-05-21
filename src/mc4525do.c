/*
Drivers Development Group
safranko.peter1@gmail.com

Copyright (c) 2026 Drivers Development Group

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "ms4525do.h"

#include <math.h>
#include <string.h>

#define PSI_TO_PA 6894.76f
#define AIR_DENSITY 1.225f

static esp_err_t ms4525_read_raw(
    ms4525_config *config,
    uint8_t data[4])
{
    return i2c_master_receive(
        config->sensor,
        data,
        4,
        -1);
}

void setup_ms4525(
    ms4525_config *config,
    uint32_t i2c_frequency,
    float min_pressure_psi,
    float max_pressure_psi,
    OUTPUT_TYPE_MS4525 output_type)
{
    memset(config, 0, sizeof(ms4525_config));

    config->dev_cfg.dev_addr_length =
        I2C_ADDR_BIT_LEN_7;

    config->dev_cfg.device_address =
        I2C_ADDRESS_MS4525;

    config->dev_cfg.scl_speed_hz =
        i2c_frequency;

    config->min_pressure =
        min_pressure_psi;

    config->max_pressure =
        max_pressure_psi;

    config->pressure_span =
        max_pressure_psi - min_pressure_psi;

    config->output_type =
        output_type;

    if(output_type == OUTPUT_TYPE_A)
    {
        config->output_min = 0.10f;
        config->output_span = 0.80f;
    }
    else
    {
        config->output_min = 0.05f;
        config->output_span = 0.90f;
    }
}

esp_err_t add_ms4525_device(
    i2c_master_bus_handle_t bus_handle,
    ms4525_config *config,
    i2c_master_dev_handle_t *sensor)
{
    esp_err_t err =
        i2c_master_bus_add_device(
            bus_handle,
            &config->dev_cfg,
            sensor);

    config->sensor = *sensor;

    return err;
}

esp_err_t ms4525_read(
    ms4525_config *config,
    ms4525_data *out)
{
    uint8_t data[4];

    esp_err_t err =
        ms4525_read_raw(config, data);

    if(err != ESP_OK)
    {
        return err;
    }

    memcpy(out->raw, data, 4);

    out->status =
        (data[0] >> 6) & 0x03;

    out->pressure_raw =
        ((uint16_t)(data[0] & 0x3F) << 8) |
        data[1];

    out->temp_raw =
        ((uint16_t)data[2] << 3) |
        ((data[3] >> 5) & 0x07);

    float pressure_psi =
    (
        (
            out->pressure_raw
            - (config->output_min * P_CNT)
        )
        *
        (
            config->pressure_span
            /
            (config->output_span * P_CNT)
        )
    )
    + config->min_pressure;

    out->pressure_pa =
        (pressure_psi * PSI_TO_PA);

    out->temp_c =
    (
        (float)out->temp_raw
        * (T_MAX - T_MIN)
        / T_CNT
    )
    + T_MIN;

    if(out->pressure_pa > 0.0f)
    {
        out->speed_ms =
            sqrtf(
                (2.0f * out->pressure_pa)
                / AIR_DENSITY);
    }
    else
    {
        out->speed_ms = 0.0f;
    }

    out->speed_kmh =
        out->speed_ms * 3.6f;

    out->speed_kt =
        out->speed_ms * 1.94384f;

    return ESP_OK;
}
