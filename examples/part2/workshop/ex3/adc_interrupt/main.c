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
  *          Программа измеряет напряжение POT1 и POT2. АЦП работает
  *          в 8-ми разрядном режиме. Значение на POT1 выводится на светодиоды
  *          LED1-LED8, POT2 - LED8-LED16.
  *          Окончание преобразования должно обрабатываться в прерывании.
  *          Программа работает в режиме 0 учебного стенда (S1 = 0, S2 = 0).
  ******************************************************************************
  */

/* Подключение заголовочного файла с макроопределениями всех регистром специальных
   функций МК STM32F072RBT6. */
#include <stm32f0xx.h>

/* Функция инициализации светодиодов */
void led_init(void)
{
    /* Включение тактирования порта C */
    RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIOCEN;

    /* Настройка на вывод линий PC0 - PC15 (LED1 - LED16) */
    GPIOC->MODER = GPIOC->MODER |
        (GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 |
         GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 |
         GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0 |
         GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0 |
         GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 |
         GPIO_MODER_MODER15_0);
}

/* Функция установки состояния светодиодов */
void led_set(uint16_t led)
{
    /* Записываем в регистра данных порта C новое состояние светодиодов.
       Номер бита соответствует номер светодиода: бит 0 - LED1, бит 1 - LED2 и
       так далее */
    GPIOC->ODR = led;
}

/* Инициализация потенциометров */
void pot_init(void)
{
    /* Включение тактирования порта A */
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    /* Включение тактирования АЦП */
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    /* Настройка линий PA0 (POT1) и PA1 (POT2) на аналоговый режим  */
    GPIOA->MODER |= GPIO_MODER_MODER0 | GPIO_MODER_MODER1;

    /* 8 бит */
    ADC1->CFGR1 |= ADC_CFGR1_RES_1;

    /* Прерывание по флагу EOC */
    ADC1->IER |= ADC_IER_EOCIE;

    /* Предделитель АЦП */
    ADC1->SMPR = 0x7;

    /* Включение АЦП */
    ADC1->CR |= ADC_CR_ADEN;
 
    /* Установка приоритета прерываний.
       В Cortex-M0 четыре уровня приоритета - 0-3.
       0 - наибольший приоритет, 3 - наименьший. */
    NVIC_SetPriority(ADC1_COMP_IRQn, 0);

    /* Разрешение прервания по ADC1 */
    NVIC_EnableIRQ(ADC1_COMP_IRQn);
}

/* Перечисление с номером потенциометра */
typedef enum {
    POT1 = ADC_CHSELR_CHSEL0, /* POT1 -> PA0 -> ADC Channel 0 */
    POT2 = ADC_CHSELR_CHSEL1, /* POT2 -> PA1 -> ADC Channel 1 */
} pot_t;

void pot_start(pot_t pot)
{
    /* Выбор следующего канала для преобразования */
    ADC1->CHSELR = pot;

    /* Программный запуск преобразования */
    ADC1->CR |= ADC_CR_ADSTART;
}

volatile uint16_t pot1_code = 0, pot2_code = 0;

/* Подпрограмма обработчик прерываний */
void ADC1_COMP_IRQHandler(void)
{
    if (ADC1->CHSELR == POT1)
    {
        pot1_code = ADC1->DR;
        pot_start(POT2);
    }
    else if (ADC1->CHSELR == POT2)
    {
        pot2_code = ADC1->DR;
        pot_start(POT1);
    }
}

/* Функция main - точка входа в программу */
int main(void)
{
    /* Инициализации светодиодов */
    led_init();
    /* Инициализация потенциометров */
    pot_init();

    pot_start(POT1);

    /* Бесконечный цикл */
    while (1)
    {
        /* Основные действия происходят в подпрограмме обработчике
           прерываний - ADC1_COMP_IRQHandler. Здесь результат
           АЦП выводится на светодиоды.
        */
        led_set(pot1_code | (pot2_code << 8));
    }
}
