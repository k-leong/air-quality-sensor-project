#include "ens160.hpp"

ens160::ens160(i2c& i2c_bus, uint8_t slave_address = 0x53) : i2c_bus(i2c_bus), slave_address(slave_address) {}

bool ens160::init() {
  // Implementation for initializing the ENS160 sensor
  // This is a placeholder implementation and should be replaced with actual initialization code
  return true;
}

uint8_t ens160::get_aqi() {
  uint8_t aqi = 0;
  // Implementation for reading the AQI value from the ENS160 sensor
  // This is a placeholder implementation and should be replaced with actual read code
  i2c_bus.transfer(slave_address, &ens160_registers::data_AQI, 1, &aqi, 1);
  return aqi;
}

uint16_t ens160::get_tvoc() {
  uint8_t tvoc[2];
  // Implementation for reading the TVOC value from the ENS160 sensor
  // This is a placeholder implementation and should be replaced with actual read code
  i2c_bus.transfer(slave_address, &ens160_registers::data_TVOC, 1, tvoc, 2);
  return static_cast<uint16_t>((tvoc[1] << 8) | tvoc[0]);
}

uint16_t ens160::get_eco2() {
  uint8_t eco2[2];
  // Implementation for reading the eCO2 value from the ENS160 sensor
  // This is a placeholder implementation and should be replaced with actual read code
  i2c_bus.transfer(slave_address, &ens160_registers::data_ECO2, 1, eco2, 2);
  return static_cast<uint16_t>((eco2[1] << 8) | eco2[0]);
}

uint16_t ens160::get_temperature() {
  uint8_t temperature[2];
  // Implementation for reading the temperature value from the ENS160 sensor
  // This is a placeholder implementation and should be replaced with actual read code
  i2c_bus.transfer(slave_address, &ens160_registers::data_Temperature, 1, temperature, 2);
  return static_cast<uint16_t>((temperature[1] << 8) | temperature[0]);
}

uint16_t ens160::get_humidity() {
  uint8_t humidity[2];
  // Implementation for reading the humidity value from the ENS160 sensor
  // This is a placeholder implementation and should be replaced with actual read code
  i2c_bus.transfer(slave_address, &ens160_registers::data_Humidity, 1, humidity, 2);
  return static_cast<uint16_t>((humidity[1] << 8) | humidity[0]);
}

