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
        adau1701_write_fixed(MOD_POSTGAIN_PO_BYPASS_ALG0_STAGE0_MONOSWITCHNOSLEW_ADDR, 0x00800000);
        adau1701_write_fixed(MOD_POSTGAIN_PO_BYPASS_ALG0_STAGE1_MONOSWITCHNOSLEW_ADDR, 0x00000000);        
    }
    else // Bypass on
    {
        adau1701_write_fixed(MOD_POSTGAIN_PO_BYPASS_ALG0_STAGE0_MONOSWITCHNOSLEW_ADDR, 0x00000000);
        adau1701_write_fixed(MOD_POSTGAIN_PO_BYPASS_ALG0_STAGE1_MONOSWITCHNOSLEW_ADDR, 0x00800000);        
    }
}

void model_current_set_dspdistortion_bypass(uint8_t bypass)
{
    if(bypass == 0)
    {
        adau1701_write_fixed(MOD_DSPDISTORTION_DSPDIST_BYPASS_MONOSWSLEW_ADDR, 0);        
    }
    else
    {
        adau1701_write_fixed(MOD_DSPDISTORTION_DSPDIST_BYPASS_MONOSWSLEW_ADDR, 1);        
    }
}

void model_current_set_dspdistortion_alpha(uint8_t alpha)
{
    // Alpha needs to be divided by 10. The actual alpha range is 0.1 - 10. Function input thus is 1-100
    
            
            
    uint16_t sigma_address[2];
    double sigma_data[2];
    
    sigma_address[0] = MOD_DSPDISTORTION_SOFTCLIP1_ALG0_SOFTCLIPALGG21ALPHA_ADDR;
    sigma_address[1] = MOD_DSPDISTORTION_SOFTCLIP1_ALG0_SOFTCLIPALGG21ALPHAM1_ADDR;
    
    
    
    
    sigma_data[0] = (double)alpha / 10;
    sigma_data[1] = 1/((double)alpha / 10);
    
    
    
    
    adau1701_write_multi(2, sigma_address, sigma_data);
}