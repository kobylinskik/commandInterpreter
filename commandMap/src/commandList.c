#include <stdint.h>
#include <stdlib.h>
#include "command.h"
#include "commandList.h"

commandListNode_t * createCommandListNode(command_t * command) {
    commandListNode_t * node = malloc(sizeof(commandListNode_t));
    node->command = command;
    node->next = NULL;
    return node;
};

void insertCommand(commandListNode_t * listNode, command_t * command) {
    while (listNode->next != NULL) {
        listNode = listNode->next;
    }
    listNode->next = createCommandListNode(command);
};