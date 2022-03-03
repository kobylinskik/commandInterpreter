#include "command.h"

uint8_t validateParams(command_t * command, uint8_t argc, char ** argv, char * responseBuffer, uint8_t responseBufferSize) {
    return command->validation(argc, argv, responseBuffer, responseBufferSize);
}

uint8_t execute(command_t * command, uint8_t argc, char ** argv, char * responseBuffer, uint8_t responseBufferSize) {
    return command->function(argc, argv, responseBuffer, responseBufferSize);
}