#ifndef SCPI_COMMANDS_HPP
#define SCPI_COMMANDS_HPP

#define BUFFER_LEN 64

#define LED1_PIN CONTROLLINO_D14
#define LED2_PIN CONTROLLINO_D15

extern volatile uint8_t reset_flag;
extern volatile uint8_t disconnect_flag;

extern uint8_t RESPONSE_LEN;
extern char COMMAND_BUFFER[BUFFER_LEN];
extern char SEND_BUFFER[BUFFER_LEN];

extern filter filter1;
extern filter filter2;
extern filter filter3;
extern filter filter4;
extern filter filter5;
extern filter filter6;

scpi_error_t identify(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t reset(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t disconnect(struct scpi_parser_context* context, struct scpi_token* command);

scpi_error_t filter1_insert(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t filter1_remove(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t filter1_getstate(struct scpi_parser_context* context, struct scpi_token* command);

scpi_error_t filter2_insert(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t filter2_remove(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t filter2_getstate(struct scpi_parser_context* context, struct scpi_token* command);

scpi_error_t filter3_insert(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t filter3_remove(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t filter3_getstate(struct scpi_parser_context* context, struct scpi_token* command);

scpi_error_t filter4_insert(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t filter4_remove(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t filter4_getstate(struct scpi_parser_context* context, struct scpi_token* command);

scpi_error_t filter5_insert(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t filter5_remove(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t filter5_getstate(struct scpi_parser_context* context, struct scpi_token* command);

scpi_error_t filter6_insert(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t filter6_remove(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t filter6_getstate(struct scpi_parser_context* context, struct scpi_token* command);

scpi_error_t set_led1(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t set_led2(struct scpi_parser_context* context, struct scpi_token* command);
#endif
