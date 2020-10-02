/*
 * File:   midi.c
 * Author: Jeroen
 *
 * Created on 29 september 2020, 21:01
 */


#include <xc.h>
#include <stdbool.h>
#include "midi.h"

#define STATE_IDLE      0
#define STATE_STATUS    1
#define STATE_DATA      2

#define MIDI_PC     0x0C
#define MIDI_CC     0x0B

uint8_t receive_state_machine;



void midi_byte_received(uint8_t data)
{
    if(data == 0xFE) 
    {
        // Ignore active sensing
        return;
    }
    if(data & 128)
    {
        // Its a status byte
        receive_state_machine = STATE_STATUS;
        
        midi_message.channel = data & 0b00001111;
        midi_message.type = data >> 4;        
        
        midi_message.cc = 0xFF;
        midi_message.cc_value = 0xFF;
    }
    else
    {
        if(midi_message.type == MIDI_PC)
        {
            midi_message.program = data;
            
            f_midi_pc_received = true;
        }
        if(midi_message.type == MIDI_CC)
        {
            if(midi_message.cc == 0xFF)
            {
                midi_message.cc = data;
            }
            else if(midi_message.cc_value == 0xFF)
            {
                midi_message.cc_value = data;
                f_midi_cc_received = true;
            }
            
        }
    }
}

bool midi_pc_received(void)
{
    return f_midi_pc_received;
}

bool midi_cc_received(void)
{
    return f_midi_cc_received;
}