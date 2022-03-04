TARGET = main.elf

COMMAND_MAP_DIR = ./commandMap
COMMAND_MAP_SRC = $(COMMAND_MAP_DIR)/src
COMMAND_MAP_INC = $(COMMAND_MAP_DIR)/inc
COMMAND_MAP_TEST = $(COMMAND_MAP_DIR)/test

INPUT_HANDLER_DIR = ./inputHandler
INPUT_HANDLER_SRC = $(INPUT_HANDLER_DIR)/src
INPUT_HANDLER_INC = $(INPUT_HANDLER_DIR)/inc
INPUT_HANDLER_TEST = $(INPUT_HANDLER_DIR)/test

STRING_UTILS_DIR = ./stringUtils
STRING_UTILS_SRC = $(STRING_UTILS_DIR)/src
STRING_UTILS_INC = $(STRING_UTILS_DIR)/inc
STRING_UTILS_TEST = $(STRING_UTILS_DIR)/test

COMMAND_DATA_DIR = ./commandData
COMMAND_DATA_SRC = $(COMMAND_DATA_DIR)/src
COMMAND_DATA_INC = $(COMMAND_DATA_DIR)/inc
COMMAND_DATA_TEST = $(COMMAND_DATA_DIR)/test

CMSIS_DIR = ./CMSIS
CORE_SUPPORT_DIR = $(CMSIS_DIR)/CM3/CoreSupport
DEVICE_SUPPORT_DIR = $(CMSIS_DIR)/CM3/DeviceSupport/ST/STM32F10x

CC = arm-none-eabi-gcc

CCFLAGS += -mcpu=cortex-m3
CCFLAGS += -mthumb
CCFLAGS += -I.
CCFLAGS += -I$(COMMAND_MAP_INC)
CCFLAGS += -I$(INPUT_HANDLER_INC)
CCFLAGS += -I$(STRING_UTILS_INC)
CCFLAGS += -I$(COMMAND_DATA_INC)
CCFLAGS += -I$(CORE_SUPPORT_DIR)
CCFLAGS += -I$(DEVICE_SUPPORT_DIR)
CCFLAGS += --specs=nosys.specs
CCFLAGS += -g

INPUT += main.c
INPUT += $(DEVICE_SUPPORT_DIR)/startup/gcc_ride7/startup_stm32f10x_ld.s
INPUT += $(DEVICE_SUPPORT_DIR)/system_stm32f10x.c
INPUT += $(CORE_SUPPORT_DIR)/core_cm3.c
INPUT += $(COMMAND_MAP_SRC)/command.c
INPUT += $(COMMAND_MAP_SRC)/commandMap.c
INPUT += $(COMMAND_DATA_SRC)/commandData.c
INPUT += $(STRING_UTILS_SRC)/stringUtils.c
INPUT += $(INPUT_HANDLER_SRC)/inputHandler.c

LD = -T./linkerScript.ld

OUTPUT = -o $(TARGET)


TEST_CC = gcc

UNITY_DIR = ./Unity/src
UNITY = $(UNITY_DIR)/unity.c

TEST_CCFLAGS += -I.
TEST_CCFLAGS += -I$(COMMAND_MAP_INC)
TEST_CCFLAGS += -I$(COMMAND_MAP_TEST)
TEST_CCFLAGS += -I$(INPUT_HANDLER_INC)
TEST_CCFLAGS += -I$(INPUT_HANDLER_TEST)
TEST_CCFLAGS += -I$(STRING_UTILS_INC)
TEST_CCFLAGS += -I$(STRING_UTILS_TEST)
TEST_CCFLAGS += -I$(UNITY_DIR)
TEST_CCFLAGS += -g
TEST_CCFLAGS += -w

COMMAND_TEST_TARGET = commandTest

COMMAND_TEST_INPUT = $(COMMAND_MAP_SRC)/command.c
COMMAND_TEST_INPUT += $(COMMAND_MAP_TEST)/commandTest.c
COMMAND_TEST_INPUT += $(STRING_UTILS_SRC)/stringUtils.c
COMMAND_TEST_INPUT += $(UNITY)

COMMAND_TEST_OUTPUT = -o $(COMMAND_TEST_TARGET)


COMMAND_MAP_TEST_TARGET = commandMapTest

COMMAND_MAP_TEST_INPUT = $(COMMAND_MAP_SRC)/command.c
COMMAND_MAP_TEST_INPUT += $(COMMAND_MAP_SRC)/commandMap.c
COMMAND_MAP_TEST_INPUT += $(COMMAND_MAP_TEST)/commandMapTest.c
COMMAND_MAP_TEST_INPUT += $(STRING_UTILS_SRC)/stringUtils.c
COMMAND_MAP_TEST_INPUT += $(UNITY)

COMMAND_MAP_TEST_OUTPUT = -o $(COMMAND_MAP_TEST_TARGET)

STRING_UTILS_TEST_TARGET = stringUtilsTest

STRING_UTILS_TEST_INPUT = $(STRING_UTILS_SRC)/stringUtils.c
STRING_UTILS_TEST_INPUT += $(STRING_UTILS_TEST)/stringUtilsTest.c
STRING_UTILS_TEST_INPUT += $(UNITY)

STRING_UTILS_TEST_OUTPUT = -o $(STRING_UTILS_TEST_TARGET)

INPUT_HANDLER_TEST_TARGET = inputHandlerTest

INPUT_HANDLER_TEST_INPUT = $(COMMAND_MAP_SRC)/command.c
INPUT_HANDLER_TEST_INPUT += $(COMMAND_MAP_SRC)/commandMap.c
INPUT_HANDLER_TEST_INPUT += $(INPUT_HANDLER_SRC)/inputHandler.c
INPUT_HANDLER_TEST_INPUT += $(INPUT_HANDLER_TEST)/inputHandlerTest.c
INPUT_HANDLER_TEST_INPUT += $(STRING_UTILS_SRC)/stringUtils.c
INPUT_HANDLER_TEST_INPUT += $(UNITY)

INPUT_HANDLER_TEST_OUTPUT = -o $(INPUT_HANDLER_TEST_TARGET)

main:
	$(CC) $(CCFLAGS) $(INPUT) $(LD) $(OUTPUT)

testCommand:
	$(TEST_CC) $(TEST_CCFLAGS) $(COMMAND_TEST_INPUT) $(COMMAND_TEST_OUTPUT)
	./$(COMMAND_TEST_TARGET)

testCommandMap:
	$(TEST_CC) $(TEST_CCFLAGS) $(COMMAND_MAP_TEST_INPUT) $(COMMAND_MAP_TEST_OUTPUT)
	./$(COMMAND_MAP_TEST_TARGET)

testStringUtils:
	$(TEST_CC) $(TEST_CCFLAGS) $(STRING_UTILS_TEST_INPUT) $(STRING_UTILS_TEST_OUTPUT)
	./$(STRING_UTILS_TEST_TARGET)

testInputHandler:
	$(TEST_CC) $(TEST_CCFLAGS) $(INPUT_HANDLER_TEST_INPUT) $(INPUT_HANDLER_TEST_OUTPUT)
	./$(INPUT_HANDLER_TEST_TARGET)

runAllTests:
	make testCommand
	make testCommandMap
	make testInputHandler