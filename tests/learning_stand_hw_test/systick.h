/**
  ******************************************************************************
  * \file    systick.h
  * \author  Александр Смирнов
  * \version 1.1.0
  * \date    02.01.2021
  * \brief   Функции для формирования временных задержек с помощью SysTick
  ******************************************************************************
*/

#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include <stdint.h>

/**
  * \brief  Инициализация системного таймера
  * \param  ticks - количество "тиков" между прерываниями
  * \retval Нет
  * \note   Таймер SysTick тактируется HCLK, поэтому, например, для формирования
  *         разрешения таймера в 1 мс при HCLK=8МГц, необходимо вызвать
  *         функцию с параметров 8МГц/1кГц = 8000.
  */
void systick_init(uint32_t ticks);

/**
  * \brief  Возвратить код счетчика
  * \param  Нет
  * \retval Количество интервалов прошедших с инициализации
  */
uint32_t systick_get_tick(void);

/**
  * \brief  Программная задержка
  * \param  ticks - количество "тиков" задержки
  * \retval Нет
  */
void systick_delay(uint32_t ticks);

/**
  * \brief  Обработчик прерывания SysTick
  * \param  Нет
  * \retval Нет
  * \note   Должен вызваться в функции SysTick_Handler
  */
void systick_interrupt(void);

#endif /* __SYSTICK_H__ */
