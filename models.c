/*
 * File:   models.c
 * Author: Jeroen
 *
 * Created on August 13, 2020, 7:42 PM
 */


#include "xc.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "config.h"
#include "models.h"
#include "cd4052.h"
#include "24aa64.h"
#include "lcd_pcf8574.h"
#include "adau1701.h"
#include "sigma/DSPPreamp_IC_1_PARAM.h"
#include "patches.h"
#include "pccomm.h"

#include "misc_func.h"

void model_read_model_from_eeprom(uint8_t model_id)
{
    // Read model settings from eeprom    
    
    eeprom_read_multi(EEPROM_MODEL_START + (model_id * (sizeof current_patch.model)), &(current_patch.model), sizeof current_patch.model);       
    
}

void model_apply_model(model_t model)
{
    mux_set_channel(model.channel - 1);
    
    // Set pre-gain filter
    
    
}

void model_initialize(uint8_t code)
{
    model_t model;
    char strbuf[128];
    
    if(code == 0xBB)
    {
        model.channel = 0;
        model.dspdistortion_alpha = 0.6;
        model.dspdistortion_asymmetry = 0.03;
        model.bypass = 0;
        model.dspdistortion_volume = -5;
        model.dspdistortion_gain_min = 0;
        model.dspdistortion_gain_max = 30;
        model.pre_cutoff_freq = 80;
        model.pre_order = 2;        
        model.post_low_cutoff_freq = 80;
        model.post_low_order = 2;
        model.post_low_gain_min = -10;
        model.post_low_gain_max = 10;
        model.post_mid_Q = 1.1;
        model.post_mid_freq = 400;
        model.post_mid_gain_min = -20;
        model.post_mid_gain_max = 10;
        model.post_high_gain_min = -10;
        model.post_high_gain_max = 10;
        model.post_presence_freq_min = 3000;
        model.post_presence_freq_max = 8000;
        model.post_presence_order = 2;
        model.zinput = 10;
        
        char str_num[16];
        char str_model[10];
        
        pccomm_log_message("Initializing models...");
        for(int i = 0; i < EEPROM_MODEL_NUM; i++)
        {            
            model.post_mid_freq++;
            uitoa(i+1, str_num);
            strcpy(model.name, "Mdl");
            strcat(model.name, str_num);
            model_store(i, model);
        }
        sprintf(strbuf, "Done. Struct size: %d Total size: %d", sizeof (model_t), sizeof (model_t) * EEPROM_MODEL_NUM);
        pccomm_log_message(strbuf);
    }
}

void model_current_store(uint8_t model_id)
{
    model_t model_data;    
    char strbuf[128];
    
    eeprom_write_multi(EEPROM_MODEL_START + (model_id * (sizeof current_patch.model)), &(current_patch.model), sizeof current_patch.model);
    sprintf(strbuf, "Model %d (%s) stored.", model_id+1, current_patch.model.name);
    pccomm_log_message(strbuf);    
}

void model_store(uint8_t model_id, model_t model_data)
{    
    char strbuf[128];
    eeprom_write_multi(EEPROM_MODEL_START + (model_id * (sizeof model_data)), &(model_data), sizeof model_data);
    
    sprintf(strbuf, "Model %d (%s) stored.", model_id+1, model_data.name);
    pccomm_log_message(strbuf);
}

void model_current_set_name(char * name)
{ 
    if(strlen(name) < 9)
    {
        strcpy(current_patch.model.name, name);        
    }
}

void model_current_set_bypass(uint8_t bypass)
{
    current_patch.model.bypass = bypass;
    // Pregain
    if(bypass & (1 << 3))
    {
        adau1701_write_fixed(MOD_PREGAIN_BYPASS_ALG0_STAGE0_MONOSWITCHNOSLEW_ADDR, 0x00000000);
        adau1701_write_fixed(MOD_PREGAIN_BYPASS_ALG0_STAGE1_MONOSWITCHNOSLEW_ADDR, 0x00800000);            
    }
    else
    {
        adau1701_write_fixed(MOD_PREGAIN_BYPASS_ALG0_STAGE0_MONOSWITCHNOSLEW_ADDR, 0x00800000);
        adau1701_write_fixed(MOD_PREGAIN_BYPASS_ALG0_STAGE1_MONOSWITCHNOSLEW_ADDR, 0x00000000);   
    }
    
    // Distortion
    if(bypass & (1 << 2))
    {
        adau1701_write_fixed(MOD_DSPDISTORTION_BYPASS_ALG0_MONOSWSLEW_ADDR, 1);        
    }
    else
    {
        adau1701_write_fixed(MOD_DSPDISTORTION_BYPASS_ALG0_MONOSWSLEW_ADDR, 0);      
    }
    
    // Analog
    if(bypass & (1 << 1))
    {
        adau1701_write_fixed(MOD_ANALOG_BYPASS_MONOSWSLEW_ADDR, 0);        
    }
    else
    {
        adau1701_write_fixed(MOD_ANALOG_BYPASS_MONOSWSLEW_ADDR, 1);            
    }
    
    // Postgain
    if((bypass & 1))
    {
        adau1701_write_fixed(MOD_POSTGAIN_PO_BYPASS_ALG0_STAGE0_MONOSWITCHNOSLEW_ADDR, 0x00000000);
        adau1701_write_fixed(MOD_POSTGAIN_PO_BYPASS_ALG0_STAGE1_MONOSWITCHNOSLEW_ADDR, 0x00800000);       
    }
    else 
    {
        adau1701_write_fixed(MOD_POSTGAIN_PO_BYPASS_ALG0_STAGE0_MONOSWITCHNOSLEW_ADDR, 0x00800000);
        adau1701_write_fixed(MOD_POSTGAIN_PO_BYPASS_ALG0_STAGE1_MONOSWITCHNOSLEW_ADDR, 0x00000000);   
    }
}

// Private function
void model_current_set_postgain_mid(int8_t boost, int16_t freq, double Q)
{
    double gainlinear;
    double B0, B1, B2, A1, A2;
    
    boost = boost / 2;
    
    // Offset the boost, so we have a mid notch by default.
    boost -= 3; 
    
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


void model_current_set_dspdistortion_alpha(double alpha)
{
    // Alpha needs to be divided by 10. The actual alpha range is 0.1 - 10. Function input thus is 1-100
            
    uint16_t sigma_address[2];
    double sigma_data[2];
    
    current_patch.model.dspdistortion_alpha = alpha;
    
    sigma_address[0] = MOD_DSPDISTORTION_SOFTCLIP1_ALG0_SOFTCLIPALGG21ALPHA_ADDR;
    sigma_address[1] = MOD_DSPDISTORTION_SOFTCLIP1_ALG0_SOFTCLIPALGG21ALPHAM1_ADDR;
    
    sigma_data[0] = alpha ;
    sigma_data[1] = 1/alpha;
    
    adau1701_write_multi(2, sigma_address, sigma_data);
}

void model_current_set_dspdistortion_asymmetry(double asymm)
{
    // Asymm needs to be divided by 10. The actual alpha range is 0.1 - ??. Function input thus is 1-???
            
    uint16_t sigma_address[2];
    double sigma_data[2];
    
    current_patch.model.dspdistortion_asymmetry = asymm;
    
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

void model_current_set_postgain_pres_order(uint8_t order)
{    
    if(order > 0 && order < 5)
    {
        current_patch.model.post_presence_order = order;    
        adau1701_write_fixed(MOD_PRES_ORDER_ALG0_MONOSWSLEW_ADDR, (uint32_t)order-1);
    }
}

void model_current_set_postgain_pres_freq_min(int16_t freq)
{
    current_patch.model.post_presence_freq_min = freq;
}
void model_current_set_postgain_pres_freq_max(int16_t freq)
{
    current_patch.model.post_presence_freq_max = freq;
}

void model_current_set_postgain_low_gain_min(int8_t gain_db)
{
    current_patch.model.post_low_gain_min = gain_db;
}

void model_current_set_postgain_low_gain_max(int8_t gain_db)
{
    current_patch.model.post_low_gain_max = gain_db;
}

void model_current_set_postgain_mid_gain_min(int8_t gain_db)
{
    current_patch.model.post_mid_gain_min = gain_db;
}
void model_current_set_postgain_mid_gain_max(int8_t gain_db)
{
    current_patch.model.post_mid_gain_max = gain_db;
}

void model_current_set_postgain_high_gain_min(int8_t gain_db)
{
    current_patch.model.post_high_gain_min = gain_db;
}

void model_current_set_postgain_high_gain_max(int8_t gain_db)
{
    current_patch.model.post_high_gain_max = gain_db;
}

void model_current_set_dspdistortion_volume(int8_t gain_db)
{
    // Gain in dB, but must be made negative!
    /*if(gain_db > 0)
    {
        gain_db = 0;
    }*/
   // gain_db = gain_db * -1;
    
    current_patch.model.dspdistortion_volume = gain_db;
    
    double gain = pow(10, (double)gain_db / 20);
    
    adau1701_write(MOD_DSPDISTORTION_VOLUME_GAIN1940ALGNS4_ADDR, gain);    
}


void model_current_set_pregain_lowcut(uint16_t value)
{    
    current_patch.model.pre_cutoff_freq = value;
    
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
    
    // Again, for the third lowcut filter
    sigma_address[0] = MOD_PREGAIN_LOWCUT3_ALG0_PARAMB00_ADDR;
    sigma_address[1] = MOD_PREGAIN_LOWCUT3_ALG0_PARAMB10_ADDR;
    sigma_address[2] = MOD_PREGAIN_LOWCUT3_ALG0_PARAMA00_ADDR;    
    
    adau1701_write_multi(3, sigma_address, sigma_data);
    
    // Again, for the fourth lowcut filter
    sigma_address[0] = MOD_PREGAIN_LOWCUT4_ALG0_PARAMB00_ADDR;
    sigma_address[1] = MOD_PREGAIN_LOWCUT4_ALG0_PARAMB10_ADDR;
    sigma_address[2] = MOD_PREGAIN_LOWCUT4_ALG0_PARAMA00_ADDR;    
    
    adau1701_write_multi(3, sigma_address, sigma_data);
}

void model_current_set_pregain_lowcut_order(uint8_t order)
{
    if(order > 0 && order < 5)
    {
        current_patch.model.pre_order = order;    
        adau1701_write_fixed(MOD_PREGAIN_ORDER_ALG0_MONOSWSLEW_ADDR, (uint32_t)order-1);
    }
}


