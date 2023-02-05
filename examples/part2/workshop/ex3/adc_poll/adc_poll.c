/**
  ******************************************************************************
  * \file    main.c
  * \author  Александр Смирнов
  * \version 1.0.0
  * \date    1.02.2022
  * \brief   Программа на языке C для учебного стенда на базе
  *          STM32F072RBT6 в среде разработки Keil uVision 5.
  *          Подключение библиотек поддержки МК STM32F072RBT6 осуществляется
  *          средствами IDE Keil через менеджер пакетов Run-Time Environment (RTE).
  *          В верхнем положении ключа SW1 включается светодиод D16,
  *          в нижнем светодиод D16 выключается.
  *          Программа работает в режиме 0 учебного стенда (S1 = 0, S2 = 0).
  ******************************************************************************
  */

/* Подключение заголовочного файла с макроопределениями всех регистром специальных
   функций МК STM32F072RBT6. */
#include <stm32f0xx.h>

/* Функция программной временной задержки */
void software_delay(uint32_t ticks)
{
    while (ticks > 0)
    {
        ticks = ticks - 1;
    }
}

/* Функция инициализации светодиодов */
void led_init(void)
{
    /* Включение тактирования порта C */
    RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIOCEN;

    /* Настройка на вывод линий PC0 - PC11 (D1 - D12) */
    GPIOC->MODER = GPIOC->MODER |
        (GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 |
         GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 |
         GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0 |
         GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0);
}

/* Функция установки состояния светодиодов */
void led_set(uint16_t led)
{
    /* Включение светодиодов*/
    GPIOC->ODR = led;
}

/* Функция инициализации кнопки SB3 */
void sb3_init(void)
{
    /* Включение тактирования порта B */
    RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIOBEN;

    /* Включение подтягивающих резисторов PB6 (SB3) */
    GPIOB->PUPDR = GPIOB->PUPDR | GPIO_PUPDR_PUPDR6_0;
}

/* Перечисление с состояниями кнопки */
typedef enum {
    SB_PRESSED_SHORT,   /* Кнопка нажата - короткое нажатие */
    SB_PRESSED_LONG,    /* Кнопка нажата - длительное нажатие */
    SB_UNPRESSED,       /* Кнопка отжата */
} sb_state_t;

/* Функция получения состояния кнопки SB1 с антидребезгом */
sb_state_t sb3_get_state(void)
{
    /* Здесь предложен следующий алгоритм антидребезга:
       В переменную pin_state через некоторый интервал
       записывается состояние линии PB4 через переменную pin.
       Если записывать состояние кнопки, то состояние
       переменной pin_state будет следующим:
       11111010101010000000000000000000101010101111111111
       | 1  |   2   |           3      |    4  |    5   |
       Состояние 1,5 - кнопка отжата,
                 2,4 - дребезг при нажатии и отжатии,
                 3 - кнопка нажата.
       Выбирая количество повторяющихся нулей или единиц можно
       выбирать чувствительность антидребезга. Чем длительнее интервалы
       тем дольше нужно нажимать кнопку.
    */

    /* Объявление статической переменной, которая сохраняет свое значение
       между вызовами функции */
    static uint16_t pin_state = 0xFFFF;
    static sb_state_t prev_state = SB_UNPRESSED;
    sb_state_t new_state;
    sb_state_t return_state;

    /* Программная задержка */
    software_delay(1000);

    /* Чтение состояния кнопки SB3 */
    uint16_t pin = (GPIOB->IDR >> 6) & 1;

    /* Сохранение нового состояния в переменную pin_state */
    pin_state = (pin_state << 1) | pin;

    /* Если 16 раз подряд состояние SB3 было 0, то кнопка нажата */
    if (pin_state == 0x0000)
    {
        new_state = SB_PRESSED_SHORT;
    }
    else
    {
        new_state = SB_UNPRESSED;
    }

    /* Определение возвращаемого состояния кнопки */
    if (new_state == SB_PRESSED_SHORT && prev_state == SB_UNPRESSED)
    {
        return_state = SB_PRESSED_SHORT;
    }
    else if (new_state == SB_PRESSED_SHORT && prev_state == SB_PRESSED_SHORT)
    {
        return_state = SB_PRESSED_LONG;
    }
    else
    {
        return_state = SB_UNPRESSED;
    }

    prev_state = new_state;

    return return_state;
}


/* Инициализация потенциометров */
void pot_init(void)
{
    /* Включение тактирования порта A */
    RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIOAEN;
    /* Включение тактирования АЦП */
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    /* Настройка линий PA0 (POT1) и PA1 (POT2) на аналоговый режим  */
    GPIOA->MODER |= GPIO_MODER_MODER0 | GPIO_MODER_MODER1;

    /* Включение АЦП */
    ADC1->CR |= ADC_CR_ADEN;
}

/* Перечисление с номером потенциометра */
typedef enum {
    POT1 = ADC_CHSELR_CHSEL0, /* POT1 -> PA0 -> ADC Channel 0 */
    POT2 = ADC_CHSELR_CHSEL1, /* POT2 -> PA1 -> ADC Channel 1 */
} pot_t;

/* Функция чтения состояния потенциометра */
uint16_t pot_get_data(pot_t pot)
{
    /* Выбор номера канала для следующего преобразования */
    ADC1->CHSELR = pot;
    /* Программный запуск преобразования */
    ADC1->CR |= ADC_CR_ADSTART;
    /* Ожидание установки флага End of Conversion (EOC) в 1 */
    while(!(ADC1->ISR & ADC_ISR_EOC_Msk));
    /* Возвращение результата преобразования */
    return ADC1->DR;
}

/* Функция main - точка входа в программу */
int main(void)
{
    /* Инициализация светодиодов */
    led_init();
    /* Инициализация кнопки SB3 */
    sb3_init();
    /* Инициализация потенциометров */
    pot_init();

    /* Бесконечный цикл */
    while (1)
    {
        /* Чтение состояния SB3 */
        if (sb3_get_state() == SB_PRESSED_LONG)
        {
            /* Если нажата, то читаем POT1 и выводим на светодиоды */
            led_set(pot_get_data(POT1));
        }
        else
        {
            /* В противном случаем, то читаем POT2 и выводим на светодиоды */
            led_set(pot_get_data(POT2));
        }
    }
}
