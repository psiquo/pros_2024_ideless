#include <stdint.h>
#define STM32F407xx
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"


uint32_t ticks;
uint32_t counter = 0;

uint32_t leds[] = {GPIO_PIN_12,GPIO_PIN_13,GPIO_PIN_14,GPIO_PIN_15};

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
    SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0_Msk;
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA; 

    EXTI->IMR |= EXTI_IMR_IM0;
    EXTI->RTSR &= (~EXTI_RTSR_TR0_Msk);
    EXTI->FTSR |= EXTI_FTSR_TR0_Msk;

    NVIC_SetPriority(EXTI0_IRQn, 0);
    NVIC_EnableIRQ(EXTI0_IRQn);
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

    GPIOA->MODER &= (~GPIO_MODER_MODE10_Msk);
    GPIOA->PUPDR &= (~GPIO_PUPDR_PUPD0_Msk);
    GPIOA->PUPDR |= (0x10U << GPIO_PUPDR_PUPD0_Pos);
}
void EXTI0_IRQHandler(void) {
  if (EXTI->PR & 1) {
    EXTI->PR |= 1;
    GPIOD->ODR ^= (1 << leds[counter % 4]); 
    counter++;
  }
}

void main(void) {
    SysTick_Config(20000);
    __enable_irq();

    gpio_setup();
    //interrupt_setup();

     while (1)
     {   
         HAL_GPIO_TogglePin(GPIOD,leds[counter++ % 4]);
         delay(100);
     }
    
}