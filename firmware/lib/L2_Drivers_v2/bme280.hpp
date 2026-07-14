#pragma once

#include <stdint.h>
#include "i2c_v2.hpp"

namespace bme280_registers {
  constexpr uint8_t chip_id = 0xD0; // 1 byte register
  constexpr uint8_t reset = 0xE0; // 1 byte register
  constexpr uint8_t ctrl_hum = 0xF2; // 1 byte register
  constexpr uint8_t status = 0xF3; // 1 byte register
  constexpr uint8_t ctrl_meas = 0xF4; // 1 byte register
  constexpr uint8_t config = 0xF5; // 1 byte register
  constexpr uint8_t press_msb = 0xF7; // 1 byte register
  constexpr uint8_t press_lsb = 0xF8; // 1 byte register
  constexpr uint8_t press_xlsb = 0xF9; // 1 byte register
  constexpr uint8_t temp_msb = 0xFA; // 1 byte register
  constexpr uint8_t temp_lsb = 0xFB; // 1 byte register
  constexpr uint8_t temp_xlsb = 0xFC; // 1 byte register
  constexpr uint8_t hum_msb = 0xFD; // 1 byte register
  constexpr uint8_t hum_lsb = 0xFE; // 1 byte register
}

class bme280 {
  public:
    // Add any public members or methods if needed
    bme280(i2c& i2c_bus, uint8_t slave_address = 0x77);
  private:
    // Add any private members or methods if needed
    i2c& i2c_bus;
    uint8_t slave_address;
};