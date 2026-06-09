# MS4525DO Differential Pressure Sensor Driver

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Framework: ESP-IDF](https://img.shields.io/badge/Framework-ESP--IDF-red.svg)](https://docs.espressif.com/projects/esp-idf/en/latest/)
[![Interface: I2C](https://img.shields.io/badge/Interface-I2C-blue.svg)](#)
[![Language: C / C++](https://img.shields.io/badge/Language-C%20%2F%20C%2B%2B-green.svg)](#)

An ESP-IDF driver for the **TE Connectivity MS4525DO** digital differential pressure sensor. The driver reads pressure and temperature over I2C and calculates airspeed, making it well suited for Pitot-tube airspeed measurements on UAV and flight-control platforms such as those built around Pixhawk PX4.

The driver ships with a lightweight **C** API and an optional **C++** wrapper class for projects that prefer an object-oriented interface.

## Features

- **Pressure & temperature** acquisition over I2C.
- **Airspeed calculation** in m/s, km/h and knots from differential pressure.
- **Output Type A and Type B** transfer function support.
- **Offset calibration** via multi-sample averaging, or a manual override. The
  averaging step is intentionally simple and may be replaced with a stronger
  algorithm by future users.
- **Moving-average filtering** of the pressure signal for stable readings.
- **C and C++ APIs** — use the C core directly or the C++ wrapper class.

## Repository Structure

| Path                  | Description                                        |
| --------------------- | -------------------------------------------------- |
| `cpp_adapter/`        | C++ wrapper class (`MS4525DO`) around the C core.  |
| `example/example.c`   | Minimal usage example (C).                         |
| `example/example.cpp` | Minimal usage example (C++).                       |
| `docs/`               | Datasheet and manufacturer notes.                  |
| `CMakeLists.txt`      | ESP-IDF component registration.                    |
| `idf_component.yml`   | ESP-IDF Component Manager manifest.                |

## Requirements

- **ESP-IDF** v5.x or newer (uses the `driver/i2c_master.h` bus/device API).
- An MS4525DO sensor via I2C (default address `0x28`).

## Installation

Add the driver as a component to your ESP-IDF project, e.g. by cloning it into
your project's `components/` directory:

```bash
git clone https://github.com/Drivers-Development-Group/Airspeed-PixhawkPX4-SensorAPI.git components/ms4525do
```

The default `CMakeLists.txt` registers the C driver only. To additionally build
the C++ wrapper and/or examples, register the extra sources in your component
`CMakeLists.txt` (C++ case):

```cmake
idf_component_register(
    SRCS
        "src/ms4525do.c"
        "cpp_adapter/src/ms4525do.cpp"
    INCLUDE_DIRS
        "include"
        "cpp_adapter/include"
)
```

## Usage

Both APIs follow the same flow: create the I2C bus, configure the sensor,
attach it to the bus, calibrate the zero offset, and read sensor data.

### C

```c
#include "ms4525do.h"

ms4525_config sensor_cfg;
setup_ms4525(&sensor_cfg, 100000, -1.0f, 1.0f, OUTPUT_TYPE_B);

i2c_master_dev_handle_t sensor;
add_ms4525_device(bus_handle, &sensor_cfg, &sensor);

ms4525_data data = {0};
ms4525_offset(&sensor_cfg, &data, 1000U); /* zero calibration */

if (ms4525_read(&sensor_cfg, &data) == ESP_OK) {
    printf("P: %.2f Pa | T: %.2f C | V: %.2f m/s\n",
           data.pressure_pa, data.temp_c, data.speed_ms);
}
```

See [`example/example.c`](example/example.c) for a complete application.

### C++

```cpp
#include "ms4525do.hpp"

MS4525DO airspeedSensor;

ms4525_config sensor_cfg;
airspeedSensor.setup(&sensor_cfg, 100000, -1.0f, 1.0f, OUTPUT_TYPE_B);

i2c_master_dev_handle_t sensor;
airspeedSensor.add_device(bus_handle, &sensor_cfg, &sensor);

ms4525_data data = {0};
airspeedSensor.offset(&sensor_cfg, &data, 1000U);

if (airspeedSensor.read(&sensor_cfg, &data) == ESP_OK) {
    printf("P: %.2f Pa | T: %.2f C | V: %.2f m/s\n",
           data.pressure_pa, data.temp_c, data.speed_ms);
}
```

See [`example/example.cpp`](example/example.cpp) for a complete application.

## API Reference

| C function            | C++ method        | Description                                              |
| --------------------- | ----------------- | -------------------------------------------------------- |
| `setup_ms4525`        | `MS4525DO::setup` | Initialize the configuration structure.                  |
| `add_ms4525_device`   | `MS4525DO::add_device` | Attach the sensor to an existing I2C master bus.    |
| `ms4525_read`         | `MS4525DO::read`  | Read pressure, temperature and derived airspeed.         |
| `ms4525_offset`       | `MS4525DO::offset`| Compute the zero offset by averaging multiple samples.   |
| `ms4525_offset_add`   | `MS4525DO::offset_add` | Manually set the pressure offset (Pa).              |

The `ms4525_data` structure exposes raw counts, `pressure_pa`, `temp_c`, and
airspeed in `speed_ms`, `speed_kmh` and `speed_kt`. See
[`include/ms4525do.h`](include/ms4525do.h) for full parameter documentation.

## Documentation

The [`docs/`](docs/) directory contains the sensor datasheet and TE Connectivity
application notes on power consumption and digital interfacing.

## Authors

- Peter Šafranko &mdash; safranko.peter1@gmail.com
- Luciano Carricart &mdash; carricartluciano@gmail.com
- Juan Grondona &mdash; jgrondonacaimi@gmail.com

## License

Distributed under the MIT License. See [`LICENSE`](LICENSE) for details.