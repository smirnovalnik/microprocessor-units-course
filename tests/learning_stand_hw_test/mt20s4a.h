/*
Драйвер ЖКИ модуля MT20S4A.
20 x 4 символов.
Графический контроллер КБ1013ВГ6(HD44780).
4х разрядная шина данных.
*/

#ifndef _MT20S4A_H_
#define _MT20S4A_H_

#include <stm32f0xx.h>

//#define F_CPU 8000000UL  /*Частота шины ЦП - 8MHz*/
//#include <util/delay.h>

#define LCD_WIDTH 20 /*Длина дисплея в символах.*/
#define LCD_HEIGHT 4 /*Высота дисплея в символах.*/

/*Определения портов.*/
#define DATA        (GPIOC->ODR)	/*Регистр порта данных.*/
//#define DDATA       (GPIOC->MODER)    /*Регистр направления передачи порта данных.*/
#define CONTROL 	(GPIOC->ODR)	/*Регистр управляющего порта.*/
//#define DCONTROL 	(GPIOC->MODER)	/*Регистр направления передачи управляющего порта.*/

#define E	(14)	/*Сигнала строба.*/
#define RW	(13)	/*Сигнал чтения записи.*/
#define RS	(12)	/*Выбор регистра приемника - команды/данные.*/

//#define BF			(PINB & (1 << PB3))			/*Флаг готовности.*/

#define E_SET() 	CONTROL |= (1 << E)		/*Установка сигнала строба.*/
#define E_CLR() 	CONTROL &= ~(1 << E)	/*Сброс сигнала строба.*/
#define RW_SET() 	CONTROL |= (1 << RW)	/*Установка сигнала чтение/запись.*/
#define RW_CLR()	CONTROL &= ~(1 << RW) 	/*Сброс сигнала чтение/запись.*/
#define RS_DR() 	CONTROL |= (1 << RS)	/*Обращение к регистру данных.*/
#define RS_IR() 	CONTROL &= ~(1 << RS)	/*Обращение к регистру команд.*/

/*Определения временных задержек для частоты шины 8МГц.*/
#define NOP() _delay_us(1) /*При 8 МГц цикл равен 125нс.*/

//#define READ_BF	//чтение флага занятости

/*Настройки ЖКИ.*/
#define ID 	1			/*Инкремент(1)/декремент(0) счетчика адреса*/
#define S 	0			/*Разрешение(1)/запрет(0) сдвига экрана.*/
#define D 	1			/*Включение(1) / выключение(0) дисплея.*/
#define C	0			/*Включение(1) / выключение (0) курсора в виде подчеркивания.*/
#define B	0			/*Включение(1) / выключение (0) курсора в виде мерцающего знакоместа.*/
#define SC	0			/*Сдвиг экрана(1) / курсора(0).*/
#define RL	1			/*Направление сдвига вправо(1)/влево(0).*/
#define DL	1			/*Ширина шины данных 8бит(1) /4бита(0).*/
#define N	1			/*Число строк две(1)/одна строка(0), для данного индикатора N = 1.*/
#define F	0			/*Размер символа 5x10(1)/5x8(0), для данного индикатора F = 0.*/
#define P	1			/*Номер страницы знакогенератора.*/

/*Коды символов знакогенератора.*/
//#define CURSOR 		0xB2     /*Символ курсора.*/
#define CURSOR 		0xB3
#define UP_ARROW	0x93
#define DOWN_ARROW	0x92

/*Прототипы функций.*/
/*Функция инициализации ЖКИ.*/
void init_disp(void);
/*Функция выключения ЖК дисплея.*/
void disp_off(void);
/*Функция включения ЖК дисплея.*/
void disp_on(void);
/*Функция вывода на дисплей символа.*/
void put_char(unsigned char ch, unsigned char pos, unsigned char line);
/*Функция вывода на дисплей строки символов с переносом строки.*/
void put_str(const char s[],unsigned char pos, unsigned char line);
/*Функция вывода строки символов на одной строке без переноса.*/
void put_str_ln(const char s[], unsigned char pos, unsigned char line);
/*Функция зачисти символа.*/
void clr_char(unsigned char pos, unsigned char line);
/*Функция зачистки строки символов.*/
void clr_str(unsigned char pos, unsigned char line, unsigned char length);
/*Функция очистки дисплея.*/
void clr_disp(void);

#endif
