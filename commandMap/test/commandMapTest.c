#include <stdint.h>
#include <stdlib.h>
#include "unity.h"
#include "command.h"
#include "commandList.h"
#include "commandMap.h"

void setUp(void) {

}

void tearDown(void) {

}

void shouldGenerateHashForString(void) {
    char * key = "testString";

    uint8_t hash = generateHash(key);
    uint8_t expectedResult = ('t' + 'e' + 's' +'t' + 'S' - 5 * 'A') % NUMBER_OF_BUCKETS;

    TEST_ASSERT_EQUAL_UINT8(expectedResult, hash);
}

void test() {

};

void shouldPutCommandUnderHashAndRetrieveIt(void) {
    char * commandName1 = "testCommand1";
    command_t command1;
    command1.label = commandName1;

    char * commandName2 = "testCommand2";
    command_t command2;
    command2.label = commandName2;

    test();

    commandMap_t * cmap = malloc(sizeof(commandMap_t));
    test();
    put(cmap, &command1);
    test();
    put(cmap, &command2);
    test();

    command_t * testedCommand = get(cmap, commandName2);
    test();

    TEST_ASSERT_EQUAL_UINT64((uint64_t)&command2, (uint64_t)testedCommand);
}

int main(void) {
  UNITY_BEGIN();  
  RUN_TEST(shouldGenerateHashForString);
  RUN_TEST(shouldPutCommandUnderHashAndRetrieveIt);
  return UNITY_END();
}
