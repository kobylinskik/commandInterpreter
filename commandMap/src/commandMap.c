#include "commandMap.h"

uint8_t generateHash(char * key) {
    uint8_t resultBase = 0;
    for (uint8_t i = 0; i < 5 && key[i] != 0; i++) {
        resultBase += key[i] - 'A';
    }

    return resultBase % NUMBER_OF_BUCKETS;
};

void initMap(commandMap_t * map) {
    for (uint8_t i = 0; i < NUMBER_OF_BUCKETS; i++) {
        map->buckets[i].currentSize = 0;
    }
}

void put(commandMap_t * map, command_t * command) {
    uint8_t hash = generateHash(command->label);
    commandMapBucket_t * bucket = &(map->buckets[hash]);
    uint8_t bucketSize = bucket->currentSize;
    bucket->commands[bucketSize] = command;
    bucket->currentSize++;
};

command_t * get(commandMap_t * map, char * key) {
    uint8_t hash = generateHash(key);

    commandMapBucket_t * bucket = &(map->buckets[hash]);

    for (uint8_t i = 0; i < bucket->currentSize; i++) {
        if (stringsMatch(bucket->commands[i]->label, key, 30) == 1) {
            return bucket->commands[i];
        }
    }
    return 0;
};