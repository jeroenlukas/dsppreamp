/*
 * File:   pccomm.c
 * Author: Jeroen
 *
 * Created on 26 augustus 2020, 20:12
 */


#include "xc.h"
#include <stdint.h>
#include <string.h>

#include "mcc_generated_files/mcc.h"

#include "config.h"
#include "pccomm.h"
#include "patches.h"
#include "lcd_pcf8574.h"

#define STATE_IDLE      0
#define STATE_HEADER    1
#define STATE_COMMAND   2
#define STATE_LENGTH    3
#define STATE_PAYLOAD   4
#define STATE_DONE      5

uint8_t receive_state_machine = STATE_IDLE;
uint8_t receive_length = 0;
uint8_t receive_buffer[100];
uint8_t receive_header_count = 0;
uint8_t receive_length_left = 0;

uint8_t f_frame_ready = 0;

frame_t received_command;
frame_t transmit_command;

void comm_parse_command(void);

uint8_t pccomm_frame_ready(void)
{
    return f_frame_ready;
}

void pccomm_send_command(void)
{
    uint8_t tx_buffer[128 + 5];
    tx_buffer[0] = 0xAA;
    tx_buffer[1] = 0xAA;
    tx_buffer[2] = 0xAA;
    tx_buffer[3] = transmit_command.command;
    tx_buffer[4] = transmit_command.length;
    
    for(int i = 0; i < transmit_command.length; i ++)
    {
        tx_buffer[5 + i] = transmit_command.payload[i];
    }
    
    for(int i = 0; i < 5+  transmit_command.length; i++)
    {
        EUSART2_Write(tx_buffer[i]);
    }
    
}

void pccomm_byte_received(uint8_t data)
{
    switch(receive_state_machine)
    {
        case STATE_IDLE:
            if(data == 0xAA)
            {
                receive_header_count++;
                receive_state_machine = STATE_HEADER;                
            }
            break;
            
        case STATE_HEADER:
            receive_header_count++;
            if(receive_header_count == 3)
            {                
                receive_state_machine = STATE_COMMAND;
            }            
            break;
            
        case STATE_COMMAND:
            received_command.command = data;
            receive_state_machine = STATE_LENGTH;
            break;
            
        case STATE_LENGTH:
            received_command.length = data;
            receive_state_machine = STATE_PAYLOAD;
            receive_length_left = received_command.length;
            break;
            
        case STATE_PAYLOAD:
            received_command.payload[received_command.length - receive_length_left] = data;                   
            
            receive_length_left--;
            
            if(receive_length_left == 0)
            {
                receive_state_machine = STATE_DONE;
                
                f_frame_ready = 1;
                
                // Reset the state machine
                receive_header_count = 0;
                receive_state_machine = STATE_IDLE;
            }
            //else               
            
            break;
    }
}

void pccomm_parse_command(void)
{
    f_frame_ready = 0;
    
    switch(received_command.command)
    {
        case COMMAND_SET_PATCH_VALUE:
            if(received_command.payload[0] == 0xFF) // Current patch
            {
                switch(received_command.payload[1])
                {
                    case COMM_PATCH_GAIN:
                        patch_current_set_gain(received_command.payload[2]);                        
                        break;
                    case COMM_PATCH_LOW:
                        patch_current_set_low(received_command.payload[2]);
                        break;
                    case COMM_PATCH_MID:
                        patch_current_set_mid(received_command.payload[2]);
                        break;
                    default:
                        LCD_SetCursor(0, 2);
                        LCD_Write_Str("?");
                        break;

                }
            }
            else
            {
                // Write to eeprom...
            }
    }
}
     
void pccomm_log_message(char * text)
{
    //frame_t frame;
    transmit_command.command = COMMAND_LOG_MESSAGE;
    transmit_command.length = strlen(text);
    
    int i = 0;
    while(*text)
    {
        transmit_command.payload[i++] = *text++;
    }
    pccomm_send_command();
}