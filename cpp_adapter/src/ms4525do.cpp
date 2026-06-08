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
 * @file 	ms4525do.cpp
 * @brief	MS4525DO differential pressure sensor driver implementation.
 *
 * Created on June 2026
 * 		@author Peter Šafranko		safranko.peter1@gmail.com
 * 		@author Luciano Carricart	carricartluciano@gmail.com
 *		@author Juan Grondona		jgrondonacaimi@gmail.com
 */

/********************************************************************************
 * INCLUDES
 ********************************************************************************/
#include "ms4525do.hpp"

/********************************************************************************
 * CLASS METHODS
 ********************************************************************************/

/* See ms4525do.hpp for details */
void MS4525DO::setup(ms4525_config* config, uint32_t i2c_frequency, float min_pressure_psi, float max_pressure_psi, OUTPUT_TYPE_MS4525 output_type){
    setup_ms4525(config, i2c_frequency, min_pressure_psi, max_pressure_psi, output_type);
}

/* See ms4525do.hpp for details */
esp_err_t MS4525DO::add_device(i2c_master_bus_handle_t bus_handle, ms4525_config* config, i2c_master_dev_handle_t* sensor){
    return add_ms4525_device(bus_handle, config, sensor);
}

/* See ms4525do.hpp for details */
esp_err_t MS4525DO::read(ms4525_config* config, ms4525_data* out){
    return ms4525_read(config, out);
}

/* See ms4525do.hpp for details */
esp_err_t MS4525DO::offset(ms4525_config* config, ms4525_data* out, uint16_t offset_loop_amount){
    return ms4525_offset(config, out, offset_loop_amount);
}

/* See ms4525do.hpp for details */
void MS4525DO::offset_add(ms4525_data* data, float offset){
    return ms4525_offset_add(data, offset);
}