#include <stdint.h>
#include "unity.h"
#include "command.h"
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

void shouldPutCommandUnderHashAndRetrieveIt(void) {
    char * commandName1 = "testCommand1";
    command_t command1;
    command1.label = commandName1;

    char * commandName2 = "testCommand2";
    command_t command2;
    command2.label = commandName2;

    commandMap_t cmap;
    initMap(&cmap);
    put(&cmap, &command1);
    put(&cmap, &command2);

    command_t * testedCommand = get(&cmap, commandName2);

    TEST_ASSERT_EQUAL_UINT64((uint64_t)&command2, (uint64_t)testedCommand);
}

void shouldReturnZeroIfKLeyDoesntExist(void) {
    char * commandName1 = "testCommand1";
    command_t command1;
    command1.label = commandName1;

    char * commandName2 = "testCommand2";
    command_t command2;
    command2.label = commandName2;

    char * commandName3 = "testCommand3";

    commandMap_t cmap;
    initMap(&cmap);
    put(&cmap, &command1);
    put(&cmap, &command2);

    command_t * testedCommand = get(&cmap, commandName3);

    TEST_ASSERT_EQUAL_UINT64(0u, (uint64_t)testedCommand);
}

void shouldReturnZeroIfKBucketIsEmpty(void) {
    char * commandName1 = "testCommand1";
    command_t command1;
    command1.label = commandName1;

    char * commandName2 = "testCommand2";
    command_t command2;
    command2.label = commandName2;

    char * commandName3 = "fafafafa";

    commandMap_t cmap;
    initMap(&cmap);
    put(&cmap, &command1);
    put(&cmap, &command2);

    command_t * testedCommand = get(&cmap, commandName3);

    TEST_ASSERT_EQUAL_UINT64(0u, (uint64_t)testedCommand);
}

int main(void) {
  UNITY_BEGIN();  
  RUN_TEST(shouldGenerateHashForString);
  RUN_TEST(shouldPutCommandUnderHashAndRetrieveIt);
  RUN_TEST(shouldReturnZeroIfKLeyDoesntExist);
  RUN_TEST(shouldReturnZeroIfKBucketIsEmpty);
  return UNITY_END();
}
