/*
 * File:   main.c
 * Author: Jeroen
 *
 * Created on 10 augustus 2017, 19:53
 */



#include <xc.h>
#include <stdint.h>
#include "config.h"
#include "mcc_generated_files/mcc.h"
#include "lcd_pcf8574.h"
#include "i2c_simplifier.h"
#include "patches.h"
#include "misc_func.h"
#include "pccomm.h"
#include "front.h"
#include "24aa64.h"



/* Flags */
volatile bool fTimer0 = false;

volatile bool f_tmr_slow = false;


volatile char strbuff[32];

volatile uint8_t tmr_slow = 0;
volatile uint8_t test_gain = 1;

/* Interrupt callbacks */
void Tmr0Interrupt(void);




void main(void) 
{    
    uint8_t adcVal;
   
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
    
    // Download firmware to ADAU1701
    default_download_IC_1();
    
    pccomm_log_message("Algorithm loaded");
    
    
     __delay_ms(100);
     
    patch_load(1); // dummy
    
    //eeprom_write_one_byte(4, 'G');
    //__delay_ms(10);
    uint8_t test = eeprom_read_one_byte(4);
    LCD_SetCursor(0,2);
    LCD_Write_Char(test);
    
    
    while(1)
    {            
     
        if(f_front_event)
        {
            f_front_event = false;
            // ..
        }
        
      
        
        if(fTimer0)
        {
            fTimer0 = false;   
            
        }
        
        if(f_tmr_slow)
        {
            f_tmr_slow = false;
        }
        
        if(f_rot_enc_gain_up)
        {
            f_rot_enc_gain_up = false;
            patch_current_set_gain(current_patch.gain + front_rot_enc_increment());
            pccomm_set_patch_value(COMM_PATCH_GAIN, current_patch.gain);
        }
        if(f_rot_enc_gain_down)
        {
            f_rot_enc_gain_down = false;
            patch_current_set_gain(current_patch.gain - front_rot_enc_increment());
            pccomm_set_patch_value(COMM_PATCH_GAIN, current_patch.gain);
        }
        
        if(f_rot_enc_low_up)
        {
            f_rot_enc_low_up = false;
            patch_current_set_low(current_patch.low + front_rot_enc_increment());
            pccomm_set_patch_value(COMM_PATCH_LOW, current_patch.low);
        }
        if(f_rot_enc_low_down)
        {
            f_rot_enc_low_down = false;
            patch_current_set_low(current_patch.low - front_rot_enc_increment());
            pccomm_set_patch_value(COMM_PATCH_LOW, current_patch.low);
        }
        
        if(f_rot_enc_mid_up)
        {
            f_rot_enc_mid_up = false;
            patch_current_set_mid(current_patch.mid + front_rot_enc_increment());
            pccomm_set_patch_value(COMM_PATCH_MID, current_patch.mid);
        }
        if(f_rot_enc_mid_down)
        {
            f_rot_enc_mid_down = false;
            patch_current_set_mid(current_patch.mid - front_rot_enc_increment());
            pccomm_set_patch_value(COMM_PATCH_MID, current_patch.mid);
        }
        
        if(f_rot_enc_high_up)
        {
            f_rot_enc_high_up = false;
            patch_current_set_high(current_patch.high + front_rot_enc_increment());
            pccomm_set_patch_value(COMM_PATCH_HIGH, current_patch.high);
        }
        if(f_rot_enc_high_down)
        {
            f_rot_enc_high_down = false;
            patch_current_set_high(current_patch.high - front_rot_enc_increment());
            pccomm_set_patch_value(COMM_PATCH_HIGH, current_patch.high);
        }
        
        if(f_rot_enc_pres_up)
        {
            f_rot_enc_pres_up = false;
            patch_current_set_presence(current_patch.presence + front_rot_enc_increment());
            pccomm_set_patch_value(COMM_PATCH_PRES, current_patch.presence);
        }
        if(f_rot_enc_pres_down)
        {
            f_rot_enc_pres_down = false;
            patch_current_set_presence(current_patch.presence - front_rot_enc_increment());
            pccomm_set_patch_value(COMM_PATCH_PRES, current_patch.presence);
        }
        
        if(f_rot_enc_vol_up)
        {
            f_rot_enc_vol_up = false;
            patch_current_set_volume(current_patch.volume + front_rot_enc_increment());
            pccomm_set_patch_value(COMM_PATCH_VOLUME, current_patch.volume);
        }
        if(f_rot_enc_vol_down)
        {
            f_rot_enc_vol_down = false;
            patch_current_set_volume(current_patch.volume - front_rot_enc_increment());
            pccomm_set_patch_value(COMM_PATCH_VOLUME, current_patch.volume);
        }
        
        if(f_rot_enc_value_up)
        {
            f_rot_enc_value_up = false;
            patch_load(current_patch_no + 1);
        }
        if(f_rot_enc_value_down)
        {
            f_rot_enc_value_down = false;
            if(current_patch_no > 1)
            {
                patch_load(current_patch_no - 1);
            }
        }
        
        if(f_front_btn_models_pressed)
        {
            f_front_btn_models_pressed = false;
            LCD_SetCursor(0, 1);
            LCD_Write_Str_Padded("Models", 8);
            pccomm_log_message("Models menu");
        }
        if(f_front_btn_system_pressed)
        {
            f_front_btn_system_pressed = false;
            LCD_SetCursor(0, 1);
            LCD_Write_Str_Padded("System", 8);
            pccomm_log_message("System menu");
        }
        if(f_front_btn_next_pressed)
        {
            f_front_btn_next_pressed = false;
            LCD_SetCursor(0, 1);
            LCD_Write_Str_Padded("Next", 8);
            pccomm_log_message("Next parameter");
        }
        
        if(EUSART1_DataReady)
        {
            // MIDI data
            EUSART1_Read();
        }
        
        if(pccomm_frame_ready() == 1)
        {
            pccomm_parse_command();
        }
        
        if(eusart2RxCount > 0)
        {
            // USB data
            pccomm_byte_received(EUSART2_Read());                        
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

    
    front_led_store_SetLow();
    
    // Increase millisecond timer
    millis_inc();
    
    // slow timer
    tmr_slow++;
    if(tmr_slow == 15)
    {
        tmr_slow = 0;
        f_tmr_slow = true;
    }
}