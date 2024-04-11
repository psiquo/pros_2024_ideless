#include <stdint.h>

#define PERIPHERAL_BASE (0x40000000U)
#define AHB1_BASE (PERIPHERAL_BASE + 0x20000U)

#define GPIOD_BASE (AHB1_BASE + 0xC00U)
#define GPIO_MODER_OFFSET (0x0U)
#define GPIO_ODR_OFFSET (0x14U)
#define GPIOD_MODER ((volatile uint32_t*) (GPIOD_BASE + GPIO_MODER_OFFSET))
#define GPIOD_ODR ((volatile uint32_t*) (GPIOD_BASE + GPIO_ODR_OFFSET))

#define LED_PIN 15

#define RCC_BASE (AHB1_BASE + 0x3800U)
#define RCC_AHB1ENR ((volatile uint32_t*) (RCC_BASE + 0x30U))
#define RCC_AHB1ENR_GPIODEN (0x3U)

void main(void) {
    *RCC_AHB1ENR |= (1 << RCC_AHB1ENR_GPIODEN);
    
    volatile uint32_t dummy;
    dummy = *(RCC_AHB1ENR);
    dummy = *(RCC_AHB1ENR);

    *GPIOD_MODER &= (~0xC0000000);
    *GPIOD_MODER |= 0x40000000;

    *GPIOD_ODR = (1 << LED_PIN);

    while (1)
    {
        for (uint32_t i = 0; i < 1000000; i++);
    }
    
}