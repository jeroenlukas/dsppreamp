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
#include "74hc165.h"
#include "i2c_simplifier.h"
#include "patches.h"
#include "misc_func.h"
#include "pccomm.h"




/* Flags */
volatile bool fTimer0 = false;
volatile bool f_front_event = false;
volatile bool f_front_btn_models_pressed = false;
volatile bool f_front_btn_system_pressed = false;
volatile bool f_front_btn_next_pressed = false;
volatile bool f_tmr_slow = false;

volatile uint32_t shift_register_data;
volatile char strbuff[32];

volatile uint8_t tmr_slow = 0;
volatile uint8_t test_gain = 1;

/* Interrupt callbacks */
void Tmr0Interrupt(void);

/* Parametric EQ calc example 
double boost = -5;
double freq = 1100;
double Q = 6;
double gain=1;
double Fs = 48000;    
double a0, omega, sn, cs, alpha, Ax, A1, A2, B0, B1, B2, gainlinear;

Ax = pow(10, boost/40); //ok
omega = 2*M_PI*freq / Fs; //ok
sn = sin(omega);// ok < RADIANS! not degrees
cs = cos(omega); // ok
alpha = sn / (2 * Q);//ok

a0 = 1 + (alpha/Ax);//ok
A1 = -(2 * cs) / a0;//ok
A2 = (1-(alpha / Ax)) / a0; //ok
gainlinear = pow(10, gain/20) / a0;//ok
B0 = (1+(alpha*Ax))*gainlinear;//ok
B1 = -(2*cs)*gainlinear;
B2 = (1-(alpha*Ax))*gainlinear;
// Took about 6.7 ms
 * */

bool prev_btn_models = true;
bool prev_btn_system = true;
bool prev_btn_next = true;

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
     
    patch_load(0); // dummy
    
    while(1)
    {            
     
        if(f_front_event)
        {
            f_front_event = false;
            // ..
            LCD_SetCursor(0,3);
            uitoa((uint16_t)shift_register_data , strbuff);
            LCD_Write_Str(strbuff);
        }
        
      
        
        if(fTimer0)
        {
            fTimer0 = false;   
            
        }
        
        if(f_tmr_slow)
        {
            f_tmr_slow = false;
            //test_gain += 1;
            //if(test_gain > 100) test_gain = 1;
            //patch_current_set_gain(test_gain);
            
            // test
            //EUSART2_Write('H');
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
            pccomm_byte_received(EUSART2_Read());
            // USB data
            //pccomm_byte_received(EUSART2_Read());
            //LCD_SetCursor(0, 2);
            //LCD_Write_Str("Comm:");
            //LCD_Write_Char(EUSART2_Read());            
        }

    }
    return;
}

void Tmr0Interrupt(void)
{
    //IO_LED1_Toggle();
    fTimer0 = true;
    
    front_led_store_SetHigh();
    
    // Readout shift registers on front panel
    shift_register_data = sn74hc165_read();
    if(shift_register_data != 0xFFFFFF)
    {
        f_front_event = true;
    }  
    
    
    // Poll buttons (models, system and next )
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
    
    front_led_store_SetLow();
    
    // slow timer
    tmr_slow++;
    if(tmr_slow == 15)
    {
        tmr_slow = 0;
        f_tmr_slow = true;
    }
}