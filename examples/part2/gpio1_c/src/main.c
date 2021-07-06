#include "stm32f072xb.h"

#include "cmsis_gcc.h"
// #include "core_cm3.h"

int main(void)
{
    RCC->AHBENR = 1 << 19; // Включение тактирования Port C
    GPIOC->MODER = 0x00000005; // Режим вывода для линий PC0 и PC1

    for (;;)
    {
        for (int i = 0; i < 100000; i++);
        GPIOC->ODR = 0x00000003;
        for (int i = 0; i < 100000; i++);
        GPIOC->ODR = 0x00000000;
    }
}
