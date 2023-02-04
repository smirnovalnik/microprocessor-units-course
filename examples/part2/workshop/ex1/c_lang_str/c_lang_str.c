/**
  ******************************************************************************
  * \file    main.c
  * \author  Александр Смирнов
  * \version 1.0.0
  * \date    4.02.2023
  * \brief   Программа на языке C для учебного стенда на базе
  *          STM32F072RBT6 в среде разработки Keil uVision 5.
  *          Подключение библиотек поддержки МК STM32F072RBT6 осуществляется
  *          средствами IDE Keil через Run-Time Environment (RTE).
  *          В программе показаны основы синтаксиса языка C.
  ******************************************************************************
  */

#include "stdio.h"
#include "EventRecorder.h"

int slen(char *s)
{
    int len = 0;

    while (*s != '\0')
    {
        len++;
        s++;
    }

    return len;
}

void swap(char* a, char* b)
{
    char tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverse(char *s)
{
    char *p = s + slen(s) - 1;

    while (s < p)
    {
        swap(s, p);
        s++;
        p--;
    }
}

/* Функция main - точка входа в программу. */
int main(void)
{
    EventRecorderInitialize(EventRecordAll, 1);

    printf("Hello, world!\n");

    char str1[] = "Hello again";
    printf("Another string: %s\n", str1);

    int a[] = {-2, -1, 0, 1, 2};
    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", a[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        printf("a[%d]=%d\n", i, a[i]);
    }

    char str2[] = "reverse of the string";
    printf("str2: %s\n", str2);
    reverse(str2);
    printf("str2: %s\n", str2);

    while(1);
}
