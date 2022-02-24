#ifndef __COMMAND__

#define __COMMAND__

typedef struct {
    char * (*function)(uint8_t argc, char ** argv);
    uint8_t (*validation)(uint8_t argc, char ** argv);
    char * label;
} command_t;

uint8_t validateParams(command_t * command, uint8_t argc, char ** argv);

char * execute(command_t * command, uint8_t argc, char ** argv);

#endif