#include "bme280.hpp"

bme280::bme280(i2c& i2c_bus, uint8_t slave_address) : i2c_bus(i2c_bus), slave_address(slave_address) {}