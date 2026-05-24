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

#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ms4525do.h"

#define I2C_PORT       I2C_NUM_0
#define SDA_PIN        21
#define SCL_PIN        22
#define I2C_FREQ_HZ    100000

void app_main(void)
{
    i2c_master_bus_config_t bus_config =
    {
        .i2c_port = I2C_PORT,
        .sda_io_num = SDA_PIN,
        .scl_io_num = SCL_PIN,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    i2c_master_bus_handle_t bus_handle;
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &bus_handle));

    ms4525_config sensor_cfg;
    setup_ms4525(&sensor_cfg, I2C_FREQ_HZ, -1.0f, 1.0f, OUTPUT_TYPE_B);

    i2c_master_dev_handle_t sensor;
    ESP_ERROR_CHECK(add_ms4525_device(bus_handle, &sensor_cfg, &sensor));
    
    ms4525_data data;
    ms4525_offset(&sensor_cfg,&data, 1000);

    while(1)
    {
        esp_err_t err = ms4525_read(&sensor_cfg, &data);

        if(err == ESP_OK)
        {
            printf(
                "P: %8.2f Pa, %8.8f Psi, %d Cnt| "
                "T: %6.2f C | "
                "V: %6.2f m/s, %6.2f km/h\n",
                data.pressure_pa,
                data.pressure_pa/6894.76f,
                data.pressure_raw,
                data.temp_c,
                data.speed_ms,
                data.speed_kmh);
        }
        else
        {
            printf("Read Failed\n");
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
