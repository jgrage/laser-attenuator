#include <Controllino.h>
#include <scpiparser.h>
#include <filter.hpp>
#include "scpi_commands.hpp"

// System commands
scpi_error_t identify(struct scpi_parser_context* context, struct scpi_token* command)
{
    scpi_free_tokens(command);
    RESPONSE_LEN = snprintf(SEND_BUFFER, BUFFER_LEN, "Laser Attenuator\n");
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


// filter2 commands
scpi_error_t filter2_insert(struct scpi_parser_context* context, struct scpi_token* command)
{
    filter2.insert();
    scpi_free_tokens(command);
    RESPONSE_LEN = 0;
    return SCPI_SUCCESS;
}

scpi_error_t filter2_remove(struct scpi_parser_context* context, struct scpi_token* command)
{
    filter2.remove();
    scpi_free_tokens(command);
    RESPONSE_LEN = 0;
    return SCPI_SUCCESS;
}

scpi_error_t filter2_getstate(struct scpi_parser_context* context, struct scpi_token* command)
{
    scpi_free_tokens(command);
    RESPONSE_LEN = snprintf(SEND_BUFFER, BUFFER_LEN, "%d\n", filter2.state);
    return SCPI_SUCCESS;
}


// filter3 commands
scpi_error_t filter3_insert(struct scpi_parser_context* context, struct scpi_token* command)
{
    filter3.insert();
    scpi_free_tokens(command);
    RESPONSE_LEN = 0;
    return SCPI_SUCCESS;
}

scpi_error_t filter3_remove(struct scpi_parser_context* context, struct scpi_token* command)
{
    filter3.remove();
    scpi_free_tokens(command);
    RESPONSE_LEN = 0;
    return SCPI_SUCCESS;
}

scpi_error_t filter3_getstate(struct scpi_parser_context* context, struct scpi_token* command)
{
    scpi_free_tokens(command);
    RESPONSE_LEN = snprintf(SEND_BUFFER, BUFFER_LEN, "%d\n", filter3.state);
    return SCPI_SUCCESS;
}


// filter4 commands
scpi_error_t filter4_insert(struct scpi_parser_context* context, struct scpi_token* command)
{
    filter4.insert();
    scpi_free_tokens(command);
    RESPONSE_LEN = 0;
    return SCPI_SUCCESS;
}

scpi_error_t filter4_remove(struct scpi_parser_context* context, struct scpi_token* command)
{
    filter4.remove();
    scpi_free_tokens(command);
    RESPONSE_LEN = 0;
    return SCPI_SUCCESS;
}

scpi_error_t filter4_getstate(struct scpi_parser_context* context, struct scpi_token* command)
{
    scpi_free_tokens(command);
    RESPONSE_LEN = snprintf(SEND_BUFFER, BUFFER_LEN, "%d\n", filter4.state);
    return SCPI_SUCCESS;
}


// filter5 commands
scpi_error_t filter5_insert(struct scpi_parser_context* context, struct scpi_token* command)
{
    filter5.insert();
    scpi_free_tokens(command);
    RESPONSE_LEN = 0;
    return SCPI_SUCCESS;
}

scpi_error_t filter5_remove(struct scpi_parser_context* context, struct scpi_token* command)
{
    filter5.remove();
    scpi_free_tokens(command);
    RESPONSE_LEN = 0;
    return SCPI_SUCCESS;
}

scpi_error_t filter5_getstate(struct scpi_parser_context* context, struct scpi_token* command)
{
    scpi_free_tokens(command);
    RESPONSE_LEN = snprintf(SEND_BUFFER, BUFFER_LEN, "%d\n", filter5.state);
    return SCPI_SUCCESS;
}


// filter6 commands
scpi_error_t filter6_insert(struct scpi_parser_context* context, struct scpi_token* command)
{
    filter6.insert();
    scpi_free_tokens(command);
    RESPONSE_LEN = 0;
    return SCPI_SUCCESS;
}

scpi_error_t filter6_remove(struct scpi_parser_context* context, struct scpi_token* command)
{
    filter6.remove();
    scpi_free_tokens(command);
    RESPONSE_LEN = 0;
    return SCPI_SUCCESS;
}

scpi_error_t filter6_getstate(struct scpi_parser_context* context, struct scpi_token* command)
{
    scpi_free_tokens(command);
    RESPONSE_LEN = snprintf(SEND_BUFFER, BUFFER_LEN, "%d\n", filter6.state);
    return SCPI_SUCCESS;
}


// led1
scpi_error_t set_led1(struct scpi_parser_context* context, struct scpi_token* command)
{
    struct scpi_token* args;
    struct scpi_numeric output_numeric;
    uint8_t output_value;

    args = command;

    while(args != NULL && args->type == 0){
        args = args->next;
    }

    output_numeric = scpi_parse_numeric(args->value, args->length, 0, 0, 100);
    
    if(output_numeric.length == 0){
        output_value = (uint8_t)constrain(output_numeric.value / 100.0f * 256.0f, 0, 255);
        analogWrite(LED1_PIN, output_value);
        RESPONSE_LEN = 0;
    }
    
    else{
        RESPONSE_LEN = snprintf(SEND_BUFFER, BUFFER_LEN, "%s\n", "Command error;Invalid unit");
    }

    
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
}


// led2
scpi_error_t set_led2(struct scpi_parser_context* context, struct scpi_token* command)
{
    struct scpi_token* args;
    struct scpi_numeric output_numeric;
    uint8_t output_value;

    args = command;

    while(args != NULL && args->type == 0){
        args = args->next;
    }

    output_numeric = scpi_parse_numeric(args->value, args->length, 0, 0, 100);
    
    if(output_numeric.length == 0){
        output_value = (uint8_t)constrain(output_numeric.value / 100.0f * 256.0f, 0, 255);
        analogWrite(LED2_PIN, output_value);
        RESPONSE_LEN = 0;
    }
    
    else{
        RESPONSE_LEN = snprintf(SEND_BUFFER, BUFFER_LEN, "%s\n", "Command error;Invalid unit");
    }

    
    scpi_free_tokens(command);
    return SCPI_SUCCESS;
}
