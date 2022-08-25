# Язык C во встраиваемых системах

- [Язык C во встраиваемых системах](#язык-c-во-встраиваемых-системах)
  - [Обращение к регистрам специальных функций](#обращение-к-регистрам-специальных-функций)
    - [Способ 1](#способ-1)
    - [Способ 2](#способ-2)
    - [Способ 3](#способ-3)
  - [Обработка прерываний в Cortex-M](#обработка-прерываний-в-cortex-m)
  - [Ассемблерные вставки](#ассемблерные-вставки)

## Обращение к регистрам специальных функций

### Способ 1

```c
#define GPIOC_ODR       (*((volatile unsigned int *)(0x48000800 + 0x14)))
...
GPIOC_ODR = GPIOC_ODR | 0x00000001;/* Установить 1 в PC0 */
```

### Способ 2

```c
#include <stm32f0xx.h>
...
GPIOC->ODR = GPIOC->ODR | 0x00000001;/* Установить 1 в PC0 */
```

### Способ 3

```c
#include <stm32f0xx_hal.h>
...
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET); /* Установить 1 в PC0 */
```

## Обработка прерываний в Cortex-M

В файле `startup_stm32f072xb.s` ищем название вектора обработки прерывания:

```asm
DCD     ADC1_COMP_IRQHandler           ; ADC1, COMP1 and COMP2
DCD     TIM1_BRK_UP_TRG_COM_IRQHandler ; TIM1 Break, Update, Trigger and Commutation
DCD     TIM1_CC_IRQHandler             ; TIM1 Capture Compare
DCD     TIM2_IRQHandler                ; TIM2
DCD     TIM3_IRQHandler                ; TIM3
```

В файлах разработчика, например в main.c, создаем функцию с этим названием:

```c
/* Подпрограмма обработчик прерывания по ADC1 */
void ADC1_COMP_IRQHandler(void)
{
    ...
}
/* Подпрограмма обработчик прерывания по TIM2 */
void TIM2_IRQHandler(void)
{
    ...
}
```

## Ассемблерные вставки

```c
/* Для IDE Keil uVision */
__asm void add(int x1, int x2, int x3)
{
    ADDS R0, R0, R1
    ADDS R0, R0, R2
    BX LR
}

int swap32(int i)
{
    int res;
    __asm {
        REVSH res, i
    }
    return res;
}

__asm("WFI"); /* Выполнение одной команды */
```
