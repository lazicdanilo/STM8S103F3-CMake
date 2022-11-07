#ifndef GPIO_H
#define GPIO_H

#include "stm8s_gpio.h"

#define DEBUG_LED_GPIO_PORT GPIOB
#define DEBUG_LED_PIN       GPIO_PIN_5

void gpio_init();
void led_on();
void led_off();
void led_toggle();

#endif  /* GPIO_H */