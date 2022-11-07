#include "tick.h"

static volatile uint32_t tick_count = 0;

/**
 * @brief Initializes the ticks. The ticks will happen every 1 ms (1000 Hz)
 */
void tick_init() {
    TIM1->ARRH = (uint8_t)(TIM1_TICK_TIMER_PERIOD >> 8);
    TIM1->ARRL = (uint8_t)(TIM1_TICK_TIMER_PERIOD);
    TIM1->PSCRH = (uint8_t)(TIM1_TICK_TIMER_PRESCALER >> 8);
    TIM1->PSCRL = (uint8_t)(TIM1_TICK_TIMER_PRESCALER);

    TIM1->CR1 = (uint8_t)((uint8_t)(TIM1->CR1 & (uint8_t)(~(TIM1_CR1_CMS | TIM1_CR1_DIR))));
    TIM1->RCR = 0x00;

    TIM1->SR1 = (uint8_t)(~(uint8_t)(TIM1_FLAG_UPDATE));
    TIM1->SR2 = (uint8_t)((uint8_t)(~((uint8_t)((uint16_t)TIM1_FLAG_UPDATE >> 8))) & (uint8_t)0x1E);

    TIM1->IER |= (uint8_t)TIM1_IT_UPDATE;

    TIM1->CR1 |= TIM1_CR1_CEN;
}

/**
 * @brief Returns current tick
 * @retval Current tick
 */
uint32_t get_tick() {
    return tick_count;
}

/**
 * @brief Returns current timer count
 * @retval Current timer count
 */
uint16_t get_timer_count() {
    return (TIM1->CNTRH << 8) + (TIM1->CNTRL);
}

/**
 * @brief Delay with 1ms step
 * @param delay_ms Delay we want to use in ms
 */
void delay_ms(uint16_t delay_ms) {
    uint32_t start_tick = get_tick();
    while ((start_tick + delay_ms) > get_tick());
}

/**
 * @brief Callback from TIM1 interrupt
 */
void tim1_interrupt_callback() {
    tick_count++;
    TIM1->SR1 = (uint8_t)(~(uint8_t)TIM1_IT_UPDATE);
}

