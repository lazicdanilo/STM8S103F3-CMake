#ifndef UART_H
#define UART_H

#include "tick.h"
#include "stm8s_gpio.h"

#define UART_SPEED      115200

#define UART_TX_PORT    GPIOD
#define UART_TX_PIN     GPIO_PIN_5
#define UART_RX_PORT    GPIOD
#define UART_RX_PIN     GPIO_PIN_6

void uart_init();
uint8_t uart_tx(uint8_t *buffer, uint8_t tx_size);
uint8_t uart_rx(uint8_t *rx_buffer, uint8_t rx_size, uint16_t timeout_100_ms);

#endif  /* UART_H */
