; \file    main.s
; \author  Александр Смирнов
; \version 1.0.0
; \date    23.08.2022
; \brief   Программа на языке Ассемблер (ARM) для учебного стенда на базе
;          STM32F072RBT6 в среде разработки Keil uVision 5.
;          Примеры использования команд управления и контроля.

            ; Секция с программой
            AREA    PROGRAM, CODE, READONLY
            ALIGN
            ENTRY

Reset_Handler


            ; Условный оператор
            ; Псевдокод:
            ; if (counter > 42)
            ;   counter = 0
            ; else
            ;   counter = counter + 1
            ; Пусть переменная counter находится в R0
            CMP  R0, #42        ; Сравнение с числом 42
            BLE  else_branch    ; Если меньше или равно, то переход else_branch
            MOVS R0, #0         ; counter = 0
            B    if_done        ; Переход на if_done
else_branch
            ADDS R0, R0, #1     ; counter = counter + 1
if_done


            ; Цикл
            ; Псевдокод:
            ; sum = 0
            ; i = 0
            ; while (i < 4)
            ;   sum = sum + i
            ;   i = i + 1
            ; Пусть sum находится в R0, i в R1
            MOVS R0, #0         ; sum = 0
            MOVS R1, #0         ; i = 0
loop1
            CMP  R1, #4         ; Сравнение i с числом 4
            BGE  loop1_done     ; Если меньше, то переход loop1_done

            ADDS R0, R0, R1     ; sum = sum + i
            ADDS R1, R1, #1     ; i = i + 1
            B    loop1          ; повтор цикла
loop1_done


            ; Простой цикл
            ; Пусть количество повторов находится в R0
            MOVS R0, #5         ; Инициализация счетчика цикла
loop2
            NOP                 ; Здесь нужно вставить полезные команды
            SUBS R0, R0, #1     ; Декремент счетчика цикла
            BNE  loop2          ; Если не ноль, то переход loop2

            ; Опрос (polling) состояния регистра
            LDR  R0, =0x20000000 ; Загрузить адрес ячейки памяти или регистра
            MOVS R2, #0x10       ; Маска для бита 4 - 10000
loop3
            LDR R1, [R0]        ; Прочитать состояние регистра
            TST R1, R2          ; Вычислить R1 И 0x4
            BEQ loop3           ; Если ноль, то прочитать еще раз


            ; Таблица переходов (многозначный выбор)
            ; Пусть номер случая находится в R0
            CMP  R0, #3         ; Сравнение с максимальным значением
            BHI  default_case   ; Если больше, то переход default_case
            MOVS R2, #4         ; Умножение номер на 4
            MULS R0, R2, R0     ; (размер адреса)
            LDR  R1,=BranchTable; Получение базового адреса таблицы переходов
            LDR  R2, [R1, R0]   ; Загрузка адреса перехода со смещением
            BX   R2             ; Переход
            ALIGN 4             ; Выравнивание
            ; Таблица переходов с адресами для каждого случая
BranchTable
            DCD  Case0
            DCD  Case1
            DCD  Case2
            DCD  Case3
default_case
            NOP                     ; Команды для случая по умолчанию
            B    switch_done
Case0
            NOP                     ; Команды для случая ‘0’
            B    switch_done
Case1
            NOP                     ; Команды для случая ‘1’
            B    switch_done
Case2
            NOP                     ; Команды для случая ‘2’
            B    switch_done
Case3
            NOP                     ; Команды для случая ‘3’
            B    switch_done
switch_done


Stop        B    Stop         ; Бесконечный цикл


            ALIGN 4

            ; Секция с таблицей векторов прерываний
            AREA    RESET, DATA, READONLY ; Указание на расположение векторов прерываний
            EXPORT  __Vectors   ; Метка __Vectors экспортируется из файла компоновщика
__Vectors
            DCD     0x20004000     ; Начало стека
            DCD     Reset_Handler  ; Вектор сброса

            END                 ; Команда транслятору об окончании текста программы
