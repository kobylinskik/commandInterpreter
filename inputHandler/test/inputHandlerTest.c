#include <stdint.h>
#include <stdlib.h>
#include "unity.h"
#include "inputHandler.h"

void setUp(void) {

}

void tearDown(void) {

}

void shouldSplitInputIntoCommandLabelAndTwoParams(void) {
    char * input = "setPin(A,5)";
    uint8_t inputLength = 11;
    char commandLabel[7];
    uint8_t argc = 0;
    char ** argv = malloc(2 * sizeof(char *));
    argv[0] = malloc(2 * sizeof(char));
    argv[1] = malloc(2 * sizeof(char));

    splitInputIntoCommandAndArgs(input, inputLength, commandLabel, &argc, argv);

    TEST_ASSERT_EQUAL_STRING("setPin", commandLabel);
    TEST_ASSERT_EQUAL_UINT8(2u, argc);
    TEST_ASSERT_EQUAL_STRING("A", argv[0]);
    TEST_ASSERT_EQUAL_STRING("5", argv[1]);
}

int main(void) {
  UNITY_BEGIN();  
  RUN_TEST(shouldSplitInputIntoCommandLabelAndTwoParams);
  return UNITY_END();
}
