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
    bool read(uint8_t slave_addr);
    void write();
  private:
    bus port;
};