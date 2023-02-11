/**
  ******************************************************************************
  * \file    i2c_temp.c
  * \author  Александр Смирнов
  * \version 1.0.0
  * \date    5.02.2023
  * \brief   Программа на языке C для учебного стенда на базе
  *          STM32F072RBT6 в среде разработки Keil uVision 5.
  *          Подключение библиотек поддержки МК STM32F072RBT6 осуществляется
  *          средствами IDE Keil через менеджер пакетов Run-Time Environment (RTE).
  *          Разработать программу, обеспечивающую чтение температуры
  *          с датчика STLM75M2F по интерфейсу I2C и последующий вывод
  *          на семисегментный индикатор.
  *          Программа работает в режиме 2 учебного стенда (S1 = 1, S2 = 0).
  ******************************************************************************
  */

/* Подключение заголовочного файла с макроопределениями всех регистров специальных
   функций МК STM32F072RBT6. */
#include <stm32f0xx.h>

/******* Низкоуровневые драйверы (драйверы периферии) *******/
/* Функция инициализации приемника/передатчика I2C */
void i2c_init(void)
{
    /* Включить тактирование порта B */
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    /* Включить тактирование I2C2 */
    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;

    /* Включить режим альтернативной функции 1 (I2C2) на линиях 10 и 11 */
    GPIOB->AFR[1] |= (1 << GPIO_AFRH_AFSEL10_Pos) | (1 << GPIO_AFRH_AFSEL11_Pos);

    /* Включить режим альтернативной функции на линиях PB10 и PB11 */
    GPIOB->MODER |=
        GPIO_MODER_MODER10_1 | GPIO_MODER_MODER11_1;

    /* Настройка частоты тактирования.
       Standard Mode - 100 кГц*/
    I2C2->TIMINGR = (uint32_t)0x10420F13;
    /* Включаем I2C */
    I2C2->CR1 |= I2C_CR1_PE;
}

/* Функция передачи байта в бесконечном цикле */
void i2c_transmit(uint8_t dev_addr, uint8_t data[], uint8_t n)
{
    I2C2->CR2 = I2C_CR2_AUTOEND | (dev_addr << 1) | (n << 16);
    I2C2->CR2 |= I2C_CR2_START;

    uint8_t i = 0;
    while (i < n)
    {
        while (!(I2C2->ISR & I2C_ISR_TXIS));
        I2C2->TXDR = data[i];
        i++;
    }
    while (!(I2C2->ISR & I2C_ISR_TC));
}

/* Функция приема байта в бесконечном цикле */
void i2c_receive(uint8_t dev_addr, uint8_t data[], uint8_t n)
{
    I2C2->CR2 = I2C_CR2_AUTOEND | I2C_CR2_RD_WRN | (dev_addr << 1) | (n << 16);
    I2C2->CR2 |= I2C_CR2_START;

    uint8_t i = 0;
    while (i < n)
    {
        while (!(I2C2->ISR & I2C_ISR_RXNE));
        data[i] = I2C2->TXDR;
        i++;
    }
    while (!(I2C2->ISR & I2C_ISR_TC));
}

/* Функция инициализации таймера TIM1 */
void timer_init(uint16_t period_us)
{
    /* Включение тактирования TIM1 */
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    /* Расчет предделителя частоты и кода переполнения таймера
       (максимальный код таймера).
       Пусть таймер счетчик переключается каждую 1 мкс или 1 МГц,
       тогда при частоте тактирования МК fmcu = 8 МГц, требуется предделитель
       на 80. Prescaler = 8 МГц / 1 МГц = 1. */
    /* Предделитель частоты */
    TIM1->PSC = 8;

    /* Максимальный код таймера (счет идет от 0 до 999) */
    TIM1->ARR = period_us - 1;

    /* Включение прерывания по переполнению */
    TIM1->DIER |= TIM_DIER_UIE;

    /* Включение таймера */
    TIM1->CR1 |= TIM_CR1_CEN;

    /* Установка приоритета прерывания по переполнению таймера.
       В Cortex-M0 четыре уровня приоритета - 0-3.
       0 - наибольший приоритет, 3 - наименьший. */
    NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 0);

    /* Разрешение прерывания по переполнению */
    NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
}

void (*timer_callback)(void);

void timer_set_callback(void (*callback)(void))
{
    timer_callback = callback;
}

/* Подпрограмма обработчик прерываний по переполнению таймера */
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
    /* Сброс флага вызвавшего прерывание */
    TIM1->SR &= ~TIM_SR_UIF;

    if (timer_callback != (void *)0)
        timer_callback();
}

/******* Высокоуровневые драйверы (драйверы устройств) *******/

void temp_sens_init(void)
{
    i2c_init();
}

#define STLM75M2F_DEV_ADDR      0b1001000

#define STLM75M2F_TEMP_REG      0x00    // 16 бит
#define STLM75M2F_CONF_REG      0x01    // 8 бит
#define STLM75M2F_HYST_REG      0x02    // 16 бит
#define STLM75M2F_OVTEMP_REG    0x03    // 16 бит

int8_t temp_sens_get_temp(void)
{
    uint8_t buf[2];
    
    /* Отправка указателя на регистр температуры */
    buf[0] = STLM75M2F_TEMP_REG;
    i2c_transmit(STLM75M2F_DEV_ADDR, buf, 1);

    /* Чтение двух байт из регистра температуры */
    i2c_receive(STLM75M2F_DEV_ADDR, buf, 2);

//    uint8_t temp;
//    i2c_receive(STLM75M2F_DEV_ADDR, &temp, 1);
//    return temp;

    return buf[0];
}

void sev_seg_update(void);

void sev_seg_init(void)
{
    /* Включить тактирование порта C */
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    /* Настройка на вывод */
    GPIOC->MODER |=
        GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 |
        GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0;

    /* Настройка на вывод D1, D2, D3, D4 */
    GPIOC->MODER |=
        GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0;

    /* Инициализация таймера - 1000 мкс */
    timer_init(1000);
    /* Фукнция, которая вызывается каждые 1000 мкс */
    timer_set_callback(sev_seg_update);
}

uint8_t sev_seg_decode(char ch, uint8_t dot)
{
    const uint8_t ch_code [] =
    {
        0b00111111, // 0
        0b00000110, // 1
        0b01011011, // 2
        0b01001111, // 3
        0b01100110, // 4
        0b01101101, // 5
        0b01111101, // 6
        0b00000111, // 7
        0b01111111, // 8
        0b01101111, // 9
        0b01000000  // -
    };

    if (ch >= '0' && ch <= '9')
    {
        return ch_code[ch - '0'] | (dot ? 0x80 : 0x00);
    }
    else if (ch == '-')
    {
        return ch_code[10];
    }
    else
    {
        return 0b00000000;
    }
}

#define D1_PIN         (1 << 8)
#define D2_PIN         (1 << 9)
#define D3_PIN         (1 << 10)
#define D4_PIN         (1 << 11)

char buf_sev_seg[4] = {0};

void sev_seg_update(void)
{
    static uint8_t pos = 0;
    const uint32_t dx_pin[4] = {D1_PIN, D2_PIN, D3_PIN, D4_PIN};

    GPIOC->ODR = sev_seg_decode(buf_sev_seg[pos], 0) | dx_pin[pos];

    pos = (pos + 1) % 4;
}

int32_t _strlen(char* s);

void sev_seg_print(char *s)
{
    for (int32_t i = _strlen(s) - 1, j = 0; i >= 0; i--, j++)
    {
        buf_sev_seg[3 - j] = s[i];
    }
}

/******* Дополнительные функции *******/

int32_t _strlen(char* s)
{
    int32_t i = 0;

    while (s[i] != '\0')
    {
        i++;
    }

    return i;
}

void reverse(char* s)
{
    for (int32_t i = 0, j = _strlen(s) - 1; i < j; i++, j--)
    {
        char c;
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void _itoa(int32_t n, char* s)
{
    int32_t sign = n;

    if (sign < 0) n = -n;

    int32_t i = 0;
    do
    {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) s[i++] = '-';
    s[i] = '\0';

    reverse(s);
}

/******* Функция main - точка входа в программу *******/
int main(void)
{
    temp_sens_init();
    sev_seg_init();

    for(;;)
    {
        int8_t temp = temp_sens_get_temp();
        char temp_str[4] = {0};
        _itoa(temp, temp_str);
        sev_seg_print(temp_str);
    }
}
