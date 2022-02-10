/**
  ******************************************************************************
  * \file    main.c
  * \author  Александр Смирнов
  * \version 1.0.0
  * \date    1.02.2022
  * \brief   Программа на языке C для учебного стенда на базе
  *          STM32F072RBT6 в среде разработки Keil uVision 5.
  *          Подключение библиотек поддержки МК STM32F072RBT6 осуществляется
  *          средствами IDE Keil через Run-Time Enviroment (RTE).
  *          В верхнем положении ключа SW1 светодиоды LED8 и LED16 мигают,
  *          в нижнем светодиоды выключены.
  *          Программа работает в режиме 0 учебного стенда (S1 = 0, S2 = 0).
  ******************************************************************************
  */

/* Подключение заголовочного файла с макроопределениями всех регистром специальных
   функций МК STM32F072RBT6. */
#include <stm32f0xx.h>

/* Функция программной временной задержки */
void software_delay(int ticks)
{
    while (ticks > 0)
    {
        ticks = ticks - 1;
    }
}

/* Функция main - точка входа в программу */
int main(void)
{
    /* Инициализация периферийных модулей */

    /* Включение тактирования порта A */
    RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIOAEN;
    /* Включение тактирования порта C */
    RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIOCEN;

    /* Настройка на вывод линии PC7 (LED8) */
    GPIOC->MODER = GPIOC->MODER | GPIO_MODER_MODER7_0;
    /* Настройка на вывод линии PC15 (LED16) */
    GPIOC->MODER = GPIOC->MODER | GPIO_MODER_MODER15_0;

    /* Включение подтягивающего резистора линии PA11 (SW1) */
    GPIOA->PUPDR = GPIOA->PUPDR | GPIO_PUPDR_PUPDR11_0;

    /* Бесконечный цикл */
    while (1)
    {
        /* Объявление переменной sw1 и чтение состояние линии PA11 (SW1) */
        int sw1 = GPIOA->IDR & (1 << 11);

        /* Исполнение ветви в зависимости от состояния sw1 */
        if (sw1 != 0)
        {
            /* Мигание светодиодов */

            /* Типовой конструкцией для установки бита в определенной позиции
               является:
               Reg = Reg | (1 << n), где Reg - регистр, n - номер позиции.
               Здесь новым оператором является << - логический сдвиг влево.
               Например 1 << 1 - это логический сдвиг влево на одну позицию. В результате получится число
               10 (в двоичной форме) или 2 в десятично. 1 << 7 - логический сдвиг на 7 позиций - число
               0x00000080 */
            /* Включить светодиод PC7 (LED8) */
            GPIOC->ODR = GPIOC->ODR | (1 << 7);
            /* Включить светодиод PC15 (LED16) */
            GPIOC->ODR = GPIOC->ODR | (1 << 15);

            /* Программная временная задержка */
            software_delay(1000000);

            /* Типовой конструкцией для сброса бита в определенной позиции
               является:
               Reg = Reg & ~(1 << n), где Reg - регистр, n - номер позиции.
               Логический сдвиг (1 << 7) дает число 0x00000080.
               Оператор ~ в языке C это побитовое НЕ (инверсия).
               Число ~0x00000080 это 0xFFFFFF7F.
               После применения оператора логического И с маской 0xFFFFFF7F в регистре сбросится бит 7.
            */
            /* Выключить светодиод PC7 (LED8) */
            GPIOC->ODR = GPIOC->ODR & ~(1 << 7);
            /* Выключить светодиод PC15 (LED16) */
            GPIOC->ODR = GPIOC->ODR & ~(1 << 15);

            /* Программная временная задержка */
            software_delay(1000000);
        }
        else
        {
            /* Выключить светодиод PC7 (LED8) */
            GPIOC->ODR = GPIOC->ODR & ~(1 << 7);
            /* Выключить светодиод PC15 (LED16) */
            GPIOC->ODR = GPIOC->ODR & ~(1 << 15);
        }
    }
}