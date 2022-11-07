#include "main.h"

void debug_print(char *msg, uint32_t msg_size) {
    uart_tx((uint8_t*)msg, (uint8_t)msg_size);
}

void main() {
    CLK->CKDIVR &= (uint8_t)(~CLK_CKDIVR_HSIDIV);
    CLK->CKDIVR |= (uint8_t)CLK_PRESCALER_HSIDIV1;

    tick_init();
    enableInterrupts();

    gpio_init();
    uart_init();
    add_log_print_function(debug_print);

    while (1) {
        LOG_INFO("Toggle LED");
        led_toggle();
        delay_ms(1000);
    }
}
