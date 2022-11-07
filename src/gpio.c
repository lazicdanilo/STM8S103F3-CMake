#include "gpio.h"

/**
 * @brief Initializes used GPIOs
 */
void gpio_init() {
    DEBUG_LED_GPIO_PORT->CR2 &= (uint8_t)(~(DEBUG_LED_PIN));  
    DEBUG_LED_GPIO_PORT->ODR &= (uint8_t)(~(DEBUG_LED_PIN));
    DEBUG_LED_GPIO_PORT->DDR |= (uint8_t)DEBUG_LED_PIN;
    DEBUG_LED_GPIO_PORT->CR1 |= (uint8_t)DEBUG_LED_PIN;
}

/**
 * @brief Turns ON the LED
 */
void led_on() {
    DEBUG_LED_GPIO_PORT->ODR |= (uint8_t)DEBUG_LED_PIN;
}

/**
 * @brief Turns OFF the LED
 */
void led_off() {
    DEBUG_LED_GPIO_PORT->ODR &= (uint8_t)(~DEBUG_LED_PIN);
}

/**
 * @brief Toggles the LED
 */
void led_toggle() {
    DEBUG_LED_GPIO_PORT->ODR ^= (uint8_t)DEBUG_LED_PIN;
}
