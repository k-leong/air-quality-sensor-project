#pragma once

#include <stdint.h>
#include "LPC17xx.h"

class gpio {
  public:
    enum struct Direction {
      input,
      output
    };
    // pins that are commpromised for LEDs and switches that are built in onto the board for LPC_GPIO1
    enum struct compromised_pins {
      led0 = 0,
      led1 = 1,
      led2 = 4,
      led3 = 8,
      switch0 = 9,
      switch1 = 10,
      switch2 = 14,
      switch3 = 15
    };

    gpio(uint8_t port, uint8_t pin);
    void init(Direction direction);
    bool gpio_get_level();
    void gpio_set_high();
    void gpio_set_low();
    void gpio_set(bool high);
  private:
    uint8_t port_num;
    uint8_t pin_num;

    LPC_GPIO_TypeDef* get_port();
};
