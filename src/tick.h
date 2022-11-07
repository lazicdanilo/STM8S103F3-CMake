#ifndef TICK_H
#define TICK_H

#include "gpio.h"

#define TIM1_TICK_TIMER_PRESCALER   160
#define TIM1_TICK_TIMER_PERIOD      100

void tick_init();
uint32_t get_tick();
uint16_t get_timer_count();
void delay_ms(uint16_t delay_ms);
void tim1_interrupt_callback();

#endif  /* TICK_H */