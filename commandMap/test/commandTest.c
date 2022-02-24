#include <stdint.h>
#include "unity.h"
#include "command.h"

void setUp(void) {

}

void tearDown(void) {

}

char * testStringRet(uint8_t argc, char ** argv) {
    return "result";
}

char * testCommandWithParamsFunction(uint8_t argc, char ** argv) {
    char * result = malloc(30 * sizeof(char));
    char * charPtr = result;
    for (int i = 0; i < argc; i++) {
      for (int j = 0; argv[i][j] != 0; j++) {
        *(charPtr++) = argv[i][j];
      }
      *(charPtr++) = ' ';
    }
    *charPtr = 0;
    return result;
}

void shouldExecuteCommand(void) {
    command_t command;
    command.function = *testStringRet;
    uint8_t argc = 0;
    char ** argv = NULL;
    char * result = execute(&command, argc, argv);
    TEST_ASSERT_EQUAL_STRING("result", result);
}

void shouldExecuteCommandWithParams(void) {
  command_t command;
    command.function = *testCommandWithParamsFunction;
    uint8_t argc = 3;
    char ** argv;
    argv[0] = "test";
    argv[1] = "result";
    argv[2] = "number 1";
    char * result = execute(&command, argc, argv);
    TEST_ASSERT_EQUAL_STRING("test result number 1 ", result);
}

int main(void) {
  UNITY_BEGIN();  
  RUN_TEST(shouldExecuteCommand);
  RUN_TEST(shouldExecuteCommandWithParams);
  return UNITY_END();
}
