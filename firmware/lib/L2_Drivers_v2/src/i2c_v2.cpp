#include "i2c_v2.hpp"

i2c::i2c(bus port) : port(port) {}

bool i2c::init(uint32_t clock_rate) {
  // Implementation for initializing the I2C bus with the specified clock rate
  // This is a placeholder implementation and should be replaced with actual hardware initialization code
  switch (i2c::port){
  case i2c::bus::i2c1:
    LPC_SC->PCONP |= (1 << 19); // Power on I2C1
    LPC_SC->PCLKSEL1 &= ~(3 << 6); // Clear PCLK for I2C1
    LPC_PINCON->PINSEL0 |= (3 << 0) | (3 << 2); // Set P0.0 and P0.1 to I2C1 SDA and SCL
    return true;
  case i2c::bus::i2c2:
    LPC_SC->PCONP |= (1 << 26); // Power on I2C2
    LPC_SC->PCLKSEL1 &= ~(3 << 20); // Clear PCLK for I2C2
    LPC_PINCON->PINSEL0 |= (2 << 20) | (2 << 22); // Set P0.10 and P0.11 to I2C2 SDA and SCL
    return true;
  default:
    return false;
  }
}

bool i2c::read(uint8_t slave_addr, uint8_t* rx_data, uint32_t length) {
  // Implementation for reading data from the specified I2C slave address
  // This is a placeholder implementation and should be replaced with actual hardware read code
  return true;
}

bool i2c::write(uint8_t slave_addr, const uint8_t* tx_data, uint32_t length) {
  // Implementation for writing data to the specified I2C slave address
  // This is a placeholder implementation and should be replaced with actual hardware write code
  return true;
}

bool i2c::transfer(uint8_t slave_addr, const uint8_t* tx_data, uint32_t tx_length, uint8_t* rx_data, uint32_t rx_length) {
  // Implementation for transferring data to and from the specified I2C slave address
  // This is a placeholder implementation and should be replaced with actual hardware transfer code
  return true;
}

bool i2c::start() {
  // Implementation for generating a start condition on the I2C bus
  // This is a placeholder implementation and should be replaced with actual hardware start code

  get_port()->I2CONSET = (1 << 5); // Set STA bit to generate start condition

  while(get_port()->I2STAT != 0x08 && get_port()->I2STAT != 0x10) {
    // Wait for start condition to be transmitted
  }
  uint8_t status = get_port()->I2STAT;
  get_port()->I2CONCLR = (1 << 5); // Clear STA bit after start condition is transmitted
  return (status == 0x08 || status == 0x10);
}

bool i2c::stop() {
  // Implementation for generating a stop condition on the I2C bus
  // This is a placeholder implementation and should be replaced with actual hardware stop code
  // errors
  // 0x20 NACK -> throw error. force stop. tx
  // 0x30 NACK -> throw error. force stop. tx
  // 0x48 NACK -> throw error. force stop. rx
  
  // success
  // 0x28 ACK -> check for more bytes then stop if no more bytes. tx
  // 0x58 NACK -> last byte received. stop. rx
  get_port()->I2CONSET = (1 << 4);
  get_port()->I2CONCLR = (1 << 5); // Clear STA bit to generate stop condition
  return true;
}

bool i2c::send_byte() {
  // Implementation for sending a byte on the I2C bus
  // This is a placeholder implementation and should be replaced with actual hardware send code
  return true;
}

uint8_t i2c::receive_ack(bool ack) {
  // Implementation for receiving an acknowledgment on the I2C bus
  // This is a placeholder implementation and should be replaced with actual hardware receive code
  return true;
}

LPC_I2C_TypeDef* i2c::get_port() {
  switch (i2c::port) {
    case i2c::bus::i2c1:
      return LPC_I2C1;
    case i2c::bus::i2c2:
      return LPC_I2C2;
    default:
      return nullptr; // Invalid port
  }
}