/*
 * File:   patches.c
 * Author: Jeroen
 *
 * Created on August 13, 2020, 7:46 PM
 */


#include <xc.h>
#include <string.h>

#include "patches.h"
#include "models.h"
//#include "i2c_simplifier.h"
#include "mcp45hvx1.h"
#include "adau1701.h"
#include "config.h"
#include "24aa64.h"
#include "lcd_pcf8574.h"
#include "misc_func.h"
#include "sigma/DSPPreamp_IC_1_PARAM.h"
#include <math.h>



//
char strbuf[20];

void patch_load(uint8_t patch_no)
{
    current_patch_no = patch_no;

    LCD_SetCursor(0,0);
    uitoa(current_patch_no, strbuf);
    LCD_Write_Str_Padded_Right(strbuf, 3);
    
    current_patch.model_id = 3;
    current_patch.model = model_read_model_from_eeprom(current_patch.model_id);    
    
    // Load some dummy values. Should be read from eeprom in future
    
    current_patch.model.gain_min = 0;
    current_patch.model.gain_max = 60;
    current_patch.model.pre_cutoff_freq = 80;
    current_patch.model.post_low_gain_min = -15;
    current_patch.model.post_low_gain_max = 15;
    current_patch.model.post_high_gain_min = -15;
    current_patch.model.post_high_gain_max = 15;
    current_patch.model.post_presence_freq_min = 2000;
    current_patch.model.post_presence_freq_max = 10000;
    current_patch.model.post_mid_Q = 1;
    current_patch.model.post_mid_freq = 400;
    current_patch.model.post_mid_gain_min = -10;
    current_patch.model.post_mid_gain_max  = 10;  
    
    //patch_t patch_load;
    
    eeprom_read_multi(EEPROM_PATCH_START + patch_no * sizeof(current_patch), &current_patch, sizeof(current_patch));
            
/*   
            
    current_patch.gain = 20;
    current_patch.low = 60;
    current_patch.mid = 50;
    current_patch.high = 50;
    current_patch.presence = 60;
    current_patch.volume = 60;*/
    
    model_current_set_dspdistortion_bypass(0);
    
    patch_current_set_gain(current_patch.gain);
    patch_current_set_low(current_patch.low);
    patch_current_set_mid(current_patch.mid);
    patch_current_set_high(current_patch.high);
    patch_current_set_presence(current_patch.presence);
    patch_current_set_volume(current_patch.volume);
    
}


int16_t patch_scale_value(int16_t min, int16_t max, int16_t perc)
{
    int16_t ret = 0;
    
    double interm =  (double)(max - min) / 100;
    
    ret = interm * perc + min;
    return ret;            
}

void patch_current_set_gain(uint8_t value)
{
    if(value > 100)
    {
        value = 100;
    }
    current_patch.gain = value;
    
    uint16_t scaled_value = patch_scale_value(current_patch.model.gain_min, current_patch.model.gain_max, value);
    
   // mcp45hvx1_set_wiper(I2C_ADDRESS_MCP45_PRE_GAIN, scaled_value);
    
    // Update bar
    LCD_SetCursor(12, 1);
    if(value > 88)
    {
        LCD_Write_Char(LCD_CC_BAR_8);
    }
    else
    {
        LCD_Write_Char(value / 13);
    }
    
    // Show on LCD
    LCD_SetCursor(0, 1);
    LCD_Write_Str("Gain: ");
    LCD_SetCursor(6, 1);
    uitoa(value, strbuf);
    LCD_Write_Str_Padded_Right(strbuf, 3);
    
    model_current_set_dspdistortion_gain((double)scaled_value);
}


// Local function
patch_current_set_tonecontrol(double bassboost, double trebleboost, double frequency)
{
    ;
    double Fs = 48000;   
    double freq_t = frequency + 100;
    double freq_b = frequency;
    double cell_gain = 1;
    double boost_t = pow(10, trebleboost/20); // unchanged
    double boost_b = pow(10, bassboost/20);
    double A_T = tan(M_PI * freq_t / Fs);
    double A_B = tan(M_PI * freq_b / Fs);
    double Knum_T = 2 / (1 + (1 / boost_t));
    double Kden_T = 2 / (1 + boost_t);
    double Knum_B = 2 / (1 + (1 / boost_b));
    double Kden_B = 2 / (1 + boost_b);
    double a10 = A_T + Kden_T;
    double a11 = A_T - Kden_T;
    double a20 = (A_B * Kden_B) + 1;
    double a21 = (A_B * Kden_B) - 1;
    double b10 = A_T + Knum_T;
    double b11 = A_T - Knum_T;
    double b20 = (A_B * Knum_B) - 1;
    double b21 = (A_B * Knum_B) + 1;
    double a0 = a10 * a20;
    double A1 = ((a10 * a21) + (a11 * a20)) / a0;
    double A2 = a11 * a21 / a0;
    double gainlinear = pow(10, (cell_gain / 20));
    double B0 = (b10 * b20) / a0 * gainlinear;
    double B1 = ((b10 * b21) + (b11 * b20)) / a0 * gainlinear;
    double B2 = (b11 * b21) / a0 * gainlinear;
        
    uint16_t sigma_address[5];
    double sigma_data[5];
    
    sigma_address[0] = MOD_POSTGAIN_PO_TONECONTROL_ALG0_STAGE0_B0_ADDR;
    sigma_address[1] = MOD_POSTGAIN_PO_TONECONTROL_ALG0_STAGE0_B1_ADDR;
    sigma_address[2] = MOD_POSTGAIN_PO_TONECONTROL_ALG0_STAGE0_B2_ADDR;
    sigma_address[3] = MOD_POSTGAIN_PO_TONECONTROL_ALG0_STAGE0_A1_ADDR;
    sigma_address[4] = MOD_POSTGAIN_PO_TONECONTROL_ALG0_STAGE0_A2_ADDR;
    
    sigma_data[0] = B0;
    sigma_data[1] = B1  ;
    sigma_data[2] = B2  ;
    sigma_data[3] = (A1*-1)  ;
    sigma_data[4] = (A2*-1) ;
    
    adau1701_write_multi(5, sigma_address, sigma_data);
}

void patch_current_set_tonecontrol_center_frequency(double frequency)
{
    double scaled_value_bass = (double)patch_scale_value(current_patch.model.post_low_gain_min, current_patch.model.post_low_gain_max, current_patch.low);     // Unchanged
    double scaled_value_treble = (double)patch_scale_value(current_patch.model.post_high_gain_min, current_patch.model.post_high_gain_max, current_patch.high);  // Unchanged
    patch_current_set_tonecontrol(scaled_value_bass, scaled_value_treble, frequency);
}

void patch_current_set_low(uint8_t value)
{    
    if(value > 100)
    {
        value = 100;
    }
    current_patch.low = value;
   
   
    double scaled_value_bass = (double)patch_scale_value(current_patch.model.post_low_gain_min, current_patch.model.post_low_gain_max, value);     
    double scaled_value_treble = (double)patch_scale_value(current_patch.model.post_high_gain_min, current_patch.model.post_high_gain_max, current_patch.high);  // Unchanged
    
    
    // Update bar
    LCD_SetCursor(14, 1);
    if(value > 88)
    {
        LCD_Write_Char(LCD_CC_BAR_8);
    }
    else
    {
        LCD_Write_Char(value / 13);
    }
    
    // Show on LCD
    LCD_SetCursor(0, 1);
    LCD_Write_Str("Low: ");
    LCD_SetCursor(6, 1);
    uitoa(value, strbuf);
    LCD_Write_Str_Padded_Right(strbuf, 3);
    
    patch_current_set_tonecontrol(scaled_value_bass, scaled_value_treble, (double)current_patch.model.post_mid_freq );
    
   /* double bassboost =  (double)scaled_value;
    double Fs = 48000;   
    double freq_t = 400;
    double freq_b = 400;
    double cell_gain = 1;
    double boost_t = pow(10, (double)patch_scale_value(current_patch.model.post_high_gain_min, current_patch.model.post_high_gain_max, current_patch.high) / 20); // unchanged
    double boost_b = pow(10, bassboost/20);
    double A_T = tan(M_PI * freq_t / Fs);
    double A_B = tan(M_PI * freq_b / Fs);
    double Knum_T = 2 / (1 + (1 / boost_t));
    double Kden_T = 2 / (1 + boost_t);
    double Knum_B = 2 / (1 + (1 / boost_b));
    double Kden_B = 2 / (1 + boost_b);
    double a10 = A_T + Kden_T;
    double a11 = A_T - Kden_T;
    double a20 = (A_B * Kden_B) + 1;
    double a21 = (A_B * Kden_B) - 1;
    double b10 = A_T + Knum_T;
    double b11 = A_T - Knum_T;
    double b20 = (A_B * Knum_B) - 1;
    double b21 = (A_B * Knum_B) + 1;
    double a0 = a10 * a20;
    double A1 = ((a10 * a21) + (a11 * a20)) / a0;
    double A2 = a11 * a21 / a0;
    double gainlinear = pow(10, (cell_gain / 20));
    double B0 = (b10 * b20) / a0 * gainlinear;
    double B1 = ((b10 * b21) + (b11 * b20)) / a0 * gainlinear;
    double B2 = (b11 * b21) / a0 * gainlinear;
        
    uint16_t sigma_address[5];
    double sigma_data[5];
    
    sigma_address[0] = MOD_POSTGAIN_PO_TONECONTROL_ALG0_STAGE0_B0_ADDR;
    sigma_address[1] = MOD_POSTGAIN_PO_TONECONTROL_ALG0_STAGE0_B1_ADDR;
    sigma_address[2] = MOD_POSTGAIN_PO_TONECONTROL_ALG0_STAGE0_B2_ADDR;
    sigma_address[3] = MOD_POSTGAIN_PO_TONECONTROL_ALG0_STAGE0_A1_ADDR;
    sigma_address[4] = MOD_POSTGAIN_PO_TONECONTROL_ALG0_STAGE0_A2_ADDR;
    
    sigma_data[0] = B0;
    sigma_data[1] = B1  ;
    sigma_data[2] = B2  ;
    sigma_data[3] = (A1*-1)  ;
    sigma_data[4] = (A2*-1) ;
    
    adau1701_write_multi(5, sigma_address, sigma_data);*/
}


patch_t patch_get_current(void)
{
    return current_patch;
}


void patch_current_set_high(uint8_t value)
{   
    if(value > 100)
    {
        value = 100;
    }
    current_patch.high = value;
    
    //int16_t scaled_value;    
    
    //scaled_value = patch_scale_value(current_patch.model.post_high_gain_min, current_patch.model.post_high_gain_max, value);
    double scaled_value_bass = (double)patch_scale_value(current_patch.model.post_low_gain_min, current_patch.model.post_low_gain_max, current_patch.low);     // Unchanged
    double scaled_value_treble = (double)patch_scale_value(current_patch.model.post_high_gain_min, current_patch.model.post_high_gain_max, value);  
    
    
    // Update bar
    LCD_SetCursor(16, 1);
    if(value > 88)
    {
        LCD_Write_Char(LCD_CC_BAR_8);
    }
    else
    {
        LCD_Write_Char(value / 13);
    }
    
    // Show on LCD
    LCD_SetCursor(0, 1);
    LCD_Write_Str("High: ");
    LCD_SetCursor(6, 1);
    uitoa(value, strbuf);
    LCD_Write_Str_Padded_Right(strbuf, 3);
    
    patch_current_set_tonecontrol(scaled_value_bass, scaled_value_treble, (double)current_patch.model.post_mid_freq );
    
    // Calculate coeffs here
    //adau1701_write(666, scaled_value);
    /* Parametric EQ calc example */
    /*double boost = scaled_value;
    double freq = 400;current_patch.model.po;
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
    // Took about 6.7 ms*/
   // value = value / 10;
    /*double trebleboost =  (double)scaled_value;
    double Fs = 48000;   
    double freq_t = 400;
    double freq_b = 400;
    double cell_gain = 1;
    double boost_t = pow(10, trebleboost/20);
    double boost_b = pow(10, (double)patch_scale_value(current_patch.model.post_low_gain_min, current_patch.model.post_low_gain_max, current_patch.low) / 20); // unchanged
    double A_T = tan(M_PI * freq_t / Fs);
    double A_B = tan(M_PI * freq_b / Fs);
    double Knum_T = 2 / (1 + (1 / boost_t));
    double Kden_T = 2 / (1 + boost_t);
    double Knum_B = 2 / (1 + (1 / boost_b));
    double Kden_B = 2 / (1 + boost_b);
    double a10 = A_T + Kden_T;
    double a11 = A_T - Kden_T;
    double a20 = (A_B * Kden_B) + 1;
    double a21 = (A_B * Kden_B) - 1;
    double b10 = A_T + Knum_T;
    double b11 = A_T - Knum_T;
    double b20 = (A_B * Knum_B) - 1;
    double b21 = (A_B * Knum_B) + 1; 
    double a0 = a10 * a20;
    double A1 = ((a10 * a21) + (a11 * a20)) / a0;
    double A2 = a11 * a21 / a0;
    double gainlinear = pow(10, (cell_gain / 20));
    double B0 = (b10 * b20) / a0 * gainlinear;
    double B1 = ((b10 * b21) + (b11 * b20)) / a0 * gainlinear;
    double B2 = (b11 * b21) / a0 * gainlinear;
    
    uint16_t sigma_address[5];
    double sigma_data[5];
    
    sigma_address[0] = MOD_POSTGAIN_PO_TONECONTROL_ALG0_STAGE0_B0_ADDR;
    sigma_address[1] = MOD_POSTGAIN_PO_TONECONTROL_ALG0_STAGE0_B1_ADDR;
    sigma_address[2] = MOD_POSTGAIN_PO_TONECONTROL_ALG0_STAGE0_B2_ADDR;
    sigma_address[3] = MOD_POSTGAIN_PO_TONECONTROL_ALG0_STAGE0_A1_ADDR;
    sigma_address[4] = MOD_POSTGAIN_PO_TONECONTROL_ALG0_STAGE0_A2_ADDR;
    
    sigma_data[0] = B0;
    sigma_data[1] = B1  ;
    sigma_data[2] = B2  ;
    sigma_data[3] = (A1*-1)  ;
    sigma_data[4] = (A2*-1) ;
    
    adau1701_write_multi(5, sigma_address, sigma_data);*/
}




void patch_current_set_volume(uint8_t value)
{    
    if(value > 100)
    {
        value = 100;
    }
    current_patch.volume = value;
    
    float scaled_value;
    scaled_value = (float)value / 100; // Should be logarithmic    
    
    // Update bar
    LCD_SetCursor(19, 1);
    if(value > 88)
    {
        LCD_Write_Char(LCD_CC_BAR_8);
    }
    else
    {
        LCD_Write_Char(value / 13);
    }
    
    // Show on LCD
    LCD_SetCursor(0, 1);
    LCD_Write_Str("Vol: ");
    LCD_SetCursor(6, 1);
    uitoa(value, strbuf);
    LCD_Write_Str_Padded_Right(strbuf, 3);
    
    // Calculate coeffs here
    adau1701_write(MOD_PO_VOLUME_ALG0_TARGET_ADDR, scaled_value);
    adau1701_write(MOD_PO_VOLUME_ALG0_STEP_ADDR, 0.000244140625);
}

void patch_current_set_mid(uint8_t value)
{    
    if(value > 100)
    {
        value = 100;
    }
     current_patch.mid = value;
    
    int16_t scaled_value;
    scaled_value = patch_scale_value(current_patch.model.post_mid_gain_min, current_patch.model.post_mid_gain_max, value);
    
    // Update bar
    LCD_SetCursor(15, 1);
    if(value > 88)
    {
        LCD_Write_Char(LCD_CC_BAR_8);
    }
    else
    {
        LCD_Write_Char(value / 13);
    }
    
    // Show on LCD
    LCD_SetCursor(0, 1);
    LCD_Write_Str("Mid: ");
    LCD_SetCursor(6, 1);
    uitoa(value, strbuf);
    LCD_Write_Str_Padded_Right(strbuf, 3);
    
    // Calculate coeffs here
    model_current_set_postgain_mid_boost(scaled_value);
}

void patch_current_set_presence(uint8_t value)
{    
    if(value > 100)
    {
        value = 100;
    }
    current_patch.presence = value;
    
    int16_t scaled_value;    
    
    scaled_value = patch_scale_value(current_patch.model.post_presence_freq_min, current_patch.model.post_presence_freq_max, value);
    
    // Update bar
    LCD_SetCursor(17, 1);
    if(value > 88)
    {
        LCD_Write_Char(LCD_CC_BAR_8);
    }
    else
    {
        LCD_Write_Char(value / 13);
    }
    
    // Show on LCD
    LCD_SetCursor(0, 1);
    LCD_Write_Str("Pres: ");
    LCD_SetCursor(6, 1);
    uitoa(value, strbuf);
    LCD_Write_Str_Padded_Right(strbuf, 3);
    
    double A1 = pow(2.7, -2 * M_PI * ((double)scaled_value/48000.0));
    double B0 = 1.0 - A1;
    double B1 = 0.0;
   
    uint16_t sigma_address[5];
    double sigma_data[5];
    
    sigma_address[0] = MOD_POSTGAIN_PO_PRESENCE_ALG0_PARAMB10_ADDR;
    sigma_address[1] = MOD_POSTGAIN_PO_PRESENCE_ALG0_PARAMB00_ADDR;
    sigma_address[2] = MOD_POSTGAIN_PO_PRESENCE_ALG0_PARAMA00_ADDR;
    
    sigma_data[0] = B1;
    sigma_data[1] = B0;
    sigma_data[2] = A1;
    
    adau1701_write_multi(3, sigma_address, sigma_data);
    
    // Again, for the second presence filter
    sigma_address[0] = MOD_POSTGAIN_PO_PRESENCE2_ALG0_PARAMB10_ADDR;
    sigma_address[1] = MOD_POSTGAIN_PO_PRESENCE2_ALG0_PARAMB00_ADDR;
    sigma_address[2] = MOD_POSTGAIN_PO_PRESENCE2_ALG0_PARAMA00_ADDR;
    
    
    adau1701_write_multi(3, sigma_address, sigma_data);
}