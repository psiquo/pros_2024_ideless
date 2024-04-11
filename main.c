#include <stdint.h>
#define STM32F407xx
#include "stm32f4xx.h"


uint32_t ticks;

uint32_t leds[] = {12,13,14,15};

void SysTick_Handler(void){
  ticks++;
}

void delay(uint32_t ms) {
  uint32_t start = ticks;
  uint32_t end = start + ms;

  if (end < start) // handle overflow
  {
    while (ticks > 0); // wait for ticks to wrap around to zero
  }

  while (ticks < end);
}

void interrupt_setup(void){
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

}
void gpio_setup(void) {
    RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIODEN_Pos);
    
    volatile uint32_t dummy;
    dummy = RCC->AHB1ENR;
    dummy = RCC->AHB1ENR;

    GPIOD->MODER |= (1 << GPIO_MODER_MODER12_Pos);
    GPIOD->MODER |= (1 << GPIO_MODER_MODER13_Pos);
    GPIOD->MODER |= (1 << GPIO_MODER_MODER14_Pos);
    GPIOD->MODER |= (1 << GPIO_MODER_MODER15_Pos);
}

void main(void) {
    SysTick_Config(20000);
    __enable_irq();

    gpio_setup();

    uint32_t counter = 0;

    while (1)
    {   
        GPIOD->ODR ^= (1 << leds[counter++ % 4]);
        delay(100);
    }
    
}