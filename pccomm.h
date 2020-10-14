/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef PCCOMM_H
#define	PCCOMM_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define COMMAND_GET_MODEL_VALUE     1
#define COMMAND_GET_PATCH_VALUE     2
#define COMMAND_SET_MODEL_VALUE     3
#define COMMAND_SET_PATCH_VALUE     4
#define COMMAND_STORE_CURRENT_MODEL 6
#define COMMAND_STORE_CURRENT_PATCH 7
#define COMMAND_MIDI_RECEIVED       8
#define COMMAND_LOG_MESSAGE         9
#define COMMAND_SELECT_PATCH        10
#define COMMAND_HEARTBEAT           11

#define COMMAND_INITIALIZE_PATCHES  124
#define COMMAND_INITIALIZE_MODELS   125

typedef struct frames
{
    uint8_t command;
    uint8_t length;
    uint8_t payload[128];
} frame_t;


void pccomm_byte_received(uint8_t data);
void pccomm_parse_command(void);
uint8_t pccomm_frame_ready(void);

void pccomm_log_message(char * text);
void pccomm_log_midi_cc(uint8_t chan, uint8_t cc, uint8_t value);
void pccomm_log_midi_pc(uint8_t chan, uint8_t program);
void pccomm_heartbeat(void);

void pccomm_set_patch_value(uint8_t patch_id, uint8_t property, uint8_t value);
void pccomm_set_patch_value_str(uint8_t patch_id, uint8_t property, char * value);

void pccomm_select_patch(uint8_t patch_no);

void pccomm_set_model_value(uint8_t model_id, uint8_t property, int8_t value);
void pccomm_set_model_value_str(uint8_t model_id, uint8_t property, char * value);
void pccomm_set_model_value_int(uint8_t model_id, uint8_t property, uint16_t value);

#endif	

