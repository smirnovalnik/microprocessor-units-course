; \file    main.s
; \author  Александр Смирнов
; \version 1.0.0
; \date    1.02.2022
; \brief   Пример программы для лабораторной работы №4 на языке Ассемблер
;          для учебного стенда на базе STM32F072RBT6
;          в среде разработки Keil uVision 5.
;          Условие:
;          Разработать программу, которая при нажатии на клавишу SB1
;          включает светодиод LED1.
;          Программа работает в режиме 0 учебного стенда (S1 = 0, S2 = 0).

; Макроопределения
; Начальный адрес регистров модуля RCC
RCC_BASE    EQU     0x40021000
; Адрес регистра AHBENR
RCC_AHBENR  EQU     RCC_BASE + 0x14

; Начальный адрес регистров модуля GPIOC
GPIOC_BASE  EQU     0x48000800
; Адрес регистра MODER
GPIOC_MODER EQU     GPIOC_BASE + 0x00
; Адрес регистра ODR
GPIOC_ODR   EQU     GPIOC_BASE + 0x14

; Начальный адрес регистров модуля GPIOB
GPIOB_BASE  EQU     0x48000400
; Адрес регистра PUPDR
GPIOB_PUPDR EQU     GPIOB_BASE + 0x0C
; Адрес регистра IDR
GPIOB_IDR   EQU     GPIOB_BASE + 0x10

; Секция с программой
            AREA    PROGRAM, CODE, READONLY ; Указание на расположение программы в памяти
            ENTRY
            ALIGN

Reset_Handler
            ; Включить тактирование портов B и C
            LDR   R0, =RCC_AHBENR     ; Загрузить адрес регистра RCC_AHBENR в R0
            LDR   R1, =((1 << 19) :OR: (1 << 18)) ; Загрузить маску портов B и C в R1
            STR   R1, [R0]            ; Сохранить R1 по адресу R0

            ; Настроить линию PC0(LED1) на вывод
            LDR   R0, =GPIOC_MODER    ; Загрузить адрес регистра GPIOC_MODER в R0
            LDR   R1, =0x01           ; Загрузить код 0x01 в R1
            STR   R1, [R0]            ; Сохранить R1 по адресу r0

            ; Включение подтягивающих резисторов для PB4(SB1)
            LDR   R0, =GPIOB_PUPDR    ; Загрузить адрес регистра GPIOB_PUPDR в R0
            LDR   R1, =(1 << 8)       ; Загрузить маску в R1
            STR   R1, [R0]            ; Сохранить R1 по адресу R0

            ; Основной цикл программы
Main_Loop
            ; Прочитать состояние порта B
            LDR   R0, =GPIOB_IDR
            LDR   R1, [R0]
            ; Замаскировать PB4(SB1)
            LDR   R2, =(1 << 4)
            ANDS  R1, R1, R2
            BNE   Led_Off

            ; Включить PC0(LED1)
            LDR   R0, =GPIOC_ODR
            LDR   R1, =0x01
            STR   R1, [R0]
            B     Main_Loop

Led_Off     ; Выключить PC0(LED1)
            LDR   R0, =GPIOC_ODR
            LDR   R1, =0x00
            STR   R1, [R0]
            B     Main_Loop

; Секция с таблицей векторов прерываний
            AREA    RESET, DATA, READONLY ; Указание на расположение векторов прерываний
            EXPORT  __Vectors   ; Метка __Vectors экспортируется из файла компоновщика
__Vectors
            DCD     0x20004000     ; Начало стека
            DCD     Reset_Handler  ; Вектор сброса

            END                    ; Команда транслятору об окончании текста программы