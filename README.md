##

Установка всех компонентов будет происходить в командной стройке.

## Windows ##

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

## MacOS ##

```
sudo code --install-extension ms-vscode.cpptools

brew tap ArmMbed/homebrew-formulae
brew install arm-none-eabi-gcc

brew install qemu
```