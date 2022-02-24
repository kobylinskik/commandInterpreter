#include <stdint.h>
#include "unity.h"
#include "command.h"
#include "commandList.h"

void setUp(void) {

}

void tearDown(void) {

}

void shouldInsertThreeCommands(void) {
  command_t command1, command2, command3;
  commandListNode_t * head = createCommandListNode(&command1);
  insertCommand(head, &command2);
  insertCommand(head, &command3);

  uint8_t results[3];
  results[0] = head->command == &command1;
  results[1] = head->next->command == &command2;
  results[2] = head->next->next->command == &command3;

  uint8_t expectedResults[] = {1, 1, 1};

  TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedResults, results, 3);
  
}

int main(void) {
  UNITY_BEGIN();  
  RUN_TEST(shouldInsertThreeCommands);
  return UNITY_END();
}
