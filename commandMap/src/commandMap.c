#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "commandList.h"
#include "commandMap.h"
#include <stdio.h>

uint8_t generateHash(char * key) {
    uint8_t resultBase = 0;
    for (uint8_t i = 0; i < 5 && key[i] != 0; i++) {
        resultBase += key[i] - 'A';
    }

    return resultBase % NUMBER_OF_BUCKETS;
};

void put(commandMap_t * map, command_t * command) {
    uint8_t hash = generateHash(command->label);
    if (map->buckets[hash] == NULL) {
        map->buckets[hash] = createCommandListNode(command);
    } else {
        insertCommand(map->buckets[hash], command);
    }
};

command_t * get(commandMap_t * map, char * key) {
    uint8_t hash = generateHash(key);

    commandListNode_t * currentNode = map->buckets[hash];
    while (currentNode != NULL) {
        if (strcmp(currentNode->command->label, key) == 0) {
            return currentNode->command;
        }
        currentNode = currentNode->next;
    }
    return NULL;
};