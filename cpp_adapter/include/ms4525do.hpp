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

 /**
 * @file 	ms4525do.hpp
 * @brief	MS4525DO differential pressure sensor public API
 *
 * Created on June 2026
 * 		@author Peter Šafranko		            safranko.peter1@gmail.com
 * 		@author Luciano Carricart	            carricartluciano@gmail.com
 *      @author Juan Valentin Grondona Caimi    jgrondonacaimi@gmail.com
 */


/********************************************************************************
 * INCLUDES
 ********************************************************************************/
#include "ms4525do.h"
/********************************************************************************
 * CLASSES
 ********************************************************************************/
class MS4525DO {
    public:
        /**
        * @brief Configure an MS4525DO driver instance.
        *
        * @param config Pointer to the driver configuration structure.
        * @param i2c_frequency I2C bus frequency in Hz.
        * @param min_pressure_psi Minimum sensor pressure range in PSI.
        * @param max_pressure_psi Maximum sensor pressure range in PSI.
        * @param output_type Sensor output transfer function type.
        */
        void setup(ms4525_config *config, uint32_t i2c_frequency, float min_pressure_psi, float max_pressure_psi, OUTPUT_TYPE_MS4525 output_type);

        /**
        * @brief Add the MS4525DO sensor to an existing I2C master bus.
        *
        * @param bus_handle I2C master bus handle.
        * @param config Pointer to the driver configuration structure.
        * @param sensor Pointer where the created I2C device handle is stored.
        *
        * @return ESP_OK on success, ESP_ERR_INVALID_ARG on invalid argument, or ESP-IDF I2C error code.
        */
        esp_err_t add_device(i2c_master_bus_handle_t bus_handle, ms4525_config *config, i2c_master_dev_handle_t *sensor);

        /**
        * @brief Read pressure, temperature, and calculated airspeed from the sensor.
        *
        * @param config Pointer to the driver configuration structure.
        * @param out Pointer to the output data structure.
        *
        * @return ESP_OK on success, ESP_ERR_INVALID_ARG on invalid argument, or ESP-IDF I2C error code.
        */
        esp_err_t read(ms4525_config *config, ms4525_data *out);

        /**
        * @brief Calculate and store the pressure offset using multiple sensor samples.
        *
        * @param config Pointer to the driver configuration structure.
        * @param out Pointer to the output data structure where the offset is stored.
        * @param offset_loop_amount Number of samples used for offset calculation.
        *
        * @return ESP_OK on success, ESP_ERR_INVALID_ARG on invalid argument, or ESP-IDF I2C error code.
        */
        esp_err_t offset(ms4525_config *config, ms4525_data *out, uint16_t offset_loop_amount);

        /**
        * @brief Manually set the pressure offset.
        *
        * @param data Pointer to the output data structure.
        * @param offset Offset value in Pa.
        */
        void offset_add(ms4525_data *data, float offset);
};

