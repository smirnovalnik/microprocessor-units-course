/**
  ******************************************************************************
  * \file    main.c
  * \author  Александр Смирнов
  * \version 1.0.0
  * \date    1.02.2022
  * \brief   Пример программа для лабораторной работы №1 на языке C
  *          для учебного стенда на базе STM32F072RBT6
  *          в среде разработки Keil uVision 5.
  *          Условние:
  *          Разработать программу, которая при нажатой кнопке SB4 выводит
  *          на светодиоды LED1-LED12 код первого канала АЦП,
  *          подключенного к потенциометру POT1, при нажатой кнопке SB3 –
  *          второго канала АЦП (POT2). При отжатых кнопка светодиоды
  *          выключены.
  *          Программа работает в режиме 0 учебного стенда (S1 = 0, S2 = 0).
  ******************************************************************************
  */

/* Подключение заголовочного файла с макроопределениями всех регистром специальных
   функций МК STM32F072RBT6. */
#include <stm32f0xx.h>

/* Функция main - точка входа в программу */
int main(void)
{
    /* Инициализация периферийных модулей */

    /* Включение тактирования порта A */
    RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIOAEN;
    /* Включение тактирования порта B */
    RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIOBEN;
    /* Включение тактирования порта C */
    RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIOCEN;
    /* Включение тактирования АЦП */
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    /* Настройка на вывод линий PC0 - PC11 (LED1 - LED12) */
    GPIOC->MODER = GPIOC->MODER |
        (GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 |
         GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 |
         GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0 |
         GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0);

    /* Включение подтягивающих резисторов PB6 (SB3) и PB7 (SB4). */
    GPIOB->PUPDR = GPIOB->PUPDR |
        (GPIO_PUPDR_PUPDR6_0 | GPIO_PUPDR_PUPDR7_0);

    /* Настройка линий PA0 (POT1) и PA1 (POT2) на аналоговый режим  */
    GPIOA->MODER |= GPIO_MODER_MODER0 | GPIO_MODER_MODER1;

    /* Включение АЦП */
    ADC1->CR |= ADC_CR_ADEN;

    /* Бесконечный цикл */
    while (1)
    {
        /* Объявление переменной sb3 и чтение состояние линии PB6 (SB3) */
        int sb3 = GPIOB->IDR & (1 << 6);
        /* Объявление переменной sb3 и чтение состояние линии PB7 (SB4)) */
        int sb4 = GPIOB->IDR & (1 << 5);

        if (sb3 == 0)
        {
            /* Выбор номера канала для следующего преобразования.
               Нулевой канал АЦП подключен к линии PA0. */
            ADC1->CHSELR = ADC_CHSELR_CHSEL0;
            /* Программный запуск преобразования */
            ADC1->CR |= ADC_CR_ADSTART;
            /* Ожидание установки флага End of Conversion (EOC) в 1 */
            while(!(ADC1->ISR & ADC_ISR_EOC_Msk));

            /* Вывод результата преобразования на регистры */
            GPIOC->ODR = ADC1->DR;
        }
        else if (sb4 == 0)
        {
            /* Выбор номера канала для следующего преобразования.
               Первый канал АЦП подключен к линии PA1. */
            ADC1->CHSELR = ADC_CHSELR_CHSEL1;
            /* Программный запуск преобразования */
            ADC1->CR |= ADC_CR_ADSTART;
            /* Ожидание установки флага End of Conversion (EOC) в 1 */
            while(!(ADC1->ISR & ADC_ISR_EOC_Msk));

            /* Вывод результата преобразования на регистры */
            GPIOC->ODR = ADC1->DR;
        }
        else
        {
            /* Выключить светодиоды PC0 - PC11 (LED1 - LED12) */
            GPIOC->ODR |= 0x0FFF;
        }
    }
}
