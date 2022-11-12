# Microprocessor Units Course

The Department of [Industrial Electronics](https://mpei.ru/Structure/Universe/ire/structure/ie/Pages/default.aspx) of [Moscow Power Engineering Institute](https://mpei.ru/).

![ ](../../img/mpei_logo.jpg) ![ ](../../img/logo_ie.jpg)

## Content

- [Microprocessor Units Course](#microprocessor-units-course)
  - [Content](#content)
  - [Instructors](#instructors)
  - [Course Description](#course-description)
  - [Learning Objectives](#learning-objectives)
  - [Prerequisites](#prerequisites)
  - [Course Structure](#course-structure)
    - [Part 1](#part-1)
    - [Part 2](#part-2)
    - [Lectures](#lectures)
    - [Workshops](#workshops)
    - [Labs](#labs)
    - [Test and Exam](#test-and-exam)
  - [Course Materials](#course-materials)
    - [Clone the repository](#clone-the-repository)
  - [List of Repository Directories](#list-of-repository-directories)
  - [Textbooks](#textbooks)
  - [Useful Links](#useful-links)
  - [Learning Stand](#learning-stand)
  - [Installing and Configuring Development Tools](#installing-and-configuring-development-tools)
    - [Keil uVision5](#keil-uvision5)
    - [vscode gcc](#vscode-gcc)
      - [Windows](#windows)
      - [Linux](#linux)
      - [macOS](#macos)
      - [vscode text editor](#vscode-text-editor)
  - [Feedback](#feedback)

## Instructors

Aleksandr Smirnov

Email: [smirnovalnik@mpei.ru](mailto:smirnovalnik@mpei.ru)

Workshops and labs are carried out by instructors of the graduating departments.

## Course Description

The course is intended for fourth-year students of the Faculty of Electronic Engineering.
The course introduces the basics of microprocessor technology, programming microcontrollers in Assembly and C languages.

## Learning Objectives

The objectives of the first part of the course are:

- study of the principles of microprocessor devices
- learning Assembly programming language and its application for embedded systems

The objectives of the second part of the course are:

- study of peripherals of the _STM32F072RBT6_ microcontroller unit
- learning C programming language and its application for embedded  systems

## Prerequisites

The student must have programming skills at least in one of high-level programming languages, know the basics of analog and digital circuitry.

## Course Structure

The course consists of two parts: fall semester (part 1) and spring semester (part 2).

### Part 1

- Lectures
  - Lecture #1: Principles of Digital Control Systems and Digital Signals Processing
  - Lecture #2: Structure of Microprocessor System
  - Lecture #3: Memory in Microprocessor System (part 1)
  - Lecture #4: Memory in Microprocessor System (part 2)
  - Lecture #5: Input/Output Devices
  - Lecture #6: Instruction Set of Central Processor Unit
  - Lecture #7: Structure of Central Processor Unit (part 1)
  - Lecture #8: Structure of Central Processor Unit (part 2)
  - Lecture #9: Interaction in Microprocessor System
  - Lecture #10: Interrupt Mode
  - Lecture #11: Direct Memory Access Mode
  - Lecture #12: Modular Principle of Microcontroller Unit
  - Lecture #13: Microcontroller System Modules
  - Lecture #14: Microcontroller Clock System
  - Lecture #15: General Purpose I/O Ports
  - Lecture #16: Features of Central Processors of Various Architectures
- Workshops
- Labs
  - Lab #1: Data Processing and Data Access Instructions
  - Lab #2: Branching and Calling Subroutine Instructions
  - Lab #3: Data Array
  - Lab #4: MCU General Purpose I/O Ports
- Test

### Part 2

- Lectures
  - Lecture #1: Structure of Microcontroller Unit
  - Lecture #2: Interaction of Central Processor Unit and Peripherals
  - Lecture #3: General Purpose I/O Ports
  - Lecture #4: Analog to Digital Converter
  - Lecture #5: Interrupt Handling
  - Lecture #6: General Purpose Timer-Counter
  - Lecture #7: Timer-Counter Output Compare Channels
  - Lecture #8: Timer-Counter Input Capture Channels
  - Lecture #9: Serial I/O
  - Lecture #10: Serial I/O: SPI
  - Lecture #11: Serial I/O: UART
  - Lecture #12: Serial I/O: I2C
  - Lecture #13: Serial I/O: CAN
  - Lecture #14: MCU Clock Subsystem
- Workshops
  - Practice #1: MCU I/O Ports
  - Practice #2: MCU Analog I/O
  - Practice #3: MCU Interrupt
  - Practice #4: MCU Real-Time Subsystem: Running LED
  - Practice #5: MCU Real-Time Subsystem: Dimming LED
  - Practice #6: MCU Serial I/O Subsystem: UART
  - Practice #7: MCU Serial I/O Subsystem: SPI, I2C
- Labs
  - Lab #1: MCU Analog I/O Subsystem
  - Lab #2: MCU Real-Time Subsystem
  - Lab #3: MCU Serial I/O Subsystem: UART
- Exam

### Lectures

The lectures study the theoretical issues of the operation of microprocessor systems, as well as some practical issues of programming these systems.

### Workshops

The workshops are conducted by instructors of the graduating departments.
The order of the workshops, the topics of the workshops and their content may differ from those given here at the discretion of the instructor.

### Labs

The labs are carried out by instructors of the graduating departments.
The order of the labs, the topics of the labs and their content may differ from those given here at the discretion of the instructor.

Performing labs involves preliminary self-preparation:
creating a project and writing the source code of the program.

Labs #1, #2, #3 of the first part can be performed on the simulator.
The rest of the work is carried out at the learning stand.

### Test and Exam

The first part of the course ends with a test, the second part ends with an exam.

## Course Materials

Course materials are hosted on [GitHub](https://github.com),
which is a large repository of programs (source codes)
under version control system `git`.

The repository is constantly updated and therefore it is recommended to pull the changes.

If you are not familiar with `git`, you can periodically download the project archive.

### Clone the repository

```bash
git clone https://github.com/smirnovalnik/microprocessor-units-course.git
```

## List of Repository Directories

- `docs` - documentation for the microcontroller and learning stand
  - `arm_official` - official documentation (technical descriptions, manuals, etc.) for the _ARM Cortex-M0_ processor
  - `asm_lang` - ARM assembly language cheat sheet
  - `c_lang` - C language cheat sheet
  - `learning_stand` - documentation (specifications, electrical circuit diagrams, assembly drawings) for _Learning Stand_
  - `mcu_st_official` - official documentation (technical descriptions, manuals, etc.) for _STM32F072RBT6_ MCU in English
  - `peripheral` - description of registers of special functions for _STM32F072RBT6_ MCU
  - `misc` - various useful documents
- `exam` - questions for credits and exams, examples of tickets
- `examples` - examples of labs and workshops
  - `part1` - for the first part of the course
    - `labs` - examples of labs
      - `lab1` - example of _Lab #1 Data access instructions. Data processing instructions_
      - `lab2` - example of _Lab #2 Branch instructions. Call subroutines instructions_
      - `lab3` - example of _Lab #3 Finding the largest number in an array. Sort array_
      - `lab4` - example of _Lab #4 Input/Output port. Flashing LED_
  - `part2` - for the second part of the course
    - `labs` - examples of labs
      - `lab1` - an example of _Lab #1 Analog input/output subsystem of MCU_
      - `lab2` - an example of _Lab #2 Real-time subsystem of MCU_
      - `lab3` - an example of _Lab #3 Serial input/output subsystem of MCU: SPI, UART, I2C_
    - `workshop` - examples analyzed in practical classes
      - `ex1` - examples of solving four practical tasks: _Turning on LED_, _Turning on LED by absolute addresses_, _LED switch control_, _Flashing LED_
      - `ex2` - examples of solving two practical tasks: _Reading ADC by software polling_, _Button anti-bounce_
      - `ex3` - examples of solving two practical problems: _External interrupts on I/O ports_, _Interrupt at the end of ADC conversion_
      - `ex4` - an example of solving a practical problem: _Running LED_
      - `ex5` - an example of solving a practical problem: _Regulating the brightness of LEDs using timer_
      - `ex6` - an example of solving a practical problem: _Connecting external Flash memory via SPI_
      - `ex7` - an example of solving practical problems: _Controlling LEDs via UART_
- `hardware` - source files for the _Learning Stand_ project in Altium Designer
- `img` - various images used in README files
- `lectures` - slides and program texts used in lectures
- `programs` - programs to install
- `tests` - _Learning Stands_ hardware tests
- `templates` - project templates

## Textbooks

- _Sarah L. Harris, David Harris "Digital Design and Computer Architecture, RISC-V Edition"_
- _Sarah L. Harris, David Harris "Digital Design and Computer Architecture, ARM Edition"_
- Ugryumov E. "Digital circuitry"_
- _Joseph Yiu "The Definitive Guide to ARM Cortex-M0 and Cortex-M0+ Processors 2nd Edition"_
- If you want to program C language you must read and **solve all exercises** in the textbook
_Brian Kernighan., Dennis Ritchie "The C Programming Language" 2nd edition._

## Useful Links

- [Page on stm32072rb from the manufacture](https://www.st.com/en/microcontrollers-microprocessors/stm32f072rb.html)
- [Page on stm32f072-disco from the manufacturer](https://www.st.com/en/evaluation-tools/32f072bdiscovery.html)

## Learning Stand

The learning stand consists of several boards with electronic components: evaluation board _STM32F072B-DISCO_, main board, LCD indicator, wireless data transmission module.

The main board contains actuators and input devices for the microprocessor controller. This board was developed at the Department of Industrial Electronics of MPEI.

The _STM32F072B-DISCO_ evaluation board contains the _STM32F072RBT6_ MCU under study, as well as the programmer _ST-LINK/V2_. The programmer allows you to load the program codes for the microcontroller unit, which are prepared in the PC, into the permanent memory of the MCU and then observe on the PC screen the execution of this program by the microcontroller.

The _STM32F072RBT6_ board contains a small number of input and output devices. The board with external elements expands the input and output capabilities, which allows you to create many different training tasks using the indication and all kinds of buttons and switches.

![ ](../../img/learning_stand.png)

1. _STM32F072B-DISCO_ evaluation board
2. Alphanumeric LCD indicator with built-in controller
3. Switches for changing peripherals
4. DAC outputs with BNC connector
5. ADC input via SPI with BNC connector
6. ADC input with BNC connector
7. 16 RGB LEDs (D1-D16)
8. Switches for selecting the ADC channel between BNC inputs and potentiometers POT1, POT2
9. Potentiometers (POT1 and POT2)
10. Keyboard consisting of 16 buttons
11. Buttons (SB1-SB4)
12. Switches (SW1-SW4)
13. 4-digit seven-segment indicator
14. SD card slot
15. CAN connector
16. USB-UART connector
17. Power connector
18. Data transmission module (ZigBee, Wi-Fi, Bluetooth)

## Installing and Configuring Development Tools

### Keil uVision5

The development of software for the microcontroller is carried out
in the Integrated Development Environment (IDE)
[Keil MDK Lite Edition](http://www2.keil.com/mdk5/editions/lite).
To download, you need to register on the Keil website.
The installation process is no different from installing any other program for Windows.

> :bulb: **Note:** Avoid Russian-language directory names both in the installation path of the program and in the paths to your projects. Some components of the development environment may not work.

This version has almost all the functionality of the professional version,
but with a limit on the size of the compiled program (`32 kB`).
For labs and workshops of this course, this is more than enough.

`Keil MDK Lite Edition` has a simulator, so the program
can be checked without a evaluation board. However, this simulator supports only the central processor, but not the peripheral modules of the microcontroller.

Keil MDK Lite Edition is initially unaware of microcontrollers
firm ST. Therefore, you will need to download and install the package `Keil.STM32F0xx_DFP.2.1.0.pack` with libraries for `stm32f0`.

### vscode gcc

> :bulb: **Note:** The use of the `gcc` and `vscode` tools is optional. All examples of workshops and labs are accompanied by a project in `Keil uVision5`.

All components will be installed on the command line.
The sequence of actions depends on the operating system.

You will need `arm-none-eabi-gcc` cross compiler, `make` build utility, `openocd` debugger, and
`Visual Studio Code` text editor with extensions.

#### Windows

Open command prompt in administrator mode.

- Download and install `Chocolatey` package manager

    The package manager will allow you to quickly install the necessary programs without resorting to searching for installation files on the Internet.

    Installation is performed by the command:

    ```shell
    Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))
    ```

    Check the installation with the command:

    ```shell
    choco --version
    ```

    If the installation was successful, the program version will be printed on the command line, for example

    ```shell
    0.10.15
    ```

- Install cross compiler `arm-none-eabi-gcc`

    ```shell
    choco install gcc-arm-embedded
    choco install make
    choco install openocd
    ```

  Checking the correct installation:

  ```shell
  make --version
  arm-none-eabi-gcc --version
  openocd --version
  ```

  Each command must return its own version.

- Download and install [vscode text editor](#vscode text editor).

#### Linux

- Installation on systems with `apt` package manager:

  ```shell
  sudo apt install binutils
  sudo apt install arm-none-eabi-gcc
  sudo apt install openocd
   ```

  Checking the correct installation:

  ```shell
  make --version
  arm-none-eabi-gcc --version
  openocd --version
  ```

  Each command must return its own version.

- Download and install [vscode text editor](#vscode text editor).

#### macOS

- Installation on systems with `brew` package manager:

  ```shell
  brew tap ArmMbed/homebrew-formulae
  brew install arm-none-eabi-gcc
  brew install openocd
  ```

  Checking the correct installation:

  ```shell
  make --version
  arm-none-eabi-gcc --version
  openocd --version
  ```

  Each command must return its own version.

- Download and install [vscode text editor](#vscode text editor).

#### vscode text editor

The instruction is applicable to all operating systems.

Download and install the version of [Visual Studio Code](https://code.visualstudio.com/) from the site according to your operating system.

Install extensions (extensions):

- To work with C/C++ code - [C/C++ for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

- For debug visualization - [Cortex-Debug](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug)

- For assembly language syntax highlighting - [Arm Assembly](https://marketplace.visualstudio.com/items?itemName=dan-c-underwood.arm)

- For linker script syntax highlighting - [LinkerScript](https://marketplace.visualstudio.com/items?itemName=ZixuanWang.linkerscript)

## Feedback

If you find errors or typos, please report them via [issues](https://github.com/smirnovalnik/microprocessor-units-course/issues) in `GitHub` or write to [smirnovalnik@mpei.ru](mailto:smirnovalnik@mpei.ru).

If you want to improve the content of the repository, you can create a `pull request` to add your changes.
