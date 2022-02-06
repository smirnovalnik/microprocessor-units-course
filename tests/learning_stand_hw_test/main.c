#include <stm32f0xx.h>
#include "hal.h"
#include "systick.h"
#include "mt20s4a.h"

#include <stdio.h>

void test_pots(void);
void test_leds(void);
void test_vcp(void);
void test_sw(void);
void test_sb(void);
void test_keyboard(void);
void test_7seg(void);
void test_lcd(void);
void test_dac(void);
void test_spi_adc(void);
void test_i2c_hum(void);
void test_i2c_temp(void);

void test_pots(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Включить тактирование прота A
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Включить тактирование порта B
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN; // Включить тактирование порта C

    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    /* Настройка на вывод */
    GPIOC->MODER |= 
        GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 |
        GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 |
        GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0 |
        GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0;

    /* Настройка на вывод */
    GPIOA->MODER |= 
        GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0;

    GPIOA->MODER |= GPIO_MODER_MODER0 | GPIO_MODER_MODER1;

    /* АЦП */
    ADC1->CR |= ADC_CR_ADEN;

    /* Зеленые */
    GPIOA->ODR = LED_GREEN_PIN;
    for (;;)
    {
        ADC1->CHSELR = ADC_CHSELR_CHSEL0;
        ADC1->CR |= ADC_CR_ADSTART;
        while(!(ADC1->ISR & ADC_ISR_EOC_Msk));

        uint16_t adc_ch0 = ADC1->DR;
        uint16_t led_ch0 = 0;
        if (adc_ch0 > 10)
        {
            for (uint32_t i = 0; i < (adc_ch0/(4096/8)) + 1; i++)
            {
                led_ch0 += 1 << i;
            }
        }
        
        ADC1->CHSELR = ADC_CHSELR_CHSEL1;
        ADC1->CR |= ADC_CR_ADSTART;
        while(!(ADC1->ISR & ADC_ISR_EOC_Msk));

        uint16_t adc_ch1 = ADC1->DR;
        uint16_t led_ch1 = 0;
        if (adc_ch1 > 10)
        {
            for (uint32_t i = 0; i < (adc_ch1/(4096/8)) + 1; i++)
            {
                led_ch1 += 1 << i;
            }
        }
        
        GPIOC->ODR = led_ch0 | (led_ch1 << 8);
    }
}

void test_leds(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Включить тактирование прота A
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Включить тактирование порта B
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN; // Включить тактирование порта C

    /* Настройка на вывод */
    GPIOC->MODER |= 
        GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 |
        GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 |
        GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0 |
        GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0;

    /* Настройка на вывод */
    GPIOA->MODER |= 
        GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0;

    for (;;)
    {
        /* Красные */
        GPIOA->ODR = LED_RED_PIN;
        GPIOC->ODR = 0;
        for (uint32_t i = 0; i < 16; i++)
        {
            GPIOC->ODR = (1 << i);
            systick_delay(100000);
        }

        /* Зеленые */
        GPIOA->ODR = LED_GREEN_PIN;
        GPIOC->ODR = 0;
        for (uint32_t i = 0; i < 16; i++)
        {
            GPIOC->ODR = (1 << i);
            systick_delay(100000);
        }

        /* Синие */
        GPIOA->ODR = LED_BLUE_PIN;
        GPIOC->ODR = 0;
        for (uint32_t i = 0; i < 16; i++)
        {
            GPIOC->ODR = (1 << i);
            systick_delay(100000);
        }
        
        /* Белый */
        GPIOA->ODR = LED_WHITE_PIN;
        GPIOC->ODR = 0;
        for (uint32_t i = 0; i < 16; i++)
        {
            GPIOC->ODR = (1 << i);
            systick_delay(100000);
        }
    }
}

void test_sw(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Включить тактирование прота A
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Включить тактирование порта B
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN; // Включить тактирование порта C

    /* Настройка на вывод */
    GPIOC->MODER |= 
        GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0;

    /* Линия PA14 (SW4) после сброса используется как SWCLK в режиме AF с pull-down.
       Для использования PA14 как порт ввода требуется отключить эти режимы,
       но при этом перестает работать отладочный интерфейс. */
    GPIOA->MODER &= ~GPIO_MODER_MODER14;
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR14;

    /* Включение подтягивающих резисторов */
    GPIOA->PUPDR |=
        GPIO_PUPDR_PUPDR11_0 | GPIO_PUPDR_PUPDR12_0 | GPIO_PUPDR_PUPDR13_0 | GPIO_PUPDR_PUPDR14_0;

    while (1)
    {
        if (GPIOA->IDR & SW1_PIN)
            GPIOC->ODR |= LED0_PIN;
        else
            GPIOC->ODR &= ~LED0_PIN;

        if (GPIOA->IDR & SW2_PIN)
            GPIOC->ODR |= LED1_PIN;
        else
            GPIOC->ODR &= ~LED1_PIN;

        if (GPIOA->IDR & SW3_PIN)
            GPIOC->ODR |= LED2_PIN;
        else
            GPIOC->ODR &= ~LED2_PIN;

        if (GPIOA->IDR & SW4_PIN)
            GPIOC->ODR |= LED3_PIN;
        else
            GPIOC->ODR &= ~LED3_PIN;
    }
}

void test_sb(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Включить тактирование прота A
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Включить тактирование порта B
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN; // Включить тактирование порта C

    /* Настройка на вывод */
    GPIOC->MODER |= 
        GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0;

    /* Включение подтягивающих резисторов */
    GPIOB->PUPDR |=
        GPIO_PUPDR_PUPDR4_0 | GPIO_PUPDR_PUPDR5_0 | GPIO_PUPDR_PUPDR6_0 | GPIO_PUPDR_PUPDR7_0;

    while (1)
    {
        if (GPIOB->IDR & SB1_PIN)
            GPIOC->ODR &= ~LED0_PIN;
        else
            GPIOC->ODR |= LED0_PIN;

        if (GPIOB->IDR & SB2_PIN)
            GPIOC->ODR &= ~LED1_PIN;
        else
            GPIOC->ODR |= LED1_PIN;

        if (GPIOB->IDR & SB3_PIN)
            GPIOC->ODR &= ~LED2_PIN;
        else
            GPIOC->ODR |= LED2_PIN;

        if (GPIOB->IDR & SB4_PIN)
            GPIOC->ODR &= ~LED3_PIN;
        else
            GPIOC->ODR |= LED3_PIN;
    }
}

void test_keyboard(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Включить тактирование прота A
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Включить тактирование порта B
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN; // Включить тактирование порта C

    /* Настройка на вывод */
    GPIOC->MODER |= 
        GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 |
        GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 |
        GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0 |
        GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0;

    /* Настройка на вывод */
    GPIOA->MODER |= 
        GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0;

    /* R0, R1, R2, R3 */
    GPIOB->MODER |= 
        GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0;

    /* C0, C1, C2, C3 pull down */
    GPIOB->PUPDR = 0;
    GPIOB->PUPDR |=
        GPIO_PUPDR_PUPDR4_1 | GPIO_PUPDR_PUPDR5_1 | GPIO_PUPDR_PUPDR6_1 | GPIO_PUPDR_PUPDR7_1;

    /* Красные */
    GPIOA->ODR = LED_RED_PIN;
    for (;;)
    {
        GPIOB->ODR = R0_PIN;
        systick_delay(10);
        if (GPIOB->IDR & C0_PIN)
            GPIOC->ODR |= LED0_PIN;
        else
            GPIOC->ODR &= ~LED0_PIN;

        if (GPIOB->IDR & C1_PIN)
            GPIOC->ODR |= LED1_PIN;
        else
            GPIOC->ODR &= ~LED1_PIN;

        if (GPIOB->IDR & C2_PIN)
            GPIOC->ODR |= LED2_PIN;
        else
            GPIOC->ODR &= ~LED2_PIN;

        if (GPIOB->IDR & C3_PIN)
            GPIOC->ODR |= LED3_PIN;
        else
            GPIOC->ODR &= ~LED3_PIN;

        GPIOB->ODR = R1_PIN;
        systick_delay(10);
        if (GPIOB->IDR & C0_PIN)
            GPIOC->ODR |= LED4_PIN;
        else
            GPIOC->ODR &= ~LED4_PIN;

        if (GPIOB->IDR & C1_PIN)
            GPIOC->ODR |= LED5_PIN;
        else
            GPIOC->ODR &= ~LED5_PIN;

        if (GPIOB->IDR & C2_PIN)
            GPIOC->ODR |= LED6_PIN;
        else
            GPIOC->ODR &= ~LED6_PIN;

        if (GPIOB->IDR & C3_PIN)
            GPIOC->ODR |= LED7_PIN;
        else
            GPIOC->ODR &= ~LED7_PIN;

        GPIOB->ODR = R2_PIN;
        systick_delay(10);
        if (GPIOB->IDR & C0_PIN)
            GPIOC->ODR |= LED8_PIN;
        else
            GPIOC->ODR &= ~LED8_PIN;

        if (GPIOB->IDR & C1_PIN)
            GPIOC->ODR |= LED9_PIN;
        else
            GPIOC->ODR &= ~LED9_PIN;

        if (GPIOB->IDR & C2_PIN)
            GPIOC->ODR |= LED10_PIN;
        else
            GPIOC->ODR &= ~LED10_PIN;

        if (GPIOB->IDR & C3_PIN)
            GPIOC->ODR |= LED11_PIN;
        else
            GPIOC->ODR &= ~LED11_PIN;
        
        GPIOB->ODR = R3_PIN;
        systick_delay(10);
        if (GPIOB->IDR & C0_PIN)
            GPIOC->ODR |= LED12_PIN;
        else
            GPIOC->ODR &= ~LED12_PIN;

        if (GPIOB->IDR & C1_PIN)
            GPIOC->ODR |= LED13_PIN;
        else
            GPIOC->ODR &= ~LED13_PIN;

        if (GPIOB->IDR & C2_PIN)
            GPIOC->ODR |= LED14_PIN;
        else
            GPIOC->ODR &= ~LED14_PIN;

        if (GPIOB->IDR & C3_PIN)
            GPIOC->ODR |= LED15_PIN;
        else
            GPIOC->ODR &= ~LED15_PIN;
    }
}

uint8_t decoder_7seg(char ch, uint8_t dot)
{
    uint8_t ch_code [10] =
    {
        0b00111111,
        0b00000110,
        0b01011011,
        0b01001111,
        0b01100110,
        0b01101101,
        0b01111101,
        0b00000111,
        0b01111111,
        0b01101111
    };
    
    if (ch >= '0' && ch <= '9')
    {
        return ch_code[ch - '0'] | (dot ? 0x80 : 0x00);
    }
    else
    {
        return 0;
    }
}

void test_7seg()
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Включить тактирование прота A
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Включить тактирование порта B
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN; // Включить тактирование порта C

    /* Настройка на вывод */
    GPIOC->MODER |= 
        GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 |
        GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0;

    /* Настройка на вывод D1, D2, D3, D4 */
    GPIOC->MODER |= 
        GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0;

    for(;;)
    {
        for (uint32_t i = 0; i < 10; i++)
        {
            systick_delay(500000);
            GPIOC->ODR = decoder_7seg((i%10) + '0', i % 2) | D1_PIN;
        }
        for (uint32_t i = 0; i < 10; i++)
        {
            systick_delay(500000);
            GPIOC->ODR = decoder_7seg((i%10) + '0', i % 2) | D2_PIN;
        }
        for (uint32_t i = 0; i < 10; i++)
        {
            systick_delay(500000);
            GPIOC->ODR = decoder_7seg((i%10) + '0', i % 2) | D3_PIN;
        }
        for (uint32_t i = 0; i < 10; i++)
        {
            systick_delay(500000);
            GPIOC->ODR = decoder_7seg((i%10) + '0', i % 2) | D4_PIN;
        }
    }
}

void test_lcd()
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Включить тактирование прота A
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Включить тактирование порта B
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN; // Включить тактирование порта C
    
    GPIOC->MODER |= 
        GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 |
        GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0;
    
    GPIOC->MODER |= 
        GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0;
    
    init_disp();
    disp_on();
    
    uint32_t i = 0;
    char buf[100];
    for (;;)
    {
        i++;
        systick_delay(1000000);
        
        snprintf(buf, 100, "%d", i);
        put_str(buf, 0, 0);
    }
}

void usart_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;   // Включить тактирование USART2
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;      // Включить тактирование порта A

    // Включить режим альтернативной функции 1 на линиях 2 и 3
    GPIOA->AFR[0] |= ((0x01 << GPIO_AFRL_AFRL2_Pos)) | (0x01 << GPIO_AFRL_AFRL3_Pos); 

    // Включить режим альтернативной функции на линиях PA2 и PA3
    GPIOA->MODER |= 
        GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1;

    USART2->BRR = 1666;                 // 2 * 8000000 / 9600 = 1666
    USART2->CR1 |= USART_CR1_OVER8;     // 
    USART2->CR1 |= USART_CR1_TE;        // Включаем TX
    USART2->CR1 |= USART_CR1_RE;        // Включаем RX
    USART2->CR1 |= USART_CR1_UE;        // Включаем USART
}

void usart_transmit(uint8_t data)
{
    USART2->TDR = data;
    while(!(USART2->ISR & USART_ISR_TC));
}

int usart_receive(void)
{
    (void)USART2->RDR;
    while(!(USART2->ISR & USART_ISR_RXNE));
    return USART2->RDR;
}

int main(void)
{
    usart_init();
    systick_init(800);

    printf("Test\n");
    printf("Choose test number\n");
    printf("\t1. Test SW1-SW4. Set S1=0 S2=0 before test\n");
    printf("\t2. Test SB1-SB4. Set S1=0 S2=0 before test\n");
    printf("\t3. Test LEDs.    Set S1=0 S2=1 before test\n");
    printf("\t4. Test POT1, POT2. Set S1=0 S2=1 S3=0 S4=0 before test\n");
    printf("\t5. Test keyboard. Set S1=0 S2=1 before test\n");
    printf("\t6. Test 7 segment. Set S1=1 S2=0 before test\n");
    printf("\t7. Test LCD. Set S1=1 S2=1 before test\n");

    int n = 0;
    //scanf("Test: %d\n", &n);
    n = usart_receive() - '0';
    printf("Test %d\n", n);
    switch (n)
    {
        case 1:
            test_sw();
            break;
        case 2:
            test_sb();
            break;
        case 3:
            test_leds();
            break;
        case 4:
            test_pots();
            break;
        case 5:
            test_keyboard();
            break;
        case 6:
            test_7seg();
            break;
        case 7:
            test_lcd();
            break;
        default:
            break;
    }

    for(;;)
    {
        
    }
}

int stdin_getchar(void)
{
    return usart_receive();
}

int stdout_putchar(int ch)
{
    usart_transmit(ch);
    return ch;
}

void SysTick_Handler(void)
{
    systick_interrupt();
}
