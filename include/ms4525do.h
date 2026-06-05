/**
 * Copyright (c) 2026 Drivers Development Group
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef MS4525DO_H
#define MS4525DO_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file 	ms4525do.h
 * @brief	MS4525DO differential pressure sensor public API
 *
 * Created on May 2026
 * 		@author Peter Šafranko		safranko.peter1@gmail.com
 * 		@author Luciano Carricart	carricartluciano@gmail.com
 */

/********************************************************************************
 * INCLUDES
 ********************************************************************************/
#include <stdint.h>
#include "esp_err.h"
#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/********************************************************************************
 * DEFINITIONS
 ********************************************************************************/
#define I2C_ADDRESS_MS4525 0x28

#define P_CNT 16383.0f
#define T_CNT 2047.0f

#define T_MIN -50.0f
#define T_MAX 150.0f

/********************************************************************************
 * TYPEDEFS
 ********************************************************************************/
typedef enum{
    OUTPUT_TYPE_A,
    OUTPUT_TYPE_B
} OUTPUT_TYPE_MS4525;

typedef struct{
    i2c_device_config_t dev_cfg;
    i2c_master_dev_handle_t sensor;
    OUTPUT_TYPE_MS4525 output_type;
    float min_pressure;
    float max_pressure;
    float pressure_span;
    float output_min;
    float output_span;
} ms4525_config;

typedef struct{
    uint8_t raw[4];
    uint8_t status;
    uint16_t pressure_raw;
    uint16_t temp_raw;
    float pressure_pa;
    float temp_c;
    float speed_ms;
    float speed_kmh;
    float speed_kt;
    float offset;
} ms4525_data;

/********************************************************************************
 * PUBLIC FUNCTIONS
 ********************************************************************************/
void setup_ms4525(ms4525_config *config, uint32_t i2c_frequency, float min_pressure_psi, float max_pressure_psi, OUTPUT_TYPE_MS4525 output_type);

esp_err_t add_ms4525_device(i2c_master_bus_handle_t bus_handle, ms4525_config *config, i2c_master_dev_handle_t *sensor);

esp_err_t ms4525_read(ms4525_config *config, ms4525_data *out);

esp_err_t ms4525_offset_make(ms4525_config *config, ms4525_data *out, uint16_t offset_loop_amount);

void ms4525_offset_add(ms4525_data *data, float offset);

#ifdef __cplusplus
}
#endif
#endif /* MS4525DO_H */
