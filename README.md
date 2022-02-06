# Курс "Микропроцессорные устройства"

## Перечень директорий репозитория

* `docs` - документация на микроконтроллер и на отладочную плату
    * `c_language` - шпаргалка по ассемблеру ARM и языку C
    * `learning_stand` - документация (спецификации, схемы электрические принципиальные, сборочные чертежи) на _Учебный стенд_
    * `mcu` - документация (технические описания, руководства и т.д.) на МК _STM32F072RBT6_
* `examples` - примеры лабораторных работ и задачи для практических занятий
    * `part1` - для первой части курса
    * `part2` - для второй части курса
        * `lab1` - пример задачи _Лабораторной работы №1_ с использованием портов ввода/вывода и АЦП
        * `lab2` - пример задачи _Лабораторной работы №2_ с использованием портов ввода/вывода и таймера
        * `lab3` - пример задачи _Лабораторной работы №2_ с использованием портов ввода/вывода и интерфейса SPI
* `hardware` - исходные файлы проекта _Учебный стенд_ в Altium Designer
* `img` - различные картинки используемые в README файлах
* `lectures` - слайды и тексты программ использованные на лекциях
* `tests` - проекты для теста аппаратного обеспечения _Учебного стенда_
* `templates` - шаблоны проектов

## Установка компонентов

Установка всех компонентов будет происходить в командной стройке.

### Windows

Открыть командную строку в режиме администратора.

* Установить пакетный менеджер __Chocolatey__

    Пакетный менеджер позволит быстро устанавливать необходмые программы не прибегая к поиску установочных файлов в интернете.

    Установка выполняется командой:
    ```bash
    Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))
    ```

    Проверить установку следует командой:
    ```bash
    choco --version
    ```
    Если установка прошла успешно, то в командной строке напечатается версия программы.

* Установить текстовый редактор с подсветкой синтаксиса __Visual Studio Code__:

    Установить текстовый редактор:
    ```bash
    choco install vscode
    ```

    Установить расширениe для работы с кодом на языке C/C++:
    ```bash
    code --install-extension ms-vscode.cpptools
    ```

    Установить расширение для визуализации отладки процессоров ARM Cortex:
    ```
    code --install-extension marus25.cortex-debug
    ```

    Установить расширение для подсветки систаксиса ассемблера ARM:
    ```
    code --install-extension dan-c-underwood.arm
    ```

    Установить расширение для подстветки синтаксиса скрипта компоновщика:
    ```
    code --install-extension zixuanwang.linkerscript
    ```

* Установить кросс-компилятор __arm-none-eabi-gcc__:

    ```bash
    choco install gcc-arm-embedded
    ```

* Установить утилиту __make__:

    ```bash
    choco install make
    ```

* Установить __openocd__:

    ```bash
    choco install openocd
    ```

* Установить __qemu__:

    ```bash
    choco install qemu
    ```

## MacOS

```bash
sudo code --install-extension ms-vscode.cpptools

brew tap ArmMbed/homebrew-formulae
brew install arm-none-eabi-gcc

brew install qemu
```
