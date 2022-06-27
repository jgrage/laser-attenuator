#ifndef SCPI_COMMANDS_HPP
#define SCPI_COMMANDS_HPP

#define BUFFER_LEN 64

extern volatile uint8_t reset_flag;
extern volatile uint8_t disconnect_flag;

extern uint8_t RESPONSE_LEN;
extern char COMMAND_BUFFER[BUFFER_LEN];
extern char SEND_BUFFER[BUFFER_LEN];

extern filter filter1;

scpi_error_t identify(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t reset(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t disconnect(struct scpi_parser_context* context, struct scpi_token* command);

scpi_error_t filter1_insert(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t filter1_remove(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t filter1_getstate(struct scpi_parser_context* context, struct scpi_token* command);
#endif
