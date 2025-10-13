#ifndef _LOGGER
#define _LOGGER

#define TRACE   1
#define ERROR   2
#define WARNING 3
#define INFO    4

#define MAX_STACK_DEPTH 32


#include "system.h"

int log_stack_depth;
void level_log(uint8_t level, const char* msg, ...);
void logger_disable();
void logger_enable();
void ADD_TO_STACK_DEPTH(void);
void REMOVE_FROM_STACK_DEPTH(void);

uint8_t log_state;

#endif // _LOGGER