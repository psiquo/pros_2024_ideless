#include <stdint.h>

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss, _sidata;

void sys_setup(void);

void main(void);

void default_handler(void){
    while(1);
}

void sys_setup(void){
    uint32_t data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *flash_data = (uint8_t*) &_sidata;
    uint8_t *sram_data = (uint8_t*) &_sdata;

    for(uint32_t i = 0; i < data_size ; i++){
        sram_data[i] = flash_data[i];
    }

    uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    uint8_t *bss = (uint8_t*) &_sbss;

    for(uint32_t i = 0 ; i < bss_size; i++){
        bss[i] = 0;
    }

    main();
}
