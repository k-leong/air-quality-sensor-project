#pragma once

#include <stdint.h>
#include "i2c_v2.hpp"

namespace ens160_registers {
  constexpr uint8_t part_id = 0x00;
  constexpr uint8_t op_mode = 0x10;
  constexpr uint8_t device_status = 0x20;
  constexpr uint8_t data_AQI = 0x21; // 1 byte register
  constexpr uint8_t data_TVOC = 0x22; // 2 byte register
  constexpr uint8_t data_ECO2 = 0x24; // 2 byte register
  constexpr uint8_t data_Temperature = 0x30; // 2 byte register
  constexpr uint8_t data_Humidity = 0x32; // 2 byte register
}

class ens160 {
  public:
    // Add any public members or methods if needed
    ens160(i2c& i2c_bus, uint8_t slave_address = 0x53);
    bool init();
    uint8_t get_aqi();
    uint16_t get_tvoc();
    uint16_t get_eco2();
    uint16_t get_temperature();
    uint16_t get_humidity();
    // bool get_air_quality(uint8_t& aqi, uint16_t& tvoc, uint16_t& eco2);
  private:
    // Add any private members or methods if needed
    i2c& i2c_bus;
    uint8_t slave_address;
    constexpr static uint8_t normal_mode = 0x02;
};