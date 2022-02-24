#include <stdint.h>
#include "command.h"

uint8_t validateParams(command_t * command, uint8_t argc, char ** argv) {
    return command->validation(argc, argv);
}

char * execute(command_t * command, uint8_t argc, char ** argv) {
    return command->function(argc, argv);
}