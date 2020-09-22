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
#include "pccomm.h"
//#include "front.h"
#include "lcd_pcf8574.h"
#include "misc_func.h"
#include "sigma/DSPPreamp_IC_1_PARAM.h"
#include <math.h>




//
char strbuf[20];

void patch_initialize(uint8_t code)
{
    eeprom_patch_t patch;
    
    if(code == 0xAF)
    {
        pccomm_log_message("Initializing all patches...");

        patch.gain = 20;
        patch.low = 60;
        patch.mid = 40;
        patch.high = 60;
        patch.presence = 30;
        patch.noise_gate = 0;
        patch.volume = 50;

        char str_num[16];
        char str_patch[10];

        for(int i = 0; i < EEPROM_PATCH_NUM; i++)
        {
            patch.model_id = 0;
            uitoa(i+1, str_num);
            strcpy(patch.name, "Ptch");
            strcat(patch.name, str_num);
            patch_store(i, patch);
        }
        
        pccomm_log_message("Done.");
    }
}



void patch_load(uint8_t patch_no)
{
    current_patch_no = patch_no;

    
    
    //current_patch.model_id = 3;
    //current_patch.model = model_read_model_from_eeprom(current_patch.model_id);    
    
    // First read the model
    
    
    // Load some dummy values. Should be read from eeprom in future
    
  
    
    //patch_t patch_load;
    
    eeprom_patch_t patch_data;
    
    eeprom_read_multi(EEPROM_PATCH_START + (patch_no * sizeof patch_data), &patch_data, sizeof patch_data);            
    
    strcpy(current_patch.name, patch_data.name);
    current_patch.model_id = patch_data.model_id;
    current_patch.gain = patch_data.gain;
    current_patch.low = patch_data.low;
    current_patch.mid = patch_data.mid;
    current_patch.high = patch_data.high;
    current_patch.presence = patch_data.presence;
    current_patch.volume = patch_data.volume;
    
    //model_read_model_from_eeprom(current_patch.model_id);
    eeprom_read_multi(EEPROM_MODEL_START + (current_patch.model_id * (sizeof current_patch.model)), &(current_patch.model), sizeof current_patch.model);      
    
    // Override some settings
    //current_patch.model.gain_min = 0;
    //current_patch.model.gain_max = 50;
    //current_patch.model.pre_cutoff_freq = 80;
   // current_patch.model.post_low_gain_min = -15;
   // current_patch.model.post_low_gain_max = 15;
    //current_patch.model.post_high_gain_min = -15;
    //current_patch.model.post_high_gain_max = 15;
    //current_patch.model.post_presence_freq_min = 2000;
    //current_patch.model.post_presence_freq_max = 10000;
   // current_patch.model.post_mid_Q = 1;
    //current_patch.model.post_mid_freq = 400;
    //current_patch.model.post_mid_gain_min = -10;
    //current_patch.model.post_mid_gain_max  = 10;  
    
/*   
            
    current_patch.gain = 20;
    current_patch.low = 60;
    current_patch.mid = 50;
    current_patch.high = 50;
    current_patch.presence = 60;
    current_patch.volume = 60;*/
    
    model_current_set_dspdistortion_bypass(0);
    model_current_set_pregain_lowcut(current_patch.model.pre_cutoff_freq);
    model_current_set_dspdistortion_alpha(current_patch.model.dspdistortion_alpha);
    model_current_set_dspdistortion_asymmetry(current_patch.model.dspdistortion_asymmetry);
    model_current_set_dspdistortion_volume(current_patch.model.dspdistortion_volume);
    
    
    //model_current_set_postgain_mid_freq(current_patch.model.post_mid_freq);
    
    patch_current_set_volume(current_patch.volume, SENDER_EXT);    
    patch_current_set_gain(current_patch.gain, SENDER_EXT);
    patch_current_set_low(current_patch.low, SENDER_EXT);
    patch_current_set_mid(current_patch.mid, SENDER_EXT);
    patch_current_set_high(current_patch.high, SENDER_EXT);
    patch_current_set_presence(current_patch.presence, SENDER_EXT);
    
    // Update display
    LCD_SetCursor(0,0);
    uitoa(current_patch_no + 1, strbuf);
    LCD_Write_Str_Zero_Padded_Right(strbuf, 3);
    
    //for(int i = 0; i < 8; i++) LCD_Write_Char(current_patch.name[i]);
    LCD_Write_Str_Padded(current_patch.name, 8);
    
    /*
    LCD_SetCursor(0,2);
    LCD_Write_Str("M");
    uitoa(current_patch.model_id + 1, strbuf);
    LCD_Write_Str_Zero_Padded_Right(strbuf, 2);
    */
    lcd_display_normal();
    
    // Send info to PC
    pccomm_set_model_value_str(COMM_MODEL_NAME, current_patch.model.name);
    pccomm_set_model_value_int(COMM_MODEL_PREGAIN_LOWCUT_FREQ, current_patch.model.pre_cutoff_freq);
    pccomm_set_model_value(COMM_MODEL_PREGAIN_LOWCUT_ORDER, current_patch.model.pre_order);
    pccomm_set_model_value(COMM_MODEL_PREGAIN_BYPASS, current_patch.model.pregain_bypass);
    pccomm_set_model_value_int(COMM_MODEL_INPUT_Z, current_patch.model.zinput);
    pccomm_set_model_value(COMM_MODEL_DSPDISTORTION_BYPASS, current_patch.model.dspdistortion_bypass);
    pccomm_set_model_value(COMM_MODEL_DSPDISTORTION_GAIN_MIN, current_patch.model.dspdistortion_gain_min);
    pccomm_set_model_value(COMM_MODEL_DSPDISTORTION_GAIN_MAX, current_patch.model.dspdistortion_gain_max);
    pccomm_set_model_value(COMM_MODEL_DSPDISTORTION_ALPHA, current_patch.model.dspdistortion_alpha * 10);
    pccomm_set_model_value(COMM_MODEL_DSPDISTORTION_ASYMMETRY, current_patch.model.dspdistortion_asymmetry * 100);
    pccomm_set_model_value(COMM_MODEL_DSPDISTORTION_VOLUME, current_patch.model.dspdistortion_volume);
    
    pccomm_set_model_value(COMM_MODEL_POSTGAIN_LOW_GAIN_MIN, current_patch.model.post_low_gain_min);
    pccomm_set_model_value(COMM_MODEL_POSTGAIN_LOW_GAIN_MAX, current_patch.model.post_low_gain_max);    
    
    pccomm_set_model_value_int(COMM_MODEL_POSTGAIN_MID_FREQ, current_patch.model.post_mid_freq);
    pccomm_set_model_value(COMM_MODEL_POSTGAIN_MID_Q, current_patch.model.post_mid_Q * 10);
    pccomm_set_model_value(COMM_MODEL_POSTGAIN_MID_GAIN_MIN, current_patch.model.post_mid_gain_min);
    pccomm_set_model_value(COMM_MODEL_POSTGAIN_MID_GAIN_MAX, current_patch.model.post_mid_gain_max);
    
    pccomm_set_model_value(COMM_MODEL_POSTGAIN_HIGH_GAIN_MIN, current_patch.model.post_high_gain_min);
    pccomm_set_model_value(COMM_MODEL_POSTGAIN_HIGH_GAIN_MAX, current_patch.model.post_high_gain_max);
    
    pccomm_set_model_value_int(COMM_MODEL_POSTGAIN_PRES_FREQ_MIN, current_patch.model.post_presence_freq_min);
    pccomm_set_model_value_int(COMM_MODEL_POSTGAIN_PRES_FREQ_MAX, current_patch.model.post_presence_freq_max);
    
    
    pccomm_set_patch_value_str(COMM_PATCH_NAME, current_patch.name);
    pccomm_set_patch_value(COMM_PATCH_MODEL, current_patch.model_id);
    pccomm_set_patch_value(COMM_PATCH_GAIN, current_patch.gain);
    pccomm_set_patch_value(COMM_PATCH_LOW, current_patch.low);
    pccomm_set_patch_value(COMM_PATCH_MID, current_patch.mid);
    pccomm_set_patch_value(COMM_PATCH_HIGH, current_patch.high);
    pccomm_set_patch_value(COMM_PATCH_PRES, current_patch.presence);
    pccomm_set_patch_value(COMM_PATCH_VOLUME, current_patch.volume);
    
    
}

void patch_current_set_name(char * name)
{
    //for(int i = 0;)
    if(strlen(name) < 9)
    {
        strcpy(current_patch.name, name);

        LCD_SetCursor(3,0);
        LCD_Write_Str_Padded(current_patch.name, 8);
    }
}

void patch_current_store(uint8_t patch_no)
{
    // Prepare eeprom_patch
    eeprom_patch_t patch_data;
    
    for(int i = 0; i < 9; i++)
        patch_data.name[i] = current_patch.name[i];
    patch_data.model_id = current_patch.model_id;
    patch_data.gain = current_patch.gain;
    patch_data.low = current_patch.low;
    patch_data.mid = current_patch.mid;
    patch_data.high = current_patch.high;
    patch_data.presence = current_patch.presence;
    patch_data.volume = current_patch.volume;
    patch_data.noise_gate = current_patch.noise_gate;
    
    
    eeprom_write_multi(EEPROM_PATCH_START + (patch_no * sizeof patch_data), &patch_data, sizeof patch_data);
    
    pccomm_log_message("Patch is stored");
    lcd_display_temporary("[stored]");
}

void patch_store(uint8_t patch_no, eeprom_patch_t patch_data)
{
    eeprom_write_multi(EEPROM_PATCH_START + (patch_no * sizeof patch_data), &patch_data, sizeof patch_data);
    
    pccomm_log_message("Patch stored");
 
        
    lcd_display_temporary("[stored]");
}


int16_t patch_scale_value(int16_t min, int16_t max, int16_t perc)
{
    int16_t ret = 0;
    
    double interm =  (double)(max - min) / 100;
    
    ret = interm * perc + min;
    return ret;            
}

void patch_current_set_model(uint8_t model_id)
{
    current_patch.model_id = model_id;
}

void patch_current_set_gain(uint8_t value, uint8_t sender)
{
    if(value > 100)
    {
        value = 100;
    }
    
    current_patch.gain = value;
    
    uint16_t scaled_value = patch_scale_value(current_patch.model.dspdistortion_gain_min, current_patch.model.dspdistortion_gain_max, value);
    
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
    
    if(sender == SENDER_USER)
    {
        // Show on LCD
        char value_str[12];
        strcpy(strbuf, "Gain: ");
        uitoa(value, value_str);
        strcat(strbuf, value_str);        
        
        lcd_display_temporary(strbuf);
    }
    model_current_set_dspdistortion_gain((double)scaled_value);
}


// Local function
patch_current_set_tonecontrol(double bassboost, double trebleboost, double frequency)
{
    
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

void patch_current_set_low(uint8_t value, uint8_t sender)
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
    
    if(sender == SENDER_USER)
    {
        // Show on LCD
      /*  LCD_SetCursor(0, 1);
        LCD_Write_Str("Low: ");
        LCD_SetCursor(6, 1);
        uitoa(value, strbuf);
        LCD_Write_Str_Padded_Right(strbuf, 3);*/
        char value_str[12];
        strcpy(strbuf, "Low: ");
        uitoa(value, value_str);
        strcat(strbuf, value_str);        
        
        lcd_display_temporary(strbuf);
    }

    patch_current_set_tonecontrol(scaled_value_bass, scaled_value_treble, (double)current_patch.model.post_mid_freq );
    
}


patch_t patch_get_current(void)
{
    return current_patch;
}


void patch_current_set_high(uint8_t value, uint8_t sender)
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
    
    if(sender == SENDER_USER)
    {
        // Show on LCD
        char value_str[12];
        strcpy(strbuf, "High: ");
        uitoa(value, value_str);
        strcat(strbuf, value_str);        
        
        lcd_display_temporary(strbuf);
    }
    patch_current_set_tonecontrol(scaled_value_bass, scaled_value_treble, (double)current_patch.model.post_mid_freq );
    
}




void patch_current_set_volume(uint8_t value, uint8_t sender)
{    
    if(value > 100)
    {
        value = 100;
    }
    current_patch.volume = value;
    
    double scaled_value;
    scaled_value = (double)value / 100; // Should be logarithmic    
    
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
    
    if(sender == SENDER_USER)
    {
        // Show on LCD
        char value_str[12];
        strcpy(strbuf, "Vol: ");
        uitoa(value, value_str);
        strcat(strbuf, value_str);        
        
        lcd_display_temporary(strbuf);
    }
    
    // Calculate coeffs here
    adau1701_write(MOD_PO_VOLUME_ALG0_TARGET_ADDR, scaled_value);
    adau1701_write(MOD_PO_VOLUME_ALG0_STEP_ADDR, 0.000244140625);
}

void patch_current_set_mid(uint8_t value, uint8_t sender)
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
    
    if(sender == SENDER_USER)
    {
        // Show on LCD
        char value_str[12];
        strcpy(strbuf, "Mid: ");
        uitoa(value, value_str);
        strcat(strbuf, value_str);        
        
        lcd_display_temporary(strbuf);
    }

    // Calculate coeffs here
    model_current_set_postgain_mid_boost(scaled_value);
}

void patch_current_set_presence(uint8_t value, uint8_t sender)
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
    
    if(sender == SENDER_USER)
    {
        // Show on LCD
        char value_str[12];
        strcpy(strbuf, "Pres: ");
        uitoa(value, value_str);
        strcat(strbuf, value_str);        
        
        lcd_display_temporary(strbuf);
    }
    
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