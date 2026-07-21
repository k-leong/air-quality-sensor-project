#pragma once

#include <stdint.h>
#include "LPC17xx.h"

class i2c {
  public:
    enum struct bus {
      i2c1,
      i2c2
    };
    i2c(bus port);
    bool init(uint32_t clock_rate);
    bool read(uint8_t slave_addr, uint8_t* rx_data, uint32_t length);
    bool write(uint8_t slave_addr, const uint8_t* tx_data, uint32_t length);
    bool transfer(uint8_t slave_addr, const uint8_t* tx_data, uint32_t tx_length, uint8_t* rx_data, uint32_t rx_length);
  private:
    bus port;
    bool start();
    bool stop();
    bool send_byte();
    uint8_t receive_ack(bool ack);
    LPC_I2C_TypeDef* get_port();
};