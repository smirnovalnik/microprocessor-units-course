; \file    main.s
; \author  Александр Смирнов
; \version 1.0.0
; \date    23.08.2022
; \brief   Программа на языке Ассемблер (ARM) для учебного стенда на базе
;          STM32F072RBT6 в среде разработки Keil uVision 5.
;          Примеры использования команд ветвления.

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
            BLE  Else_Branch    ; Если меньше или равно, то переход Else_Branch
            MOVS R0, #0         ; counter = 0
            B    If_Done        ; Переход на If_Done
Else_Branch
            ADDS R0, R0, #1     ; counter = counter + 1
If_Done


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
Loop1
            CMP  R1, #4         ; Сравнение i с числом 4
            BGE  Loop1_Done     ; Если меньше, то переход Loop1_Done

            ADDS R0, R0, R1     ; sum = sum + i
            ADDS R1, R1, #1     ; i = i + 1
            B    Loop1          ; повтор цикла
Loop1_Done


            ; Простой цикл
            ; Пусть количество повторов находится в R0
            MOVS R0, #5         ; Инициализация счетчика цикла
Loop2
            NOP                 ; Здесь нужно вставить полезные команды
            SUBS R0, R0, #1     ; Декремент счетчика цикла
            BNE  Loop2          ; Если не ноль, то переход Loop2

            ; Опрос (polling) состояния регистра
            LDR  R0, =0x20000000 ; Загрузить адрес ячейки памяти или регистра
            MOVS R2, #0x10       ; Маска для бита 4 - 10000
Loop3
            LDR R1, [R0]        ; Прочитать состояние регистра
            TST R1, R2          ; Вычислить R1 И 0x4
            BEQ Loop3           ; Если ноль, то прочитать еще раз


            ; Таблица переходов (многозначный выбор)
            ; Пусть номер случая находится в R0
            CMP  R0, #3         ; Сравнение с максимальным значением
            BHI  Default_Case   ; Если больше, то переход Default_Case
            MOVS R2, #4         ; Умножение номер на 4
            MULS R0, R2, R0     ; (размер адреса)
            LDR  R1,=Branch_Table; Получение базового адреса таблицы переходов
            LDR  R2, [R1, R0]   ; Загрузка адреса перехода со смещением
            BX   R2             ; Переход
            ALIGN 4             ; Выравнивание
            ; Таблица переходов с адресами для каждого случая
Branch_Table
            DCD  Case0
            DCD  Case1
            DCD  Case2
            DCD  Case3
Default_Case
            NOP             ; Команды для случая по умолчанию
            B    Switch_Done
Case0
            NOP             ; Команды для случая ‘0’
            B    Switch_Done
Case1
            NOP             ; Команды для случая ‘1’
            B    Switch_Done
Case2
            NOP             ; Команды для случая ‘2’
            B    Switch_Done
Case3
            NOP             ; Команды для случая ‘3’
            B    Switch_Done
Switch_Done


Stop        B    Stop       ; Бесконечный цикл

            ALIGN

            ; Секция с таблицей векторов прерываний
            AREA    RESET, DATA, READONLY ; Указание на расположение векторов прерываний
            EXPORT  Vectors         ; Экспорт метки Vectors для компоновщика
Vectors
            DCD     0x20004000      ; Начало стека (последний адрес ОЗУ)
            DCD     Reset_Handler   ; Вектор сброса (начало программы)

            END                     ; Команда транслятору об окончании текста программы