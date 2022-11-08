#include "uart.h"

/**
 * @brief Initializes the UART peripheral
 */
void uart_init() {
    uint32_t BaudRate_Mantissa = 0, BaudRate_Mantissa100 = 0;

    /* RX pin of UART */
    /* Set pin as input */
    UART_RX_PORT->DDR &= (uint8_t)(~(UART_RX_PIN));
    /* All Pull-Up on the pin */
    UART_RX_PORT->CR1 |= (uint8_t)UART_RX_PIN;
    /* No external interrupt or No slope control */
    UART_RX_PORT->CR2 &= (uint8_t)(~(UART_RX_PIN));

    /* TX pin of UART */
    /* Set pin as output */
    UART_TX_PORT->DDR |= (uint8_t)(UART_TX_PIN);
    /* Make it push-pull */
    UART_TX_PORT->CR1 |= (uint8_t)UART_TX_PIN;
    /* Output speed up to 2MHz */
    UART_TX_PORT->CR2 &= (uint8_t)(~(UART_TX_PIN));

    UART1->CR1 &= (uint8_t)(~UART1_CR1_M);  
    UART1->CR1 |= (uint8_t)0x00;
    UART1->CR3 &= (uint8_t)(~UART1_CR3_STOP);  
    UART1->CR3 |= (uint8_t)0x00;  
    UART1->CR1 &= (uint8_t)(~(UART1_CR1_PCEN | UART1_CR1_PS));  
    UART1->CR1 |= (uint8_t)0x00;  
    UART1->BRR1 &= (uint8_t)(~UART1_BRR1_DIVM);  
    UART1->BRR2 &= (uint8_t)(~UART1_BRR2_DIVM);  
    UART1->BRR2 &= (uint8_t)(~UART1_BRR2_DIVF);  

    BaudRate_Mantissa    = ((uint32_t)HSI_VALUE / (UART_SPEED << 4));
    BaudRate_Mantissa100 = (((uint32_t)HSI_VALUE * 100) / (UART_SPEED << 4));
    UART1->BRR2 |= (uint8_t)((uint8_t)(((BaudRate_Mantissa100 - (BaudRate_Mantissa * 100)) << 4) / 100) & (uint8_t)0x0F); 
    UART1->BRR2 |= (uint8_t)((BaudRate_Mantissa >> 4) & (uint8_t)0xF0); 
    UART1->BRR1 |= (uint8_t)BaudRate_Mantissa;           

    UART1->CR2 &= (uint8_t)~(UART1_CR2_TEN | UART1_CR2_REN); 
    UART1->CR3 &= (uint8_t)~(UART1_CR3_CPOL | UART1_CR3_CPHA | UART1_CR3_LBCL); 
    UART1->CR3 |= (uint8_t)((uint8_t)0x80 & (uint8_t)(UART1_CR3_CPOL | UART1_CR3_CPHA | UART1_CR3_LBCL));  
    UART1->CR2 |= (uint8_t)UART1_CR2_TEN;  
    UART1->CR2 |= (uint8_t)UART1_CR2_REN;  
    UART1->CR3 &= (uint8_t)(~UART1_CR3_CKEN); 
    UART1->CR1 &= (uint8_t)(~UART1_CR1_UARTD); 
}

/**
 * @brief Sends data from buffer over UART in polling mode
 * @param tx_buffer Pointer to the buffer from which we want to send data
 * @param tx_size Size of the data we want to send
 */
uint8_t uart_tx(uint8_t *tx_buffer, uint8_t tx_size) {
    for(uint8_t i = 0; i < tx_size; ++i) {
        UART1->DR = tx_buffer[i];
        while(!(UART1->SR & (uint8_t)UART1_FLAG_TXE));
    }
    return 0;
}

/**
 * @brief Receives data from UART in polling mode
 * @param rx_buffer Pointer to the buffer to which we want to save received data
 * @param rx_size Size of the data we want to receive
 * @param timeout_ms Timeout in ms
 */
uint8_t uart_rx(uint8_t *rx_buffer, uint8_t rx_size, uint16_t timeout_ms) {
    uint32_t start_tick = get_tick();
    for(uint8_t i = 0; i < rx_size; ++i) {
        while(!(UART1->SR & (uint8_t)UART1_FLAG_RXNE)) {
            if ((start_tick + timeout_ms) < get_tick()) {
                return 1;   /* Timeout ocurred */
            }
        }
        rx_buffer[i] = ((uint8_t)UART1->DR);
    }
    return 0;
}