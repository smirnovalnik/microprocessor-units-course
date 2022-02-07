# Практическое занятие №2

## Цель

Целями практического занятия являются:
* знакомство с языком программирования C
* изучения модуля АЦП
* изучение алгоритма антидребезга

## Режим _Учебного стенда_ и функциональная схема

Для выполнения задач переключатели _S1_ и _S2_ должны быть установлены в положение _0_ на учебном стенде.
При этом должен загореться светодиод LED1 _While LED_, обозначающий режим стенда номер _0_.

![ ](../../../img/lab1_ex1-4_sch.png)

## Описание задач

На практическом занятие решаются две задачи:

* `gpio_debouncing` - _Антидребезг кнопки_
    Программа подсчета количества нажатий кнопки. Нажатия кнопки реализовано с защитой от дребезга
    контактов.
* `adc_poll` - _Чтение АЦП программным опросом_
    Программа измерения состояния потециометров _POT1_ и _POT2_ с помощью АЦП в режиме опроса.