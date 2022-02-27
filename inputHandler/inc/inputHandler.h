#ifndef __INPUT_HANDLER__
#define __INPUT_HANDLER__

void splitInputIntoCommandAndArgs(char * input, uint8_t inputLength, char * commandLabelBuffer, uint8_t * argc, char ** argv);

#endif