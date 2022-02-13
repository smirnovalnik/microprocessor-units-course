/**
  ******************************************************************************
  * \file    main.c
  * \author  Александр Смирнов
  * \version 1.0.0
  * \date    1.02.2022
  * \brief   Программа на языке C для учебного стенда на базе
  *          STM32F072RBT6 в среде разработки Keil uVision 5.
  *          Подключение библиотек поддержки МК STM32F072RBT6 осуществляется
  *          средствами IDE Keil через Run-Time Environment (RTE).
  *          При нажатии на кнопку SB1 включается светодиод LED1.
  *          Определения события нажатия по прерыванию.
  *          Программа работает в режиме 0 учебного стенда (S1 = 0, S2 = 0).
  ******************************************************************************
  */

/* Подключение заголовочного файла с макроопределениями всех регистром специальных
   функций МК STM32F072RBT6. */
#include <stm32f0xx.h>

/* Функция инициализации светодиода LED1 */
void led1_init(void)
{
    /* Включение тактирования порта C */
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    /* Настройка на вывод линии PC0 (LED1) */
    GPIOC->MODER |= GPIO_MODER_MODER0_0;
}

/* Функция включения светодиода LED1 */
void led1_on(void)
{
   /* Включаем LED установкой в 1 бита 0 */
    GPIOC->ODR |= 1;
}

/* Функция отключения светодиода LED1 */
void led1_off(void)
{
    /* Выключаем LED1 сбросом в 0 бита 0 */
    GPIOC->ODR &= ~1;
}

/* Функция инициализации кнопки SB1 */
void sb1_init(void)
{
    /* Включение тактирования порта B */
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    /* Включение подтягивающих резисторов PB4 (SB1) */
    GPIOB->PUPDR = GPIOB->PUPDR | GPIO_PUPDR_PUPDR4_0;

    /* Разрешение прерывания по линии EXTI4 в регистре
       Interrupt mask register (IMR) */
    EXTI->IMR |= EXTI_IMR_MR4;

    /* Разрешение прерывания по фронту по линии EXTI4 в регистре
       Rising trigger selection register(RTSR) */
    EXTI->RTSR |= EXTI_RTSR_RT4;
    
    /* Разрешение прерывания по спаду по линии EXTI4 в регистре
       Falling trigger selection register(FTSR) */
    EXTI->FTSR |= EXTI_FTSR_FT4;

    /* Включение тактирования модуля System configuration controller(SYSCFG) */
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    /* Подключение линии EXTI4 к выводу PB4 в регистре
       SYSCFG external interrupt configuration register (EXTICR2) */
    SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI4_PB;

    /* Сброс флага вызвовшего прерывание в регистре
       Pending register(PR) */
    EXTI->PR |= EXTI_PR_PIF4;

    /* Установка приоритета прерываний.
       В Cortex-M0 четыре уровня приоритета - 0-3.
       0 - наибольший приоритет, 3 - наименьший. */
    NVIC_SetPriority(EXTI4_15_IRQn, 0);

    /* Разрешение прервания по линиям EXTI4-EXTI15 */
    NVIC_EnableIRQ(EXTI4_15_IRQn);
}

/* Перечисление с состояниями кнопки */
typedef enum {
    SB_PRESSED,     /* Кнопка нажата */
    SB_UNPRESSED    /* Кнопка отжата */
} sb_state_t;

/* Функция получения состояния кнопки SB1 с антидребезгом */
sb_state_t sb1_get_state(void)
{
    /* Чтение состояния кнопки SB1 */
    uint16_t pin = (GPIOB->IDR >> 4) & 1;

    /* Если состояние SB1 было 0, то кнопка нажата */
    if (pin == 0)
    {
        return SB_PRESSED;
    }
    else
    {
        return SB_UNPRESSED;
    }
}

/* Подпрограмма обработчик прерываний от запросов на внешние прерывания
   портов ввода/вывода по линиям 4-15 */
void EXTI4_15_IRQHandler(void)
{
    /* Сброс флага вызвовшего прерывание в регистре
       Pending register(PR) */
    EXTI->PR |= EXTI_PR_PIF4;

    /* Чтение состояния кнопки */
    if (sb1_get_state() == SB_PRESSED)
    {
        led1_on();
    }
    else
    {
        led1_off();
    }
}

/* Функция main - точка входа в программу */
int main(void)
{
    /* Инициализации светодиода LED1 */
    led1_init();
    /* Инициализация кнопки SB1 */
    sb1_init();

    /* Бесконечный цикл */
    while (1)
    {
        /* Основные действия происходят в подпрограмме обработчике
           прерываний - EXTI4_15_IRQHandler. Здесь можно поместить
           другие задачи или например перевести МК в энергосберегающий режим
           с помощью функции __wfi();
        */
    }
}
