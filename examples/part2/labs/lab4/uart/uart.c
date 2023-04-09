/**
  ******************************************************************************
  * \file    uart.c
  * \author  Александр Смирнов
  * \version 1.0.0
  * \date    02.04.2022
  * \brief   Программа на языке C для учебного стенда на базе
  *          STM32F072RBT6 в среде разработки Keil uVision 5.
  *          Подключение библиотек поддержки МК STM32F072RBT6 осуществляется
  *          средствами IDE Keil через менеджер пакетов Run-Time Environment (RTE).
  *          Разработать программу, обеспечивающую управление цветом светодиода
  *          через командный интерфейс.
  *          При вводе команды "RED" светодиод D1 загорается красным цветом,
  *          при вводе "GREEN" - зеленым, "BLUE" - синим, а при вводе "WHITE" -
  *          белым цветом.
  *          Если введена неизвестная команда, то на терминал выводится слово
  *          "ERROR".
  *          Программа работает в режиме 1 учебного стенда (S1 = 0, S2 = 1).
  ******************************************************************************
  */

/* Подключение заголовочного файла с макроопределениями всех регистров специальных
   функций МК STM32F072RBT6. */
#include <stm32f0xx.h>

/* Функция инициализации светодиодов D1-D8 и линий управления цветом */
void leds_init(void)
{
    /* Включение тактирования порта A */
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    /* Включение тактирования порта C */
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    /* Настройка на вывод линий PA6, PA7, PA8 (RED, GREEN, BLUE) */
    GPIOA->MODER |= (GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0);

    /* Настройка на вывод линий PC0 - PC7 (D1 - D8) */
    GPIOC->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 |
                    GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 |
                    GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0;
}

/* Макроопределения с цветами */
#define RED     0x1
#define GREEN   0x2
#define BLUE    0x4

/* Функция включения светодиодов и выбора цвета */
void led_set(uint8_t led, uint8_t color)
{
    /* Записываем в регистр данных порта C новое состояние светодиодов.
       Номер бита соответствует номеру светодиода: бит 0 - D1, бит 1 - D2 и
       так далее */
    GPIOC->ODR = led;

    /* Включение светодиодов нужного цвета */
    if (color & RED)
    {
        GPIOA->ODR |= (1 << 6);
    }
    else
    {
        GPIOA->ODR &= ~(1 << 6);
    }

    if (color & GREEN)
    {
        GPIOA->ODR |= (1 << 7);
    }
    else
    {
        GPIOA->ODR &= ~(1 << 7);
    }

    if (color & BLUE)
    {
        GPIOA->ODR |= (1 << 8);
    }
    else
    {
        GPIOA->ODR &= ~(1 << 8);
    }
}

/* Функция инициализации приемника/передатчика USART2 */
void usart_init(void)
{
    /* Включить тактирование порта A */
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    /* Включить тактирование USART2 */
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    /* Включить режим альтернативной функции 1 (USART2) на линиях 2 и 3 */
    GPIOA->AFR[0] |= (1 << GPIO_AFRL_AFRL2_Pos) | (1 << GPIO_AFRL_AFRL3_Pos);

    /* Включить режим альтернативной функции на линиях PA2 и PA3 */
    GPIOA->MODER |=
        GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1;

    /* Установить коэффициент деления.
       BRR = fbus / baudrate
       Пусть baudrate = 9600 бит/с, частота шины fbs = 8 МГц,
       тогда BRR = 8000000 / 9600 */
    USART2->BRR = 8000000 / 9600;
    /* Включаем передатчик */
    USART2->CR1 |= USART_CR1_TE;
    /* Включаем приемник */
    USART2->CR1 |= USART_CR1_RE;
    /* Включаем USART */
    USART2->CR1 |= USART_CR1_UE;

    /* Чтение регистра данных для сброса флагов */
    uint16_t dummy = USART2->RDR;
}

/* Функция передачи байта в бесконечном цикле */
void usart_transmit(uint8_t data)
{
    /* Записать байт в регистр данных */
    USART2->TDR = data;
    /* Ожидание флага окончания передачи TC (Transmission Complete) */
    while(!(USART2->ISR & USART_ISR_TC));
}

/* Функция приема байта в бесконечном цикле */
uint8_t usart_receive(void)
{
    /* Ожидание флага буфер приемника не пуст RXNE (Receiver buffer not empty) */
    while(!(USART2->ISR & USART_ISR_RXNE));
    /* Чтение приятого байта и возврат */
    return USART2->RDR;
}

/* Функция сравнения двух строк.
   В стандартной библиотеке C уже есть функция strcmp.
   В примере для учебных целей показана простейшая реализация
   такой функции. */
int32_t _strcmp(char s1[], char s2[])
{
    int32_t i = 0;

    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
        {
            break;
        }
        i++;
    }

    return s1[i] - s2[i];
}

/* Функция main - точка входа в программу */
int main(void)
{
    /* Инициализация светодиодов D1-D8 и управления цветом */
    leds_init();
    /* Инициализация таймера TIM1 */
    usart_init();

    /* Объявления массива buf и инициализация нулями. */
    char buf[20] = {0};
    int32_t pos = 0;

    /* Бесконечный цикл */
    while (1)
    {
        char ch = usart_receive();

        /* Наполнение буфера если не нажата клавиша Enter.
           Символ `\r` передается при нажатии клавиши Enter в терминале. */
        if (ch != '\r')
        {
            if (pos < 20)
            {
                buf[pos] = ch;
                pos++;
            }
        }
        else
        {
            /* Сравнение содержимого буфера с командой */
            if (_strcmp(buf, "RED") == 0)
            {
                /* Исполнение команды */
                led_set(0x01, RED);
            }
            else if (_strcmp(buf, "GREEN") == 0)
            {
                led_set(0x01, GREEN);
            }
            else if (_strcmp(buf, "BLUE") == 0)
            {
                led_set(0x01, BLUE);
            }
            else if (_strcmp(buf, "WHITE") == 0)
            {
                led_set(0x01, RED |  GREEN | BLUE);
            }
            /* Команда не найдена */
            else
            {
                /* Передача строки ERROR.
                   Символ `\n` переводит курсор на новую строку в терминале */
                char* str = "ERROR\n";
                for (int32_t i = 0; i < sizeof("ERROR\n") - 1; i++)
                {
                    usart_transmit(str[i]);
                }
            }

            /* Буфер наполняется заново */
            pos = 0;
            /* Очистка буфера */
            for(int32_t i = 0; i < 20; i++)
            {
                buf[i] = '\0';
            }
        }
    }
}
