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

void setup_ms4524(ms4525_config *config, uint8_t i2c_address, uint8_t min_pressure, uint8_t max_pressure, OUTPUT_TYPE_MS4525 output_type){
    config->i2c_address = i2c_address;
    config->max_pressure = max_pressure;
    config->min_pressure = min_pressure;
    config->output_type = output_type;
}

float get_pressure_raw_ms4524(ms4525_config config){
    //TODO
    return 0;
}
float get_pressure_pa_ms4524(ms4525_config config){
    float per_a;
    float per_b;
    if(config.output_type == OUTPUT_TYPE_A){
        per_a = 0.8;
        per_b = 0.1;
    }
    else{
        per_a = 0.9;
        per_b = 0.05;
    }
    return (
        (get_pressure_raw_ms4524(config)-per_b*P_CNT) * 
        ((config.max_pressure-config.min_pressure)/(per_a * P_CNT)) + 
        config.min_pressure);
}

float get_temp_raw_ms4524(ms4525_config config){
    //TODO
    return 0;
}

float get_temp_c_ms4524(ms4525_config config){
    return(
        get_temp_raw_ms4524(config) * (T_MAX - T_MIN) /
        T_CNT - T_MIN
    );
}

float get_speed_ms_ms4524(ms4525_config config){
    return sqrt((2*get_pressure_pa_ms4524(config))/1.225);
}

float get_speed_kms_ms4524(ms4525_config config){
    return get_speed_ms_ms4524(config) * 3.6;
}

float get_speed_kt_ms4524(ms4525_config config){
    return get_speed_ms_ms4524(config) * 1.944;
}
