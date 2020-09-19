/*
 * File:   front.c
 * Author: Jeroen
 *
 * Created on 5 september 2020, 17:24
 */


#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "config.h"
#include "74hc165.h"
#include <stdbool.h>
#include "front.h"
#include "pccomm.h"
#include "misc_func.h"

#define RE_GAIN     0   
#define RE_LOW      1
#define RE_MID      2
#define RE_HIGH     3
#define RE_PRES     4
#define RE_VOL      5
#define RE_VALUE    6

#define RE_UP       1
#define RE_DOWN     2

#define RE_SLOW     1
#define RE_FAST     2


/* Rotary encoder */
typedef struct rotary_encoder {
    uint8_t rot_enc;
    uint8_t prev_rot_enc;
    uint8_t data;
} rotary_encoder_t;

volatile rotary_encoder_t rot_enc[7];

bool prev_btn_models = true;
bool prev_btn_system = true;
bool prev_btn_next = true;

uint32_t last_rot_enc_timestamp = 0;

uint8_t rot_enc_speed = RE_SLOW;


volatile uint32_t shift_register_data = 0;


uint8_t a_last = 1;
uint8_t b_last = 1;

uint8_t process_rotary_encoder(uint8_t encoder)
{
    uint8_t ret = 0;
    uint8_t pin_a, pin_b;
    
    switch(encoder)
    {
        case RE_GAIN:
            pin_a = 1;
            pin_b = 2;
            break;
        case RE_LOW:
            pin_a = 4;
            pin_b = 5;
            break;
        case RE_MID:
            pin_a = 7;
            pin_b = 8;
            break;
        case RE_HIGH:
            pin_a = 10;
            pin_b = 11;
            break;
        case RE_PRES:
            pin_a = 13;
            pin_b = 14;
            break;
        case RE_VOL:
            pin_a = 16;
            pin_b = 17;
            break;
        case RE_VALUE:
            pin_a = 19;
            pin_b = 20;
            break;            
        default:
            break;
    }
    
    rot_enc[encoder].rot_enc = 0;
    uint8_t a = (shift_register_data >> pin_a) & 1;
    uint8_t b = (shift_register_data >> pin_b) & 1;

#if 1
    rot_enc[encoder].rot_enc =  ((a << 1) + b) & 3; 

    if(rot_enc[encoder].rot_enc != rot_enc[encoder].prev_rot_enc)
    {                
        rot_enc[encoder].data = (rot_enc[encoder].data << 2);
        rot_enc[encoder].data += (rot_enc[encoder].rot_enc & 3);
        if(rot_enc[encoder].data == 0b10000111) 
        {                                 
            ret = RE_UP;

        }
        else if(rot_enc[encoder].data == 0b01001011)
        {
            ret = RE_DOWN;                
        }
    }
    
    rot_enc[encoder].prev_rot_enc = rot_enc[encoder].rot_enc;
    
#endif
    
#if 0
    if(a != rot_enc[encoder].prev_rot_enc && a == 1)
    {
        if(b != a)
        {
            ret = RE_UP;
        }
        else
            ret = RE_DOWN;
    }
        
    rot_enc[encoder].prev_rot_enc = a;
#endif

    if(ret > 0)
    {
        if(millis() - last_rot_enc_timestamp < ROT_ENC_FAST_THRESHOLD)
        {
            rot_enc_speed = RE_FAST;
        }
        else rot_enc_speed = RE_SLOW;
 
        last_rot_enc_timestamp = millis();
    }
    
    return ret;
}



void front_check_buttons(void)
{
    shift_register_data = sn74hc165_read();
    
   // if(shift_register_data != 0x037FFFFE) 
    switch(process_rotary_encoder(RE_GAIN))
    {
        case RE_UP:
            f_rot_enc_gain_up = true;
            break;
        case RE_DOWN:
            f_rot_enc_gain_down = true;
            break;
        default:
            break;
    }
    
    switch(process_rotary_encoder(RE_LOW))
    {
        case RE_UP:
            f_rot_enc_low_up = true;
            break;
        case RE_DOWN:
            f_rot_enc_low_down = true;
            break;
        default:
            break;
    }
    
    switch(process_rotary_encoder(RE_MID))
    {
        case RE_UP:            
            f_rot_enc_mid_up = true;
            break;
        case RE_DOWN:            
            f_rot_enc_mid_down = true;
            break;
        default:
            break;
    }
    
    switch(process_rotary_encoder(RE_HIGH))
    {
        case RE_UP:            
            f_rot_enc_high_up = true;
            break;
        case RE_DOWN:            
            f_rot_enc_high_down = true;
            break;
        default:
            break;
    }
    
    switch(process_rotary_encoder(RE_PRES))
    {
        case RE_UP:
            f_rot_enc_pres_up = true;
            break;
        case RE_DOWN:
            f_rot_enc_pres_down = true;
            break;
        default:
            break;
    }
        
    switch(process_rotary_encoder(RE_VOL))
    {
        case RE_UP:
            f_rot_enc_vol_up = true;
            break;
        case RE_DOWN:
            f_rot_enc_vol_down = true;
            break;
        default:
            break;
    }
    
    switch(process_rotary_encoder(RE_VALUE))
    {
        case RE_UP:
            f_rot_enc_value_up = true;
            break;
        case RE_DOWN:
            f_rot_enc_value_down = true;
            break;
        default:
            break;
    }    
        
    
    // Poll other buttons (models, system and next )
    if(front_btn_models_GetValue() < prev_btn_models)
    {
        f_front_btn_models_pressed = true;        
    }
    if(front_btn_system_GetValue() < prev_btn_system)
    {
        f_front_btn_system_pressed = true;        
    }
    if(front_btn_next_GetValue() < prev_btn_next)
    {
        f_front_btn_next_pressed = true;        
    }
        
            
    prev_btn_models = front_btn_models_GetValue();
    prev_btn_system = front_btn_system_GetValue();
    prev_btn_next = front_btn_next_GetValue();
}

uint8_t front_rot_enc_increment(void)
{
    if(rot_enc_speed == RE_SLOW)
    {
        return ROT_ENC_INCREMENT_SLOW;
    }
    else return ROT_ENC_INCREMENT_FAST;
}