/*
 * File:   main.c
 * Author: Jeroen
 *
 * Created on 10 augustus 2017, 19:53
 */



#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "config.h"
#include "mcc_generated_files/mcc.h"
#include "lcd_pcf8574.h"
#include "i2c_simplifier.h"
#include "patches.h"
#include "misc_func.h"
#include "pccomm.h"
#include "front.h"
#include "24aa64.h"
#include "midi.h"



/* Flags */
volatile bool fTimer0 = false;

volatile bool f_tmr_slow = false;
volatile bool f_tmr_1s = false;

volatile char strbuff[128];

volatile uint8_t tmr_slow = 0;
volatile uint16_t tmr_1s = 0;
volatile uint8_t test_gain = 1;

/* Interrupt callbacks */
void Tmr0Interrupt(void);




void main(void) 
{    
    
    __delay_ms(50);
    
    // Initialize peripherals and system (configured by MCC)
    SYSTEM_Initialize();
    
    TMR0_SetInterruptHandler(Tmr0Interrupt);
    
    INTERRUPT_PeripheralInterruptEnable();
    INTERRUPT_GlobalInterruptEnable();
    
    front_led_midi_SetHigh();
    __delay_ms(100);
    front_led_midi_SetLow();              
    
    LCD_Init();
    
    lcd_load_custom_characters();
    
    LCD_Home();
    LCD_Write_Str("DSPPreamp!");
    
    pccomm_log_message("Startup");
    
    // Download firmware to ADAU1701
    default_download_IC_1();    
    
    sprintf(strbuff, "Startup completed after %d ms", millis() + 50);
    pccomm_log_message(strbuff);
    
    __delay_ms(1000);
    LCD_Home();
    LCD_Write_Str_Padded("001Clean", 12);
    LCD_SetCursor(12, 0);
    LCD_Write_Str("G-LMHP-V");
    LCD_SetCursor(12, 1);
    LCD_Write_Char(LCD_CC_BAR_3);
    LCD_SetCursor(14, 1);
    LCD_Write_Char(LCD_CC_BAR_5);
    LCD_SetCursor(15, 1);
    LCD_Write_Char(LCD_CC_BAR_1);
    LCD_SetCursor(16, 1);
    LCD_Write_Char(LCD_CC_BAR_4);
    LCD_SetCursor(17, 1);
    LCD_Write_Char(LCD_CC_BAR_6);
    LCD_SetCursor(19, 1);
    LCD_Write_Char(LCD_CC_BAR_7);
    
    patch_load(0);     
    
    while(1)
    {            
     
        if(f_front_event)
        {
            f_front_event = false;
            // ..
        }
        
        if(f_tmr_1s)
        {
            f_tmr_1s = false;
            pccomm_heartbeat();
        }
        
        if(fTimer0)
        {
            fTimer0 = false;   
            if(temporary_display && millis() > millis_temporary_display)
            {
                lcd_display_normal();
            }
        }
        
        if(f_tmr_slow)
        {
            f_tmr_slow = false;
        }
        
        if(f_rot_enc_gain_up)
        {
            f_rot_enc_gain_up = false;
            patch_current_set_gain(current_patch.gain + front_rot_enc_increment(), SENDER_USER);
            pccomm_set_patch_value(0xFF, COMM_PATCH_GAIN, current_patch.gain);
        }
        if(f_rot_enc_gain_down)
        {
            f_rot_enc_gain_down = false;
            if(current_patch.gain > front_rot_enc_increment())
                patch_current_set_gain(current_patch.gain - front_rot_enc_increment(), SENDER_USER);
            else 
                patch_current_set_gain(0, SENDER_USER);
            pccomm_set_patch_value(0xFF, COMM_PATCH_GAIN, current_patch.gain);
        }
        
        if(f_rot_enc_low_up)
        {
            f_rot_enc_low_up = false;
            patch_current_set_low(current_patch.low + front_rot_enc_increment(), SENDER_USER);
            pccomm_set_patch_value(0xFF, COMM_PATCH_LOW, current_patch.low);
        }
        if(f_rot_enc_low_down)
        {
            f_rot_enc_low_down = false;
            if(current_patch.low > front_rot_enc_increment())
                patch_current_set_low(current_patch.low - front_rot_enc_increment(), SENDER_USER);
            else
                patch_current_set_low(0, SENDER_USER);
            pccomm_set_patch_value(0xFF, COMM_PATCH_LOW, current_patch.low);
        }
        
        if(f_rot_enc_mid_up)
        {
            f_rot_enc_mid_up = false;
            patch_current_set_mid(current_patch.mid + front_rot_enc_increment(), SENDER_USER);
            pccomm_set_patch_value(0xFF, COMM_PATCH_MID, current_patch.mid);
        }
        if(f_rot_enc_mid_down)
        {
            f_rot_enc_mid_down = false;
            if(current_patch.mid > front_rot_enc_increment())
                patch_current_set_mid(current_patch.mid - front_rot_enc_increment(), SENDER_USER);
            else
                patch_current_set_mid(0, SENDER_USER);
            pccomm_set_patch_value(0xFF, COMM_PATCH_MID, current_patch.mid);
        }
        
        if(f_rot_enc_high_up)
        {
            f_rot_enc_high_up = false;
            patch_current_set_high(current_patch.high + front_rot_enc_increment(), SENDER_USER);
            pccomm_set_patch_value(0xFF, COMM_PATCH_HIGH, current_patch.high);
        }
        if(f_rot_enc_high_down)
        {
            f_rot_enc_high_down = false;
            if(current_patch.high > front_rot_enc_increment())
                patch_current_set_high(current_patch.high - front_rot_enc_increment(), SENDER_USER);
            else
                patch_current_set_high(0, SENDER_USER);
            pccomm_set_patch_value(0xFF, COMM_PATCH_HIGH, current_patch.high);
        }
        
        if(f_rot_enc_pres_up)
        {
            f_rot_enc_pres_up = false;
            patch_current_set_presence(current_patch.presence + front_rot_enc_increment(), SENDER_USER);
            pccomm_set_patch_value(0xFF, COMM_PATCH_PRES, current_patch.presence);
        }
        if(f_rot_enc_pres_down)
        {
            f_rot_enc_pres_down = false;
            if(current_patch.presence > front_rot_enc_increment())
                patch_current_set_presence(current_patch.presence - front_rot_enc_increment(), SENDER_USER);
            else
                patch_current_set_presence(0, SENDER_USER);
            pccomm_set_patch_value(0xFF, COMM_PATCH_PRES, current_patch.presence);
        }
        
        if(f_rot_enc_vol_up)
        {
            f_rot_enc_vol_up = false;
            patch_current_set_volume(current_patch.volume + front_rot_enc_increment(), SENDER_USER);
            pccomm_set_patch_value(0xFF, COMM_PATCH_VOLUME, current_patch.volume);
        }
        if(f_rot_enc_vol_down)
        {
            f_rot_enc_vol_down = false;
            if(current_patch.volume > front_rot_enc_increment())
                patch_current_set_volume(current_patch.volume - front_rot_enc_increment(), SENDER_USER);
            else
                patch_current_set_volume(0, SENDER_USER);
            pccomm_set_patch_value(0xFF, COMM_PATCH_VOLUME, current_patch.volume);
        }
        
        if(f_rot_enc_value_up)
        {
            f_rot_enc_value_up = false;
            patch_load(current_patch_no + 1);
            
            pccomm_select_patch(current_patch_no);
        }
        if(f_rot_enc_value_down)
        {
            f_rot_enc_value_down = false;
            if(current_patch_no > 0)
            {
                patch_load(current_patch_no - 1);
                
                pccomm_select_patch(current_patch_no);
            }
        }
        
        if(f_front_btn_gain_pressed)
        {
            pccomm_log_message("Gain");
            f_front_btn_gain_pressed = false;
        }
        if(f_front_btn_store_pressed)
        {
            f_front_btn_store_pressed = false;                        
            patch_current_store(current_patch_no);
        }
        if(f_front_btn_exit_pressed)
        {
            f_front_btn_exit_pressed = false;
            pccomm_log_message("Exit");
        }
        
        if(f_front_btn_models_pressed)
        {
            f_front_btn_models_pressed = false;            
            pccomm_log_message("Models menu");
        }
        if(f_front_btn_system_pressed)
        {
            f_front_btn_system_pressed = false;            
            pccomm_log_message("System menu");
        }
        if(f_front_btn_next_pressed)
        {
            f_front_btn_next_pressed = false;
            pccomm_log_message("Next parameter");
        }
        
        if(eusart1RxCount > 0)
        {
            // MIDI data
            if(!f_midi_pc_received && !f_midi_cc_received) // Only read from buffer if there are no pending PC or CC messages to be processed
                midi_byte_received(EUSART1_Read());
        }
        if(midi_pc_received())
        {
            f_midi_pc_received = false;
            
            pccomm_log_midi_pc(midi_message.channel, midi_message.program);
            patch_load(midi_message.program);
            pccomm_select_patch(current_patch_no);
        }
        if(midi_cc_received())
        {
            f_midi_cc_received = false;
            
            pccomm_log_midi_cc(midi_message.channel, midi_message.cc, midi_message.cc_value);
        }        
           
        
        
        if(eusart2RxCount > 0)
        {
            // USB data
            pccomm_byte_received(EUSART2_Read());                        
        }
        
        if(pccomm_frame_ready() == 1)
        {
            pccomm_parse_command();
        }

    }
    return;
}

void Tmr0Interrupt(void)
{
    //IO_LED1_Toggle();
    fTimer0 = true;
    
    //front_led_store_SetHigh();
    
    // Readout shift registers on front panel
    front_check_buttons();
    
    
    
    // Increase millisecond timer
    millis_inc();
    
    // slow timer
    tmr_slow++;
    if(tmr_slow == 50)
    {
        tmr_slow = 0;
        front_check_level();
        f_tmr_slow = true;
    }
    
    tmr_1s++;
    if(tmr_1s == 1000)
    {
        tmr_1s = 0;
        f_tmr_1s = true;
    }
          
    
    //front_led_store_SetLow(); // total 464us
}