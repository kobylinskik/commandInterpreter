#ifndef __COMMAND_MAP__

#define __COMMAND_MAP__

#define NUMBER_OF_BUCKETS 23

typedef struct {
    commandListNode_t * buckets[NUMBER_OF_BUCKETS];
} commandMap_t;

uint8_t generateHash(char * key);

void put(commandMap_t * map, command_t * command);

command_t * get(commandMap_t * map, char * key);

#endif