; Шаблон программы и проекта на языке UAL ассемблер для процессора Cortex-M0

; Секция с таблицей векторов прерываний
            AREA    RESET, DATA, READONLY
            EXPORT  __Vectors   ; Метка __Vectors экспортируется из файла компоновщика
__Vectors
            DCD     0x20004000     ; Начало стека
            DCD     Reset_Handler  ; Вектор сброса


; Секция с константами
            AREA    CONST, DATA, READONLY
myconst     DCD     0xAA


; Секция с данными
            AREA    RWDATA, DATA, READWRITE
mydata      DCD     43


; Макроопределения
mydef       EQU     17


; Секция с програмой
            AREA    PROGRAM, CODE, READONLY
            ENTRY

Reset_Handler
            ; Пример программы копирования константы myconst
            ; в ячейку памяти mydata
            LDR     R0, =myconst
            LDR     R1, [R0]
            LDR     R2, =mydata
            STR     R1, [R2]
            
            ; Пример программы копирования mydef
            ; в ячейку памяти mydata + 4
            LDR     R0, =mydef
            ADDS    R2, R2, #4
            STR     R0, [R2]

STOP
            B  STOP             ; Бесконечный цикл

            END                 ; Конец программы