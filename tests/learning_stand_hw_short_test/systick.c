/**
  ******************************************************************************
  * \file    systick.c
  * \author  Александр Смирнов
  * \version 1.1.0
  * \date    02.01.2021
  * \brief   Функции для формирования временных задержек с помощью SysTick
  ******************************************************************************
*/

#include "systick.h"
#include <stm32f0xx.h>

volatile static uint32_t systick_ms;

void systick_init(uint32_t ticks)
{
    systick_ms = 0;
    SysTick_Config(ticks);
    NVIC_SetPriority(SysTick_IRQn, 15);
    NVIC_EnableIRQ(SysTick_IRQn);
}

uint32_t systick_get_tick(void)
{
    return systick_ms;
}

void systick_delay(uint32_t ticks)
{
    uint32_t start = 0;

    start = systick_get_tick();
    while((systick_get_tick() - start) < ticks);
}

void systick_interrupt(void)
{
    systick_ms++;
}
