#include "ms4525do.hpp"

void MS4525DO::setup(ms4525_config* config, uint32_t i2c_frequency, float min_pressure_psi, float max_pressure_psi, OUTPUT_TYPE_MS4525 output_type){
    setup_ms4525(config, i2c_frequency, min_pressure_psi, max_pressure_psi, output_type);
}

esp_err_t MS4525DO::add_device(i2c_master_bus_handle_t bus_handle, ms4525_config* config, i2c_master_dev_handle_t* sensor){
    return add_ms4525_device(bus_handle, config, sensor);
}

esp_err_t MS4525DO::read(ms4525_config* config, ms4525_data* out){
    return ms4525_read(config, out);
}

esp_err_t MS4525DO::offset(ms4525_config* config, ms4525_data* out, uint16_t offset_loop_amount){
    return ms4525_offset(config, out, offset_loop_amount);
}

void MS4525DO::offset_add(ms4525_data* data, float offset){
    return ms4525_offset_add(data, offset);
}