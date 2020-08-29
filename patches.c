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
#include "lcd_pcf8574.h"
#include "misc_func.h"
#include "sigma/DSPPreamp_IC_1_PARAM.h"

patch_t current_patch;

//
char strbuf[20];

patch_load(uint8_t patch_no)
{
    current_patch.model_id = 3;
    current_patch.model = model_read_model_from_eeprom(current_patch.model_id);    
    
    
    
    current_patch.gain = 50; // read all this from eeprom
    
    current_patch.low = 2;
    
    
    // Load model first
    
    
    //memcpy(&current_patch.model, &model, sizeof(model_t));
    
}


int16_t patch_scale_value(int16_t min, int16_t max, int16_t perc)
{
    int16_t ret = 0;
    
    ret = ((max - min) / 100) * perc + min;
    return ret;            
}

void patch_current_set_gain(uint8_t value)
{
    current_patch.gain = value;
    
    uint32_t scaled_value = patch_scale_value(current_patch.model.gain_min, current_patch.model.gain_max, value);
    
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
}



void patch_current_set_low(uint8_t value)
{    
    current_patch.low = value;
    
    uint32_t scaled_value;
    scaled_value = patch_scale_value(current_patch.model.post_low_gain_min, current_patch.model.post_low_gain_max, value);
    
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
    
    // Calculate coeffs here
    adau1701_write(666, scaled_value);
}


void patch_current_set_volume(uint8_t value)
{    
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
     current_patch.mid = value;
    
    uint32_t scaled_value;
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
    adau1701_write(666, scaled_value);
}

