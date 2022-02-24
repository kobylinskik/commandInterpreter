#ifndef __COMMAND_LIST__

#define __COMMAND_LIST__

typedef struct commandListNode {
    command_t * command;
    struct commandListNode * next;
} commandListNode_t;

commandListNode_t * createCommandListNode(command_t * command);

void insertCommand(commandListNode_t * listNode, command_t * command);

#endif