/**
  ******************************************************************************
  * \file    main.c
  * \author  Александр Смирнов
  * \version 1.0.0
  * \date    17.08.2022
  * \brief   Программа на языке C для учебного стенда на базе
  *          STM32F072RBT6 в среде разработки Keil uVision 5.
  *          Подключение библиотек поддержки МК STM32F072RBT6 осуществляется
  *          средствами IDE Keil через Run-Time Environment (RTE).
  *          Программа для тестирования учебного стенда в укороченном
  *          варианте. Тест светодиодов (LED1-LED16), кнопок (SB1-SB4) и 
  *          переключателей (SW1-SW4).
  *          Программа работает в режиме 1 учебного стенда (S1 = 0, S2 = 1).
  ******************************************************************************
  */

#include <stm32f0xx.h>
#include "hal.h"
#include "systick.h"

int main(void)
{
    systick_init(8000);

    // Включить тактирование портов A, B, C
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    // Настройка на вывод LED1-LED16
    GPIOC->MODER |=
        GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 |
        GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 |
        GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0 |
        GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0;

    // Настройка на вывод RGB
    GPIOA->MODER |=
        GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0;

    /* Линия PA14 (SW4) после сброса используется как SWCLK в режиме AF с pull-down.
       Для использования PA14 как порт ввода требуется отключить эти режимы,
       но при этом перестает работать отладочный интерфейс. */
    GPIOA->MODER &= ~GPIO_MODER_MODER14;
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR14;

    // Включение подтягивающих резисторов для SW1-SW4
    GPIOA->PUPDR |=
        GPIO_PUPDR_PUPDR11_0 | GPIO_PUPDR_PUPDR12_0 | GPIO_PUPDR_PUPDR13_0 | GPIO_PUPDR_PUPDR14_0;

    // Включение подтягивающих резисторов для SB1-SB4
    GPIOB->PUPDR |=
        GPIO_PUPDR_PUPDR4_0 | GPIO_PUPDR_PUPDR5_0 | GPIO_PUPDR_PUPDR6_0 | GPIO_PUPDR_PUPDR7_0;

    uint16_t color = 0;
    uint8_t direction = 0;

    for(;;)
    {
        // Проверка кнопок SB1-SB4
        if (GPIOB->IDR & SB1_PIN)
        {
            GPIOA->ODR = LED_RED_PIN;
            GPIOC->ODR = 0xFFFF;
            break;
        }

        if (GPIOB->IDR & SB2_PIN)
        {
            GPIOA->ODR = LED_GREEN_PIN;
            GPIOC->ODR = 0xFFFF;
            break;
        }

        if (GPIOB->IDR & SB3_PIN)
        {
            GPIOA->ODR = LED_BLUE_PIN;
            GPIOC->ODR = 0xFFFF;
            break;
        }

        if (GPIOB->IDR & SB4_PIN)
        {
            GPIOA->ODR = LED_WHITE_PIN;
            GPIOC->ODR = 0xFFFF;
            break;
        }

        // Проверка переключателей SW1-SW4
        color = 0;
        direction = 0;
        if (GPIOA->IDR & SW1_PIN)
        {
            color |= LED_RED_PIN;
        }

        if (GPIOA->IDR & SW2_PIN)
        {
            color |= LED_GREEN_PIN;
        }

        if (GPIOA->IDR & SW3_PIN)
        {
            color |= LED_BLUE_PIN;
        }

        if (GPIOA->IDR & SW4_PIN)
        {
            direction = 1;
        }

        // Бегущий огонь
        GPIOA->ODR = color;
        GPIOC->ODR = 0;
        for (uint32_t i = 0; i < 16; i++)
        {
            GPIOC->ODR = direction ? (1 << i) : (0x8000 >> i);
            systick_delay(100);
        }
    }
}

void SysTick_Handler(void)
{
    systick_interrupt();
}
