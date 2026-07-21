#include "bme280.hpp"

bme280::bme280(i2c& i2c_bus, uint8_t slave_address = 0x77) : i2c_bus(i2c_bus), slave_address(slave_address) {}

bool bme280::init() {
  // Implementation for initializing the BME280 sensor
  // This is a placeholder implementation and should be replaced with actual initialization code
  return true;
}

uint32_t bme280::read_temperature() {
  uint8_t temp_data[3];
  i2c_bus.transfer(slave_address, &bme280_registers::temp_msb, 1, temp_data, 3);
  return (static_cast<uint32_t>(temp_data[0]) << 12) |
          (static_cast<uint32_t>(temp_data[1]) << 4) |
          (static_cast<uint32_t>(temp_data[2]) >> 4);
}

uint32_t bme280::read_pressure() {
  uint8_t press_data[3];
  i2c_bus.transfer(slave_address, &bme280_registers::press_msb, 1, press_data, 3);
  return (static_cast<uint32_t>(press_data[0] << 12)) | 
          (static_cast<uint32_t>(press_data[1] << 4)) | 
          (static_cast<uint32_t>(press_data[2] >> 4));
}

uint16_t bme280::read_humidity() {
  uint8_t hum_data[2];
  i2c_bus.transfer(slave_address, &bme280_registers::hum_msb, 1, hum_data, 2);
  return (static_cast<uint16_t>(hum_data[0] << 8)) | 
          (static_cast<uint16_t>(hum_data[1]));
}