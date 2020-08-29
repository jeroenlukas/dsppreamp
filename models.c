/*
 * File:   models.c
 * Author: Jeroen
 *
 * Created on August 13, 2020, 7:42 PM
 */


#include "xc.h"
#include "config.h"
#include "models.h"
#include "cd4052.h"
#include "24aa64.h"
#include "lcd_pcf8574.h"
#include "adau1701.h"
#include "sigma/DSPPreamp_IC_1_PARAM.h"

model_t model_read_model_from_eeprom(uint8_t model_id)
{
    // Read model settings from eeprom
    model_t model;
    
    model.channel = eeprom_read_model_parameter(model_id, EEPROM_MODEL_INDEX_CHANNEL);
    model.gain_max = eeprom_read_model_parameter(model_id, EEPROM_MODEL_INDEX_GAIN_MAX);
    model.gain_min  = eeprom_read_model_parameter(model_id, EEPROM_MODEL_INDEX_GAIN_MIN);
    
    return model;
}

void model_apply_model(model_t model)
{
    mux_set_channel(model.channel - 1);
    
    // Set pre-gain filter
    
    
}

void model_current_set_postgain_bypass(uint8_t bypass)
{
    if(bypass == 0) // Bypass off, normal operation
    {
        adau1701_write_fixed(MOD_PO_BYPASS_ALG0_STAGE0_MONOSWITCHNOSLEW_ADDR, 0x00800000);
        adau1701_write_fixed(MOD_PO_BYPASS_ALG0_STAGE1_MONOSWITCHNOSLEW_ADDR, 0x00000000);        
    }
    else // Bypass on
    {
        adau1701_write_fixed(MOD_PO_BYPASS_ALG0_STAGE0_MONOSWITCHNOSLEW_ADDR, 0x00000000);
        adau1701_write_fixed(MOD_PO_BYPASS_ALG0_STAGE1_MONOSWITCHNOSLEW_ADDR, 0x00800000);        
    }
    
    
    // Show on LCD
    LCD_SetCursor(0, 1);
    LCD_Write_Str("PoG bypassed ");
    LCD_SetCursor(6, 1);
    //uitoa(value, strbuf);
    //LCD_Write_Str_Padded_Right(strbuf, 3);
}