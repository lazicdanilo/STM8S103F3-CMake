#include "log.h"

#if ENABLE_DEBUG
    static char temp_msg[LOG_MESSAGE_MAX_SIZE + 2]; /* +2 for \r\n */
#endif  /* ENABLE_DEBUG */

static DEBUG_LOG_PRINT debug_log_print = NULL;

/**
 * @brief Adds log function
 * @param[in] print_function Pointer to the log function tat will interact with hardware (UART for example)
 */
void add_log_print_function(DEBUG_LOG_PRINT print_function) {
    debug_log_print = print_function;
}

#if ENABLE_DEBUG
/**
 * @brief Adds prefix to the provided log message based on log_level parameter and calls user provided callback function to send the message
 * @param[in] log_level Log level of the log message we want to print (LOG_LEVEL_INFO, LOG_LEVEL_WARN, LOG_LEVEL_ERROR)
 * @param[in] msg Pointer to the log message we want to print
 */
void log(log_level_t log_level, char *msg, ...) {
    va_list args;
    uint8_t prefix_size = 0;

    switch (log_level) {
        case LOG_LEVEL_INFO:
            strcpy(temp_msg, INFO_MSG_PREFIX);
            prefix_size = INFO_MSG_PREFIX_SIZE;
            break;

        case LOG_LEVEL_WARN:
            strcpy(temp_msg, WARN_MSG_PREFIX);
            prefix_size = INFO_MSG_PREFIX_SIZE;
            break;

        case LOG_LEVEL_ERROR:
            strcpy(temp_msg, ERROR_MSG_PREFIX);
            prefix_size = INFO_MSG_PREFIX_SIZE;
            break;
    }

    /* If we are over the allowed  size, cap it to max size so we don't overflow */
    if (strlen(msg) >= (LOG_MESSAGE_MAX_SIZE - prefix_size)) {
        return;
    }

    /* Add arguments */
    va_start(args, msg);
    int msg_size = vsprintf(&temp_msg[prefix_size], msg, args);
    va_end(args);

    msg_size += prefix_size;
    /* Add new line characters */
    temp_msg[msg_size] = '\r';
    msg_size++;
    temp_msg[msg_size] = '\n';
    msg_size++;

    if (debug_log_print != NULL) {
        debug_log_print(temp_msg, (uint32_t)msg_size);
    }
}

#endif  /* ENABLE_DEBUG */
