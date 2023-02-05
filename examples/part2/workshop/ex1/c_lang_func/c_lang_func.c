/**
  ******************************************************************************
  * \file    c_lang_func.c
  * \author  Александр Смирнов
  * \version 1.0.0
  * \date    3.02.2023
  * \brief   Программа на языке C для учебного стенда на базе
  *          STM32F072RBT6 в среде разработки Keil uVision 5.
  *          Подключение библиотек поддержки МК STM32F072RBT6 осуществляется
  *          средствами IDE Keil через менеджер пакетов Run-Time Environment (RTE).
  *          В программе показано использование функций (подпрограмм).
  ******************************************************************************
  */

/* Простейшая функция на языке C.
   Функция прибавляет к аргументу n число 2 и возвращает получившееся число.
  */
int add2(int n)
{
    int tmp = n + 2;
    return tmp;
}

int power(int base, int n)
{
    int result = 1;
    for (int i = 0; i < n; i++)
    {
        result = result * base;
    }

    return result;
}

int rpower(int base, int n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return base * rpower(base, n - 1);
    }
}

int find_min(int a[], int n)
{
    int min = a[0];

    for (int i = 0; i < n; i++)
    {
        if (a[i] < min)
        {
            min = a[i];
        }
    }

    return min;
}

int count_number(int a[], int len, int n)
{
    int cnt = 0;

    for (int i = 0; i < len; i++)
    {
        if (a[i] == n)
        {
            cnt = cnt + 1;
        }
    }

    return cnt;
}

/* Функция main - точка входа в программу. */
int main(void)
{
    /* Объявление и инициализация переменных */
    int a = 1;
    int b = 2;
    int c;

    /* Вызов функций */
    c = add2(a);
    c = add2(5);

    c = power(2, 5);
    c = power(10, b);

    c = rpower(2, 5);
    c = rpower(10, b);

    /* Объявление и инициализация массива */
    int arr[] = {4, 8, -10, 12, 18, 24, -8, 0, 1, 0};

    c = find_min(arr, 10);
    c = count_number(arr, 10, 0);
}
