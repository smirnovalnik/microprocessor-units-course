; \file    main.s
; \author  Александр Смирнов
; \version 1.0.0
; \date    19.08.2022
; \brief   Программа на языке Ассемблер (ARM) для учебного стенда на базе
;          STM32F072RBT6 в среде разработки Keil uVision 5.
;          Дан массив двухбайтовых чисел в дополнительном коде со знаком.
;          Начальный адрес массива – 0х20000000. Количество элементов – 10.
;          Найти максимальное число в массиве. Результат положить в ячейку
;          с адресом 0x20000020.

            AREA    DATA, DATA, READONLY
ARR         DCW     42, 16, 5, 23, 19, 84, 19, 37, 20, 12

; Макроопределения
ARR_LEN     EQU     10                          ; Длина массива
ARR_ADDR    EQU     0x20000000
MAX_ADDR    EQU     0x20000020

; Секция с программой
            AREA    PROGRAM, CODE, READONLY
            ALIGN
            ENTRY

Reset_Handler
            LDR     R0, =ARR
            LDR     R1, =ARR_ADDR
            MOVS    R2, #0
Copy_Loop   LDRH    R3, [R0, R2]
            STRH    R3, [R1, R2]
            ADDS    R2, R2, #2
            CMP     R2, #(2 * ARR_LEN)
            BNE     Copy_Loop

; Поиск максимального числа
            LDR     R0, =ARR_ADDR
            MOVS    R1, #0
            LDRH    R2, [R0]

Max_Loop    ADDS    R1, R1, #2
            LDRH    R3, [R0, R1]
            CMP     R2, R3
            BGT     More
            MOV     R2, R3
More        CMP     R1, #(2 * (ARR_LEN - 1))
            BNE     Max_Loop

            LDR     R0, =MAX_ADDR
            STR     R2, [R0]

Stop        B  Stop             ; Бесконечный цикл

; Секция с таблицей векторов прерываний
            AREA    RESET, DATA, READONLY ; Указание на расположение векторов прерываний
            EXPORT  Vectors         ; Экспорт метки Vectors для компоновщика
Vectors
            DCD     0x20004000      ; Начало стека (последний адрес ОЗУ)
            DCD     Reset_Handler   ; Вектор сброса (начало программы)

            END                     ; Команда транслятору об окончании текста программы
