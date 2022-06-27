#include <scpiparser.h>
#include <filter.hpp>
#include "scpi_commands.hpp"

// System commands
scpi_error_t identify(struct scpi_parser_context* context, struct scpi_token* command)
{
    scpi_free_tokens(command);
    RESPONSE_LEN = snprintf(SEND_BUFFER, BUFFER_LEN, "Vaccum Controller 1 (3CH)\n");
    return SCPI_SUCCESS;
}

scpi_error_t reset(struct scpi_parser_context* context, struct scpi_token* command)
{
    scpi_free_tokens(command);
    RESPONSE_LEN = snprintf(SEND_BUFFER, BUFFER_LEN, "Resetting now...\n");
    reset_flag = 1;
    return SCPI_SUCCESS;
}

scpi_error_t disconnect(struct scpi_parser_context* context, struct scpi_token* command)
{
    scpi_free_tokens(command);
    RESPONSE_LEN = snprintf(SEND_BUFFER, BUFFER_LEN, "Closing connection...\n");
    disconnect_flag = 1;
    return SCPI_SUCCESS;
}

// filter1 commands
scpi_error_t filter1_insert(struct scpi_parser_context* context, struct scpi_token* command)
{
    filter1.insert();
    scpi_free_tokens(command);
    RESPONSE_LEN = 0;
    return SCPI_SUCCESS;
}

scpi_error_t filter1_remove(struct scpi_parser_context* context, struct scpi_token* command)
{
    filter1.remove();
    scpi_free_tokens(command);
    RESPONSE_LEN = 0;
    return SCPI_SUCCESS;
}

scpi_error_t filter1_getstate(struct scpi_parser_context* context, struct scpi_token* command)
{
    scpi_free_tokens(command);
    RESPONSE_LEN = snprintf(SEND_BUFFER, BUFFER_LEN, "%d\n", filter1.state);
    return SCPI_SUCCESS;
}
