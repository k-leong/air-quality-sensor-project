#pragma once

#include <stdint.h>
#include "LPC17xx.h"
#include "sys_config.h"
#include <stdio.h>
#include "utilities.h"

class uart {
  public:
    enum struct uart_port {
      uart1,
      uart2,
      uart3
    };
    // only available uarts ports/pins that are not compromised by the board's design and has available gpio pins for use
    enum struct uart1_pair : uint8_t {
      // con2 pin14 and pin15. blue color wire
      port = 2,
      tx_pin = 0,
      rx_pin = 1
    };
    enum struct uart2_pair : uint8_t {
      // con2 pin6 and pin7. black color wire
      port = 2,
      tx_pin = 8,
      rx_pin = 9
    };
    enum struct uart3_pair1 : uint8_t {
      // con1 pin16 and pin17. red color wire
      port = 4,
      tx_pin = 28,
      rx_pin = 29
    };
    enum struct uart3_pair2 : uint8_t {
      // con2 pin1 and pin2. white color wire
      port = 0,
      tx_pin = 0,
      rx_pin = 1
    };
    // enum struct uart3_pair3 : uint8_t {
    //   // con3 pin2 and con1 pin12. red color wire
    //   port = 0,
    //   tx_pin = 25,
    //   rx_pin = 26
    // };
    uart(uart_port port);
    void init(uint32_t baudrate, uint32_t pclk);
    void write(char* data);
    char read();
  private:
    uart_port port_num;
};