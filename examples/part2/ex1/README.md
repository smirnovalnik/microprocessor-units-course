# Практическое занятие №1

## Цель

Целями практического занятия являются:
* знакомство с языком программирования C
* знакомство со способами обращения к регистрам специальных фукнций
* изучение порта ввода/вывода

## Режим _Учебного стенда_ и функциональная схема

Для выполнения задач переключатели _S1_ и _S2_ должны быть установлены в положение _0_ на учебном стенде.
При этом должен загореться светодиод LED1 _While LED_, обозначающий режим стенда номер _0_.

![ ](../../../img/lab1_ex1-4_sch.png)

## Описание задач

На практическом занятие решаются четыре задачи:

* `gpio_cmsis` - _Включение светодиода_
    Простейшая программа для включения одного светодиода.
* `gpio_raw_regs` - _Включение светодиода по абсолютным адресам_
    Программа эквивалентная программе `gpio_cmsis`, но без использования библиотеки CMSIS.
* `gpio_toggle` -  _Управление светодиода переключателем_
    В этой программе добавляется чтение порта для изменения состояния светодиода.
* `blinking_led` - _Мигающий светодиод_
    Периодическое включение и выключение светодиода в зависимости от состояния переключателя.