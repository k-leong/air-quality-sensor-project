#include "L2_Drivers_v2/gpio_v2.hpp"

gpio::gpio(uint8_t port, uint8_t pin) : port_num(port), pin_num(pin) {}

LPC_GPIO_TypeDef* gpio::get_port() {
  switch (gpio::port_num) {
    case 0:
      return LPC_GPIO0;
    case 1:
      return LPC_GPIO1;
    case 2:
      return LPC_GPIO2;
    case 3:
      return LPC_GPIO3;
    case 4:
      return LPC_GPIO4;
    default:
      return nullptr; // Invalid port number
  }
}

void gpio::init(Direction direction) {
  switch (direction) {
    case Direction::input:
      get_port()->FIODIR &= ~(1 << gpio::pin_num);
      break;
    case Direction::output:
      get_port()->FIODIR |= (1 << gpio::pin_num);
      break;
  }
}

void gpio::gpio_set_high() {
  get_port()->FIOSET |= (1 << gpio::pin_num);
}

void gpio::gpio_set_low() {
  get_port()->FIOCLR |= (1 << gpio::pin_num);
}

bool gpio::gpio_get_level() {
  return get_port()->FIOPIN & (1 << gpio::pin_num);
}

void gpio::gpio_set(bool high) {
  if (high) {
    gpio_set_high();
  } 
  else {
    gpio_set_low();
  }
}
