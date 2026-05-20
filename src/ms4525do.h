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

#ifndef MS4525_SENSOR_H
#define MS4525_SENSOR_H

#include <stdint.h>
#include "driver/i2c.h"

//Output types A and B, defaults to A
typedef enum{
    OUTPUT_TYPE_A,
    OUTPUT_TYPE_B
}OUTPUT_TYPE_MS4525;

//Configuration of ms4525
//@param i2c_address address of the connected i2c
//@param min_pressure minimum pressure of the sensor
//@param max_pressure maximum pressure of the sensor
//@param output_type output types A and B, defaults to A
typedef struct {
    uint8_t i2c_address;
    uint8_t min_pressure;
    uint8_t max_pressure;
    OUTPUT_TYPE_MS4525 output_type = OUTPUT_TYPE_A;
}ms4525_config;

//Sets up the port
//@return success in bool
bool setup_ms4524(ms4525_config *config);

//Checks the pressure with raw data
//@return pressure raw data in float
float get_pressure_raw_ms4524(ms4525_config config);

//Checks the pressure with pascals
//@return pressure pascal data in float
float get_pressure_pa_ms4524(ms4525_config config);

//Checks the temperature with raw data
//@return temperature raw data in float
float get_temp_raw_ms4524(ms4525_config config);

//Checks the temperature with celsius data
//@return temperature celsius data in float
float get_temp_c_ms4524(ms4525_config config);

//Calculates the speed in knots
//@return speed knots in float
float get_speed_kt_ms4524(ms4525_config config);

//Calculates the speed in km/h
//@return speed kilometers/h in float
float get_speed_km_ms4524(ms4525_config config);


#endif 