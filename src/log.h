#ifndef LOG_H
#define LOG_H

#include <stdarg.h>		/* Needed for va_start and va_end */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define ENABLE_DEBUG 1

#if ENABLE_DEBUG
    #define LOG_MESSAGE_MAX_SIZE 64
    #define LOG_INFO(...) 	log(LOG_LEVEL_INFO, __VA_ARGS__);
    #define LOG_WARN(...) 	log(LOG_LEVEL_WARN, __VA_ARGS__);
    #define LOG_ERROR(...)	log(LOG_LEVEL_ERROR, __VA_ARGS__);
#else
    #define LOG_MESSAGE_MAX_SIZE 0
    #define LOG_INFO(...)
    #define LOG_WARN(...)
    #define LOG_ERROR(...)
#endif  /* ENABLE_DEBUG */

#define INFO_MSG_PREFIX "[I] "
#define INFO_MSG_PREFIX_SIZE sizeof(INFO_MSG_PREFIX) - 1	/* -1 as the sizeof returns NULL termination as well */
#define WARN_MSG_PREFIX "[W] "
#define WARN_MSG_PREFIX_SIZE sizeof(WARN_MSG_PREFIX) - 1
#define ERROR_MSG_PREFIX "[E] "
#define ERROR_MSG_PREFIX_SIZE sizeof(ERROR_MSG_PREFIX) - 1

typedef void (*DEBUG_LOG_PRINT) (char *msg, uint32_t msg_size);

typedef enum {
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_INFO,
} log_level_t;

void log(log_level_t log_level, char *msg, ...);
void add_log_print_function(DEBUG_LOG_PRINT print_function);

#endif /* LOG_H */
