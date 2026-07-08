/*
 *     SocialLedge.com - Copyright (C) 2013
 *
 *     This file is part of free software framework for embedded processors.
 *     You can use it and/or distribute it as long as this copyright header
 *     remains unmodified.  The code is free for personal use and requires
 *     permission to use in a commercial product.
 *
 *      THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 *      OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 *      MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 *      I SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 *      CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *     You can reach the author of this software at :
 *          p r e e t . w i k i @ g m a i l . c o m
 */

/**
 * @file
 * @brief This is the application entry point.
 */

#include <stdio.h>
#include "utilities.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "queue.h"
#include "L2_Drivers_v2/gpio_v2.hpp"
#include "L2_Drivers_v2/uart_v2.hpp"


typedef struct {
  uint8_t led_pin;
  uint8_t switch_pin;
  SemaphoreHandle_t switch_press_indication;
} port_pin_s;

typedef struct {
  gpio led_pin;
  gpio switch_pin;
  SemaphoreHandle_t switch_press_indication;
} gpio_s;

static QueueHandle_t uart_queue;

void led_task(void *task_parameter) {
  gpio_s *pair = (gpio_s*) task_parameter;
  pair->led_pin.init(gpio::Direction::output);
  // gpio1__set_as_output(pair->led_pin);
  while (true) {
    // Note: There is no vTaskDelay() here, but we use sleep mechanism while waiting for the binary semaphore (signal)
    if (xSemaphoreTake(pair->switch_press_indication, 1000)) {
      // TODO: Blink the LED
      pair->led_pin.gpio_set_high(); // Set LED on
      vTaskDelay(100); // Keep LED on for 100ms
      pair->led_pin.gpio_set_low(); // Set LED off
    } else {
      puts("Timeout: No switch press indication for 1000ms");
    }
  }
}

void switch_task(void *task_parameter) {
  gpio_s *pair = (gpio_s*) task_parameter;
  pair->switch_pin.init(gpio::Direction::input);
  // gpio1__set_as_input(pair->switch_pin);
  while (true) {
    // TODO: If switch pressed, set the binary semaphore
    if (pair->switch_pin.gpio_get_level()) {
      xSemaphoreGive(pair->switch_press_indication);
    }
    
    // Task should always sleep otherwise they will use 100% CPU
    // This task sleep also helps avoid spurious semaphore give during switch debeounce
    vTaskDelay(100); 
  }
}

void uart_read_task(void *task_parameter) {
  uart *uart_ptr = (uart*) task_parameter;
  char value[50];
  int index = 0;
  while (1) {
    char c = uart_ptr->read();
    if (c == '\n' || c == '\r'){
      value[index] = '\0';
      printf("Value Received: %s \n", value);
      index = 0;
    } 
    else {
      value[index++] = c;
    }  
  }
}

void uart_write_task(void *task_parameter) {
  uart *uart_ptr = (uart*) task_parameter;
  char value[50] = "123456789\r\n";
  while (1) {
    printf("What would you like to send? ");
    // scanf("%s", value);
    uart_ptr->write(value);
    vTaskDelay(3000);
  }
}


int main (void)
{
  // gpio led0(1,static_cast<uint8_t>(gpio::compromised_pins::led0)); // LED0
  // gpio switch0(1,static_cast<uint8_t>(gpio::compromised_pins::switch0)); // SWITCH0
  // led0.init(gpio::Direction::output);
  // switch0.init(gpio::Direction::input);
  // static gpio_s pair0 = {.led_pin=led0, .switch_pin=switch0}; // LED0 and SWITCH0
  // pair0.switch_press_indication = xSemaphoreCreateBinary();
  // xTaskCreate(led_task, "LED0", configMINIMAL_STACK_SIZE, &pair0, tskIDLE_PRIORITY, NULL);
  // xTaskCreate(switch_task, "SWITCH0", configMINIMAL_STACK_SIZE, &pair0, tskIDLE_PRIORITY, NULL);
  // xTaskCreate(led_task, "LED1", configMINIMAL_STACK_SIZE, &pair1, tskIDLE_PRIORITY, NULL);
  // xTaskCreate(switch_task, "SWITCH1", configMINIMAL_STACK_SIZE, &pair1, tskIDLE_PRIORITY, NULL);
  // xTaskCreate(led_task, "LED0", configMINIMAL_STACK_SIZE, &pair2, tskIDLE_PRIORITY, NULL);
  // xTaskCreate(switch_task, "SWITCH0", configMINIMAL_STACK_SIZE, &pair2, tskIDLE_PRIORITY, NULL);
  // xTaskCreate(led_task, "LED0", configMINIMAL_STACK_SIZE, &pair3, tskIDLE_PRIORITY, NULL);
  // xTaskCreate(switch_task, "SWITCH0", configMINIMAL_STACK_SIZE, &pair3, tskIDLE_PRIORITY, NULL);

  static uart uart2(uart::uart_port::uart2);
  uint32_t pclk = sys_get_cpu_clock()/4;
  uart2.init(38400, pclk);
  xTaskCreate(uart_read_task, "uart read", 1024, &uart2, tskIDLE_PRIORITY, NULL);
  xTaskCreate(uart_write_task, "uart write", 1024, &uart2, tskIDLE_PRIORITY + 1, NULL);

  vTaskStartScheduler();
  return 0;
}
