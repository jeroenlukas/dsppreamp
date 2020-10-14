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
#include "models.h"
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
    
    // Workaround, length should be 2 at least otherwise new new patch doesnt load in ADAU 
    if(transmit_command.length == 1)
    {
        transmit_command.length = 2;
        transmit_command.payload[1] = 0;
    }
    
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
                    case COMM_PATCH_NAME:
                        patch_current_set_name(received_command.payload + 2);
                        break;
                    case COMM_PATCH_GAIN:
                        patch_current_set_gain(received_command.payload[2], SENDER_USER);                        
                        break;
                    case COMM_PATCH_LOW:
                        patch_current_set_low(received_command.payload[2], SENDER_USER);
                        break;
                    case COMM_PATCH_MID:
                        patch_current_set_mid(received_command.payload[2], SENDER_USER);
                        break;
                    case COMM_PATCH_VOLUME:
                        patch_current_set_volume(received_command.payload[2], SENDER_USER);
                        break;
                    case COMM_PATCH_HIGH:
                        patch_current_set_high(received_command.payload[2], SENDER_USER);
                        break;
                    case COMM_PATCH_PRES:
                        patch_current_set_presence(received_command.payload[2], SENDER_USER);
                        break;
                    case COMM_PATCH_MODEL:
                        patch_current_set_model(received_command.payload[2]);
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
            break;
        case COMMAND_SET_MODEL_VALUE:
            if(received_command.payload[0] == 0xFF) // Current model
            {
                switch(received_command.payload[1])
                {
                    case COMM_MODEL_NAME:
                        model_current_set_name(received_command.payload + 2);
                        break;
                    case COMM_MODEL_BYPASS:
                        model_current_set_bypass(received_command.payload[2]);
                        break;
                   // case COMM_MODEL_DSPDISTORTION_BYPASS:
                    //    model_current_set_dspdistortion_bypass(received_command.payload[2]);
                    //    break;
                    case COMM_MODEL_DSPDISTORTION_ALPHA:
                        model_current_set_dspdistortion_alpha((double)received_command.payload[2] / 10);
                        break;
                    case COMM_MODEL_DSPDISTORTION_GAIN_MIN:                        
                        current_patch.model.dspdistortion_gain_min = (int8_t)received_command.payload[2];
                        patch_current_set_gain(current_patch.gain, SENDER_EXT);  
                        break;
                    case COMM_MODEL_DSPDISTORTION_GAIN_MAX:
                        current_patch.model.dspdistortion_gain_max = (int8_t)received_command.payload[2];
                        patch_current_set_gain(current_patch.gain, SENDER_EXT);  
                        break;
                    case COMM_MODEL_DSPDISTORTION_VOLUME:
                        model_current_set_dspdistortion_volume(received_command.payload[2]);
                        break;
                    case COMM_MODEL_DSPDISTORTION_ASYMMETRY:
                        model_current_set_dspdistortion_asymmetry((double)received_command.payload[2] / 100);
                        break;
                  //  case COMM_MODEL_ANALOG_BYPASS:
                  //      model_current_set_analog_bypass(received_command.payload[2]);
                  //      break;
                    case COMM_MODEL_PREGAIN_LOWCUT_FREQ:
                        model_current_set_pregain_lowcut((received_command.payload[2] << 8) + received_command.payload[3]);
                        break;
                    case COMM_MODEL_PREGAIN_LOWCUT_ORDER:
                        model_current_set_pregain_lowcut_order(received_command.payload[2]);
                        break;                        
                    // Low
                    case COMM_MODEL_POSTGAIN_LOW_GAIN_MIN:
                        model_current_set_postgain_low_gain_min((int8_t)received_command.payload[2]);
                        patch_current_set_low(current_patch.low, SENDER_EXT);
                        break;
                    case COMM_MODEL_POSTGAIN_LOW_GAIN_MAX:
                        model_current_set_postgain_low_gain_max((int8_t)received_command.payload[2]);
                        patch_current_set_low(current_patch.low, SENDER_EXT);
                        break;
                        
                    // Mid
                    case COMM_MODEL_POSTGAIN_MID_GAIN_MIN:
                        model_current_set_postgain_mid_gain_min((int8_t)received_command.payload[2]);
                        patch_current_set_mid(current_patch.mid, SENDER_EXT);
                        break;
                    case COMM_MODEL_POSTGAIN_MID_GAIN_MAX:
                        model_current_set_postgain_mid_gain_max((int8_t)received_command.payload[2]);
                        patch_current_set_mid(current_patch.mid, SENDER_EXT);
                        break;
                    case COMM_MODEL_POSTGAIN_MID_Q:                        
                        model_current_set_postgain_mid_Q((double)received_command.payload[2] / 10); // range 0.1-25.5
                        break;
                    case COMM_MODEL_POSTGAIN_MID_FREQ:
                        model_current_set_postgain_mid_freq((received_command.payload[2] << 8) + received_command.payload[3]);
                        break;
                        
                    // High
                    case COMM_MODEL_POSTGAIN_HIGH_GAIN_MIN:
                        model_current_set_postgain_high_gain_min((int8_t)received_command.payload[2]);
                        patch_current_set_high(current_patch.high, SENDER_EXT);
                        break;
                    case COMM_MODEL_POSTGAIN_HIGH_GAIN_MAX:
                        model_current_set_postgain_high_gain_max((int8_t)received_command.payload[2]);
                        patch_current_set_high(current_patch.high, SENDER_EXT);
                        break;
                        
                    // Presence
                    case COMM_MODEL_POSTGAIN_PRES_ORDER:
                        model_current_set_postgain_pres_order(received_command.payload[2]);
                        break;
                    case COMM_MODEL_POSTGAIN_PRES_FREQ_MIN:
                        model_current_set_postgain_pres_freq_min((received_command.payload[2] << 8) + received_command.payload[3]);
                        patch_current_set_presence(current_patch.presence, SENDER_EXT);
                        break;
                    case COMM_MODEL_POSTGAIN_PRES_FREQ_MAX:
                        model_current_set_postgain_pres_freq_max((received_command.payload[2] << 8) + received_command.payload[3]);
                        patch_current_set_presence(current_patch.presence, SENDER_EXT);
                        break;
                }
            }
            break;
        case COMMAND_GET_MODEL_VALUE:
            switch(received_command.payload[1])
            {
                case COMM_MODEL_NAME:
                    pccomm_set_model_value_str(received_command.payload[0], COMM_MODEL_NAME, model_get_value_string(received_command.payload[0], COMM_MODEL_NAME));
                    
                    break;
            }
            break;
            
        case COMMAND_GET_PATCH_VALUE:
            switch(received_command.payload[1])
            {
                case COMM_PATCH_NAME:
                    pccomm_set_patch_value_str(received_command.payload[0], COMM_PATCH_NAME, patch_get_value_string(received_command.payload[0], COMM_MODEL_NAME));
                    break;
            }
            break;
            
        case COMMAND_STORE_CURRENT_MODEL:
            model_current_store(current_patch.model_id);
            break;
            
        case COMMAND_STORE_CURRENT_PATCH:
            patch_current_store(current_patch_no);
            break;
            
        case COMMAND_SELECT_PATCH:
            patch_load(received_command.payload[0]);
            break;
            
        case COMMAND_INITIALIZE_PATCHES:
            patch_initialize(received_command.payload[0]);
            break;
            
        case COMMAND_INITIALIZE_MODELS:
            model_initialize(received_command.payload[0]);
            break;
    }
}
     
void pccomm_log_message(char * text)
{
    //frame_t frame;
    transmit_command.command = COMMAND_LOG_MESSAGE;
    transmit_command.length = strlen(text) + 1;
    
    int i = 0;
    while(*text)
    {
        transmit_command.payload[i++] = *text++;
    }
    transmit_command.payload[i] = '\0';
    pccomm_send_command();
}

void pccomm_heartbeat(void)
{
    transmit_command.command = COMMAND_HEARTBEAT;
    transmit_command.length = 1;
    transmit_command.payload[0] = 0;
    pccomm_send_command();
}

void pccomm_log_midi_cc(uint8_t chan, uint8_t cc, uint8_t value)
{
    transmit_command.command = COMMAND_MIDI_RECEIVED;
    transmit_command.length = 4;
    transmit_command.payload[0] = chan;
    transmit_command.payload[1] = 0x0B;
    transmit_command.payload[2] = cc;
    transmit_command.payload[3] = value;
    pccomm_send_command();
}

void pccomm_log_midi_pc(uint8_t chan, uint8_t program)
{
    transmit_command.command = COMMAND_MIDI_RECEIVED;
    transmit_command.length = 4;
    transmit_command.payload[0] = chan;
    transmit_command.payload[1] = 0x0C;
    transmit_command.payload[2] = program;
    transmit_command.payload[3] = 0;
    pccomm_send_command();
}

void pccomm_set_patch_value(uint8_t patch_id, uint8_t property, uint8_t value)
{
    transmit_command.command = COMMAND_SET_PATCH_VALUE;
    transmit_command.length = 3;
    
    transmit_command.payload[0] = patch_id;
    transmit_command.payload[1] = property;
    transmit_command.payload[2] = value;
    pccomm_send_command();
}

void pccomm_set_patch_value_str(uint8_t patch_id, uint8_t property, char * value)
{
    transmit_command.command = COMMAND_SET_PATCH_VALUE;
    transmit_command.length = 2 + strlen(value) + 1;
    transmit_command.payload[0] = patch_id;
    transmit_command.payload[1] = property;
    int i;
    for(i = 0; i < strlen(value)+1; i++) transmit_command.payload[2+i] = value[i];
    transmit_command.payload[1+i] = 0;
    //value[i++] = 0;
    pccomm_send_command();
}

void pccomm_select_patch(uint8_t patch_no)
{
    transmit_command.command = COMMAND_SELECT_PATCH;
    transmit_command.length = 1;// 1
    
    transmit_command.payload[0] = patch_no;
    
    pccomm_send_command();
}


void pccomm_set_model_value(uint8_t model_id, uint8_t property, int8_t value)
{
    transmit_command.command = COMMAND_SET_MODEL_VALUE;
    transmit_command.length = 3;
    
    transmit_command.payload[0] = model_id;
    transmit_command.payload[1] = property;
    transmit_command.payload[2] = value;
    pccomm_send_command();
}

void pccomm_set_model_value_int(uint8_t model_id, uint8_t property, uint16_t value)
{
    transmit_command.command = COMMAND_SET_MODEL_VALUE;
    transmit_command.length = 4;
    
    transmit_command.payload[0] = model_id;
    transmit_command.payload[1] = property;
    transmit_command.payload[2] = (value >> 8) & 0xFF;
    transmit_command.payload[3] = value & 0xFF;
    pccomm_send_command();
}

void pccomm_set_model_value_str(uint8_t model_id, uint8_t property, char * value)
{
    transmit_command.command = COMMAND_SET_MODEL_VALUE;
    transmit_command.length = 2 + strlen(value) + 1;
    
    transmit_command.payload[0] = model_id;
    transmit_command.payload[1] = property;
    int i;
    for(i = 0; i < strlen(value)+2; i++) transmit_command.payload[2+i] = value[i];
    transmit_command.payload[i] = 0;
    //value[i++] = 0;
    pccomm_send_command();
}