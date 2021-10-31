  @ Использовать синтаксис UAL
  .syntax unified
  @ Процессор cortex-m0
  .cpu cortex-m0
  @ Набор команд Thumb
  .thumb

  .align

  @ Начальный адрес регистров модуля RCC
  .equ RCC_BASE,    0x40021000
  @ Адрес регистра AHBENR
  .equ RCC_AHBENR,  RCC_BASE + 0x14

  @ Начальный адрес регистров модуля GPIOC
  .equ GPIOC_BASE,  0x48000800
  @ Адрес регистра MODER
  .equ GPIOC_MODER, 0x48000800 + 0x00
  @ Адрес регистра ODR
  .equ GPIOC_ODR,   0x48000800 + 0x14

  @ Макроопределение с длительностью задержки
  .equ DELAY, 1000000

  .section .text
  .type start, %function
start:
  @ Инициализация стека
  ldr   r0, =_estack
  mov   sp, r0
  @ Включить тактирование порта C
  ldr   r0, =RCC_AHBENR     @ Загрузить адрес регистра RCC_AHBENR в r0
  ldr   r1, =(1 << 19)      @ Загрузить маску порта C в r1
  str   r1, [r0]            @ Сохранить r1 по адресу r0

  ldr   r0, =GPIOC_MODER    @ Загрузить адрес регистра GPIOC_MODER в r0
  ldr   r1, =0x01           @ Загрузить код 0x01 в r1
  str   r1, [r0]            @ Сохранить r1 по адресу r0

  @ Основной цикл программы
main_loop:
  @ Записать 1 в порт данных
  ldr   r0, =GPIOC_ODR
  ldr   r1, =0x01
  str   r1, [r0]

  @ Вызвать подпрограмму временной задержки
  bl    delay

  @ Записать 1 в порт данных
  ldr   r0, =GPIOC_ODR
  ldr   r1, =0x00
  str   r1, [r0]

  @ Вызвать подпрограмму временной задержки
  bl    delay

  @ Безусловный переход на метку main_loop
  b     main_loop

  @ Подпрограмма программной временной задержки
delay:
  ldr   r0, =DELAY
delay_loop:
  subs  r0, r0, #1
  bne   delay_loop
  bx    lr

  @ Указание на секцию с таблицей векторов прерываний
  .section .isr_vector,"a",%progbits

  @ Таблица векторов прерываний
vector_tables:
  .word  _estack
  .word  start
