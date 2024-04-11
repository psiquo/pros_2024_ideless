CC=arm-none-eabi-gcc

CFLAGS=-mcpu=cortex-m4 -mthumb -nostdlib -DSTM32F407xx
INCLUDES=-ICMSIS/CMSIS/Core/Include -ICMSIS/Device/ST/STM32F4/Include -IHAL/Inc -I.
LD_FLAGS=-T linker_script.ld 

.PHONY: clean flash

all: blink.elf

clean:
	rm *.o *.elf
flash: blink.elf 
	sudo openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program blink.elf verify reset exit"


blink.elf: main.o startup.o system_stm32f4xx.o startup.s stm32f4xx_hal_gpio.o
	$(CC) $(CFLAGS) $(INCLUDES) $(LD_FLAGS) $^ -o $@ 

main.o: main.c 
	$(CC) $(CFLAGS) $(INCLUDES) $^ -c

startup.o: startup.c 
	$(CC) $(CFLAGS) $(INCLUDES) $^ -c

system_stm32f4xx.o: CMSIS/Device/ST/STM32F4/Source/Templates/system_stm32f4xx.c
	$(CC) $(CFLAGS) $(INCLUDES) $^ -c

stm32f4xx_hal_gpio.o: HAL/Src/stm32f4xx_hal_gpio.c
	$(CC) $(CFLAGS) $(INCLUDES) $^ -c