#include "logger.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int log_stack_depth = 0;
uint8_t log_state = 1;

#define LOGGER_DISABLED

void level_log(uint8_t level, const char* msg, ...)
{
    #ifndef LOGGER_DISABLED

    if(!log_state) return; 
    if(log_stack_depth >= MAX_STACK_DEPTH) return;
    
    va_list ap;
    int format_specifier_value;

    va_start (ap, msg);
    format_specifier_value = va_arg (ap, int);
    va_end (ap);

    /* To Keep track of the call stack visually,
     I am putting spaces before the log message 
     */
    for(int i=0; i<log_stack_depth; i++){
        printf(">  ");
    }
    

    // Allocating memory for the message with 
    char* new_msg = (char*)(calloc(128, sizeof(uint8_t)));
    if(new_msg == NULL) {
        printf("Memory allocation for new_msg failed\n");
        /* ensure the memory is properly released */
        free(new_msg);
        new_msg = NULL;
        return;
    }

    sprintf(new_msg, msg, format_specifier_value);

    switch (level) {

        case TRACE:
            printf("Trace:   %s\n", new_msg);
            break;

        case ERROR:
            printf("! ERROR: %s\n", new_msg);
            break;

        case WARNING:
            printf("Warning: %s\n", new_msg);
            break;

        case INFO:
            printf("Info:    %s\n", new_msg);
    }

    free(new_msg);
    new_msg = NULL;

    #endif
    return;
}

void logger_disable() {
    log_state = 0;
}

void logger_enable() {
    log_state = 1;
}

void REMOVE_FROM_STACK_DEPTH(void) {
    
    #ifndef LOGGER_DISABLED

    log_stack_depth--;
    if (log_stack_depth < MAX_STACK_DEPTH)
    {
        printf("------------------------------------------------------\n");
    }

    #endif
    return;
}

void ADD_TO_STACK_DEPTH(void)
{
    log_stack_depth++;
}