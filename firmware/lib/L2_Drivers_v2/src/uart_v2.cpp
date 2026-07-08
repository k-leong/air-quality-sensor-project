#include "L2_Drivers_v2/uart_v2.hpp"

uart::uart(uart_port port) : port_num(port) {}

void uart::init(uint32_t baudrate, uint32_t pclk) {
  const uint16_t divider = (pclk / (16 * baudrate));
  switch (uart::port_num) {
  case uart::uart_port::uart1:
    LPC_SC->PCONP |= (1 << 4); // Power on UART1
    LPC_SC->PCLKSEL0 &= ~(3 << 8); // Clear PCLK for UART1
    LPC_UART1->LCR |= (1 << 7); // Enable access to Divisor Latches
    LPC_UART1->DLM |= (divider >> 8) & 0xFF; // Set DLM
    LPC_UART1->DLL |= (divider >> 0) & 0xFF; // Set DLL
    LPC_UART1->LCR &= ~(1 << 7); // Disable access to Divisor Latches
    LPC_UART1->FDR |= (1 << 4) | (0 << 0); // Set DIVADDVAL to 1 and MULVAL to 1
    LPC_PINCON->PINSEL4 |= (2 << 0) | (2 << 2); // Set P2.0 and P2.1 to UART1 TX and RX respectively
    break;
  case uart::uart_port::uart2:
    LPC_SC->PCONP |= (1 << 24); // Power on UART2
    LPC_SC->PCLKSEL1 &= ~(3 << 16); // Clear PCLK for UART2
    LPC_UART2->LCR |= (1 << 7);
    LPC_UART2->DLM = (divider >> 8) & 0xFF; // Set DLM
    LPC_UART2->DLL = (divider >> 0) & 0xFF; // Set DLL
    LPC_UART2->LCR &= ~(1 << 7);
    LPC_UART2->FDR = (1 << 4) | (0 << 0); // Set MULVAL to 1 and DIVADDVAL to 0
    LPC_UART2->LCR |= (3 << 0);
    LPC_PINCON->PINSEL4 |= (2 << 16) | (2 << 18);
    break;
  case uart::uart_port::uart3:
    LPC_SC->PCONP |= (1 << 25); // Power on UART3
    LPC_SC->PCLKSEL1 &= ~(3 << 18); // Clear PCLK for UART3
    LPC_UART3->LCR |= (1 << 7);
    LPC_UART3->DLM |= (divider >> 8) & 0xFF; // Set DLM
    LPC_UART3->DLL |= (divider >> 0) & 0xFF; // Set DLL
    LPC_UART3->LCR &= ~(1 << 7);
    LPC_UART3->FDR = (1 << 4) | (0 << 0); // Set DIVADDVAL to 0 and MULVAL to 1
    LPC_PINCON->PINSEL9 |= (2 << 24) | (2 << 26);
    // LPC_PINCON->PINSEL0 |= (2 << 0) | (2 << 2);
    break;
  default:
    return ; // Invalid port number
  }
}

void uart::write(char* data) {
  printf("Writing: %s\n", data);
  switch (uart::port_num) {
  case uart::uart_port::uart1:
    while (LPC_UART1->LSR & (1 << 5)) {
      LPC_UART1->THR = *data++;
    }
    break;
  case uart::uart_port::uart2:
    while (*data) {
      while ((LPC_UART2->LSR & (1 << 5)) == 0);
      LPC_UART2->THR = *data++;
    }
    
    break;
  case uart::uart_port::uart3:
    while (LPC_UART3->LSR & (1 << 5)) {
      LPC_UART3->THR = *data++;
    }
    break;
  default:
    return ; // Invalid port number
  }
}

char uart::read() {
  switch (uart::port_num) {
  case uart::uart_port::uart1:
    while (LPC_UART1->LSR | (1 << 0)) {
      return LPC_UART1->RBR;
    }
    break;
  case uart::uart_port::uart2:    
    while (!(LPC_UART2->LSR & (1 << 0)));
    return LPC_UART2->RBR;
  case uart::uart_port::uart3:
    while (LPC_UART3->LSR | (1 << 0)) {
      return LPC_UART3->RBR;
    }
    break;
  default:
    return -1; // Invalid port number
  }
}
