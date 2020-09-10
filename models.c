/*
 * File:   models.c
 * Author: Jeroen
 *
 * Created on August 13, 2020, 7:42 PM
 */


#include "xc.h"
#include <math.h>
#include "config.h"
#include "models.h"
#include "cd4052.h"
#include "24aa64.h"
#include "lcd_pcf8574.h"
#include "adau1701.h"
#include "sigma/DSPPreamp_IC_1_PARAM.h"
#include "patches.h"

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

// Private function
void model_current_set_postgain_mid(int8_t boost, int16_t freq, double Q)
{
    double gainlinear;
    double B0, B1, B2, A1, A2;
    
    boost = boost / 2;
    
    // Offset the boost, so we have a mid notch by default.
    boost -= 10; 
    
    if(boost == 0)
    {
        gainlinear = 1.1220184; // Linear gain = 0 dB
        B0 = gainlinear;
        B1 = 0;
        B2 = 0;
        A1 = 0;
        A2 = 0;
    }
    
    else
    {
        double Ax = pow(10, (double)boost/40);
        double omega = 2 * M_PI * (double)freq / 48000;
        double sn = sin(omega);
        double cs = cos(omega);
        double alpha = sn / (2 * Q);
        double a0 = 1 + (alpha / Ax);
        A1 = - (2 * cs) / a0;
        A2 = (1 - (alpha / Ax)) / a0;
        gainlinear = pow(10, 1 / 20) / a0;
        B0 = (1 + (alpha * Ax)) * gainlinear;
        B1 = - (2* cs) * gainlinear;
        B2 = (1 - (alpha * Ax)) * gainlinear;
    }
    
    uint16_t sigma_address[5];
    double sigma_data[5];
    
    sigma_address[0] = MOD_POSTGAIN_MID1_ALG0_STAGE0_B0_ADDR;
    sigma_address[1] = MOD_POSTGAIN_MID1_ALG0_STAGE0_B1_ADDR;
    sigma_address[2] = MOD_POSTGAIN_MID1_ALG0_STAGE0_B2_ADDR;
    sigma_address[3] = MOD_POSTGAIN_MID1_ALG0_STAGE0_A0_ADDR;
    sigma_address[4] = MOD_POSTGAIN_MID1_ALG0_STAGE0_A1_ADDR;
    
    sigma_data[0] = B0;
    sigma_data[1] = B1;
    sigma_data[2] = B2;
    sigma_data[3] = A1 * -1;
    sigma_data[4] = A2 * -1;
    
    adau1701_write_multi(5, sigma_address, sigma_data);
            
    sigma_address[0] = MOD_POSTGAIN_MID2_ALG0_STAGE0_B0_ADDR;
    sigma_address[1] = MOD_POSTGAIN_MID2_ALG0_STAGE0_B1_ADDR;
    sigma_address[2] = MOD_POSTGAIN_MID2_ALG0_STAGE0_B2_ADDR;
    sigma_address[3] = MOD_POSTGAIN_MID2_ALG0_STAGE0_A0_ADDR;
    sigma_address[4] = MOD_POSTGAIN_MID2_ALG0_STAGE0_A1_ADDR;
    adau1701_write_multi(5, sigma_address, sigma_data);
}

void model_current_set_postgain_mid_Q(double Q)
{    
    
    if(Q > 0.2)
    {
        current_patch.model.post_mid_Q = Q;  
        
        
        int8_t boost = patch_scale_value(current_patch.model.post_mid_gain_min, current_patch.model.post_mid_gain_max, current_patch.mid);
        model_current_set_postgain_mid(boost, current_patch.model.post_mid_freq, Q);
    }
}


void model_current_set_postgain_mid_freq(int16_t freq)
{
    if(freq > 100)
    {
        current_patch.model.post_mid_freq = freq;        
        
        int8_t boost = patch_scale_value(current_patch.model.post_mid_gain_min, current_patch.model.post_mid_gain_max, current_patch.mid);
        model_current_set_postgain_mid(boost, freq, current_patch.model.post_mid_Q);
        
        // Also update the post gain tonecontrol center frequency
        patch_current_set_tonecontrol_center_frequency((double)freq);
    }
}


void model_current_set_postgain_mid_boost(int16_t boost)
{
    if(boost > -30)
    {
        //current_patch.model.post_mid_freq = freq;        
        
        //int8_t boost = patch_scale_value(current_patch.model.post_mid_gain_min, current_patch.model.post_mid_gain_max, current_patch.mid);
        model_current_set_postgain_mid(boost, current_patch.model.post_mid_freq, current_patch.model.post_mid_Q);
    }
}


void model_current_set_dspdistortion_bypass(uint8_t bypass)
{
    if(bypass == 0)
    {
        adau1701_write_fixed(MOD_DSPDISTORTION_BYPASS_MONOSWSLEW_ADDR, 0);        
    }
    else
    {
        adau1701_write_fixed(MOD_DSPDISTORTION_BYPASS_MONOSWSLEW_ADDR, 1);        
    }
}


void model_current_set_analog_bypass(uint8_t bypass)
{
    if(bypass == 0)
    {
        adau1701_write_fixed(MOD_ANALOG_BYPASS_MONOSWSLEW_ADDR, 1);        
    }
    else
    {
        adau1701_write_fixed(MOD_ANALOG_BYPASS_MONOSWSLEW_ADDR, 0);        
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

void model_current_set_dspdistortion_asymmetry(double asymm)
{
    // Asymm needs to be divided by 10. The actual alpha range is 0.1 - ??. Function input thus is 1-???
            
    uint16_t sigma_address[2];
    double sigma_data[2];
    
    sigma_address[0] = MOD_DSPDISTORTION_ASYMMETRY_DCINPALG1_ADDR;
    
    sigma_data[0] = asymm ;
    
    
    adau1701_write_multi(1, sigma_address, sigma_data);
}

void model_current_set_dspdistortion_gain(double gain_db)
{
    // Gain in dB, 0-72 dB
    if(gain_db > 72.0)
    {
        gain_db = 72;
    }
    
    double gain = pow(10, gain_db/3 / 20);
    
    // Actually the total gain of 72 dB is spread accross 3 gain stages with 24 dB max gain
    
    adau1701_write(MOD_DSPDISTORTION_GAIN1_GAIN1940ALGNS3_ADDR, gain);    
    adau1701_write(MOD_DSPDISTORTION_GAIN2_GAIN1940ALGNS5_ADDR, gain);  
    adau1701_write(MOD_DSPDISTORTION_GAIN3_GAIN1940ALGNS6_ADDR, gain);
}

void model_current_set_dspdistortion_volume(uint8_t gain_db)
{
    // Gain in dB, but must be made negative!
    /*if(gain_db > 0)
    {
        gain_db = 0;
    }*/
   // gain_db = gain_db * -1;
    
    double gain = pow(10, (double)gain_db*-1 / 20);
    
    adau1701_write(MOD_DSPDISTORTION_VOLUME_GAIN1940ALGNS4_ADDR, gain);    
}


void model_current_set_pregain_lowcut(uint16_t value)
{    
    
    
    double A1 = pow(2.7, -2 * M_PI * ((double)value/48000.0));
    
    double B1 = (1.0 + A1) * 0.5;
    double B0 = -B1;
   
    uint16_t sigma_address[5];
    double sigma_data[5];
    
    sigma_address[0] = MOD_PREGAIN_LOWCUT_ALG0_PARAMB00_ADDR;
    sigma_address[1] = MOD_PREGAIN_LOWCUT_ALG0_PARAMB10_ADDR;
    sigma_address[2] = MOD_PREGAIN_LOWCUT_ALG0_PARAMA00_ADDR;
    
    sigma_data[0] = B0;
    sigma_data[1] = B1;
    sigma_data[2] = A1;
    
    adau1701_write_multi(3, sigma_address, sigma_data);
    
    // Again, for the second lowcut filter
    sigma_address[0] = MOD_PREGAIN_LOWCUT2_ALG0_PARAMB00_ADDR;
    sigma_address[1] = MOD_PREGAIN_LOWCUT2_ALG0_PARAMB10_ADDR;
    sigma_address[2] = MOD_PREGAIN_LOWCUT2_ALG0_PARAMA00_ADDR;
    
    
    adau1701_write_multi(3, sigma_address, sigma_data);
}