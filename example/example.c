/**
 * @file    example.c
 * @brief   Example application for the MS4525DO pressure sensor driver.
 */

#include <stdio.h>

#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "ms4525do.h"

#define I2C_PORT       		(I2C_NUM_0)
#define SDA_PIN        		(21)
#define SCL_PIN        		(22)
#define I2C_FREQ_HZ    		(100000)

#define APP_TASK_DELAY_MS	(50)

void app_main(void) {
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
    
    ms4525_data data = {0};
    ESP_ERROR_CHECK(ms4525_offset(&sensor_cfg, &data, 1000U));

    while(1) {
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
        } else {
            printf("Read Failed\n");
        }

        vTaskDelay(pdMS_TO_TICKS(APP_TASK_DELAY_MS));
    }
}
