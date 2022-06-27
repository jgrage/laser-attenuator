/* main.cpp
 * Jonas
 */
 
#include <avr/wdt.h>
#include <Ethernet.h>
#include <Controllino.h>
#include <scpiparser.h>
#include <filter.hpp>

#include "scpi_commands.hpp"


// Create Components
filter filter1;

// Define ethernet interface
byte mac[] = { 0x42, 0x23, 0xC0, 0xFE, 0xFE, 0x13 };
EthernetServer server = EthernetServer(23);


// Declare buffers for SCPI communication
uint8_t RESPONSE_LEN;
char COMMAND_BUFFER[BUFFER_LEN];
char SEND_BUFFER[BUFFER_LEN];
struct scpi_parser_context ctx;


// Flag used for periodic polling of readback values
volatile uint8_t timer_flag = 0;
volatile uint8_t reset_flag = 0;
volatile uint8_t disconnect_flag = 0;
volatile uint8_t change_flag = 0;

void setup(void){
    // Initialize ethernet controller
    //Ethernet.begin(mac, ip, gateway, subnet);
    //DHCP
    Ethernet.begin(mac);
    
    // Clear watchdog timer
    MCUSR = 0;
    
    // setup timer for sensor polling via ISR
    TCCR1A = 0x00;
    TCCR1B = 0x00;
    TCNT1 = 0x00;
    OCR1A = 780;                        // set compare unit to 780 (results in 10Hz timer with a prescaler of 1024)
    TCCR1B |= _BV(WGM12);               // CTC mode
    TCCR1B |= _BV(CS12) | _BV(CS10);    // set prescaler to 1024
    TIMSK1 |= _BV(OCIE1B);              // enable compare match interrupt
    
    
    // Initialize and connect the components
    filter1.connect(CONTROLLINO_D0, CONTROLLINO_A0, CONTROLLINO_A1);
    
    
    //Register System SCPI commands
    scpi_init(&ctx);
    scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "*IDN?", 5, "*IDN?", 5, identify);
    scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "*RST", 4, "*RST", 4, reset);
    scpi_register_command(ctx.command_tree, SCPI_CL_SAMELEVEL, "*END", 4, "*END", 4, disconnect);
    
    // Generate filter 1 command tree
    struct scpi_command* f1;
    f1 = scpi_register_command(ctx.command_tree, SCPI_CL_CHILD, "FILTER1", 7, "F1", 2, NULL);
    scpi_register_command(f1, SCPI_CL_CHILD, "INSERT", 6, "IN", 2, filter1_insert);
    scpi_register_command(f1, SCPI_CL_CHILD, "REMOVE", 6, "RM", 2, filter1_remove);
    scpi_register_command(f1, SCPI_CL_CHILD, "STATE?", 6, "ST?", 3, filter1_getstate);
    
    
    // Start server and enable interrupts
    server.begin();
    sei();
}


// Raise timer_flag
ISR(TIMER1_COMPB_vect){
    timer_flag = 1;
}


// Helper function to read variable length command and put it in a buffer
unsigned int get_command(EthernetClient* client, char* Buffer, uint8_t MaxLen){
    unsigned int c;
    uint8_t idx = 0;
    
    while(client->available() && idx < MaxLen - 1){
        c = client->read();
        
        if ((unsigned char)c == '\n'){
            break;
        }
        
        else{
            Buffer[idx] = (unsigned char)c;
            idx++;
        }
    }
    //Buffer[idx] = '\0';
    return idx;
}


void loop(){
        
    if(timer_flag == 1){
        // Flash indicating that timer is running
        digitalWrite(CONTROLLINO_D8, HIGH);
        
        // Update states
        filter1.update_state();
        
        delay(20);
        digitalWrite(CONTROLLINO_D8, LOW);
        delay(20);
        timer_flag = 0;
    }
        
    EthernetClient client = server.available();
    if (client) {
        int len = get_command(&client, COMMAND_BUFFER, BUFFER_LEN);
        scpi_execute_command(&ctx, COMMAND_BUFFER, len);
        
        if (RESPONSE_LEN > 0){
            client.write(SEND_BUFFER, RESPONSE_LEN);
            RESPONSE_LEN = 0;
        }
        
        if (disconnect_flag == 1){
            client.stop();
            disconnect_flag = 0;
        }
        
        if (reset_flag == 1){
            client.stop();
            wdt_enable(WDTO_15MS);
        }
    }
}
