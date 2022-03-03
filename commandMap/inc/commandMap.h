#ifndef __COMMAND_MAP__

#define __COMMAND_MAP__

#include "command.h"
#include "stringUtils.h"
#include <stdint.h>

#define NUMBER_OF_BUCKETS 23
#define MAX_BUCKET_SIZE 10

typedef struct {
    uint8_t currentSize;
    command_t * commands[MAX_BUCKET_SIZE];
} commandMapBucket_t;

typedef struct {
    commandMapBucket_t buckets[NUMBER_OF_BUCKETS];
} commandMap_t;

void initMap(commandMap_t * map);

uint8_t generateHash(char * key);

void put(commandMap_t * map, command_t * command);

command_t * get(commandMap_t * map, char * key);

#endif