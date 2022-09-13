
# Цель
TARGET = learning_stand

# Переменные сборки
# Включить отладочную информацию или нет
DEBUG = 1
# Уровень оптимизации
OPT = -O0

# Пути
# Директория с результатом построения
BUILD_DIR = build

# Исходные коды
# Исходные коды на языке C
C_SOURCES = \
src/main.c \
src/system_stm32f0xx.c

# Исходные коды на языке ассемблер
ASM_SOURCES = \
src/startup_stm32f072xb.s

# Префикс бинарников
PREFIX = arm-none-eabi-
# Путь к бинарникам gcc компилятора может быть определен при вызове через переменную GCC_PATH ($ make GCC_PATH=xxx)
# или может быть добавлен в переменные среды PATH.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

# Флаги CFLAGS
# Выбор центрального процессора
CPU = -mcpu=cortex-m0

# Включение поддержки fpu
# Отсутсвует для Cortex-M0/M0+/M3
FPU =

# float-abi
FLOAT-ABI =

# МК
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# Подключение макроопределений для gcc
# Для ассемблера
AS_DEFS =

# Для C
C_DEFS =  \
-DSTM32F072xB

# Подключение заголовочных файлов
# Для ассемблера
AS_INCLUDES =

# Для C
C_INCLUDES =  \
-Isrc \
-Ilib/cmsis_device_f0/Include \
-Ilib/cmsis_core/Include

# Итоговые флаги gcc
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

# Подключение отладочной информации
ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Создание информации о зависимостях
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

# Флаги LDFLAGS
# Скрипт компоновщика
LDSCRIPT = STM32F072RBTx_FLASH.ld

# Внешние библиотеки
LIBS = -lc -lm -lnosys
LIBDIR =
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# Цель по умолчанию: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

# Построение
# Список объектов на языке C
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# Список объектов на языке ассемблер
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir $@

# Очистка директории с результатом построения
clean:
	-rm -fR $(BUILD_DIR)

# Прошивка МК
flash:
	openocd -f interface/stlink.cfg -f target/stm32f0x.cfg -c "program $(BUILD_DIR)/$(TARGET).elf verify reset exit"

# Зависимости
-include $(wildcard $(BUILD_DIR)/*.d)
