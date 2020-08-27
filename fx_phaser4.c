/*
 * File:   s_beeptest.c
 * Author: Jeroen
 *
 * Created on 22 september 2017, 21:21
 */

#include <xc.h>
#include <stdint.h>
#include "fx_phaser4.h"
#include "sigma/phaser4_IC_1.h"
#include "sigma/phaser4_IC_1_PARAM.h"
#include "sigma/phaser4_IC_1_REG.h"
#include "mcc_generated_files/mcc.h"

// Sigma project related
#define DEVICE_ADDR_ 0x68

#define PRESET_LED_FLASH_TIME   70

unsigned char preset = 0; // 0 is no preset
unsigned char prevStage = 0;
unsigned char prevWave = 0;
unsigned char prevMod = 0;

void btnPresetPushed()
{
    if(preset < 3)
    {
        preset++;
    }
    else preset = 0;
    
  
}



void potChanged(uint8_t pot, uint8_t value)
{
    uint8_t ix;
    float dp;
    float fb;
    uint32_t fb_fixed;
    float rt;
    uint32_t rt_fixed;
    uint8_t wave;
     //uint8_t sw[4] = {0,0,0,0};
    uint32_t sens_fixed;
    float float_value;
    float sens = 0.0;
            
    uint32_t dp_fixed;
    
    switch(pot)
    {
        case 0: // Depth
            //float dp;
            

            // !!
           // value = 250;

            dp = (float)value / (float)255;

            dp_fixed = dp * 0x800000;    

            SIGMA_WRITE_SAFELOAD(0, MOD_CTRL_DEPTH_ALG0_TARGET_ADDR, dp_fixed);
            break;
            
        case 1: // Feedback            
            fb = (float)value / (float)255;
            fb_fixed = fb * 0x800000;

            SIGMA_WRITE_SAFELOAD(0, MOD_CTRL_FEEDBACK_ALG0_TARGET_ADDR, fb_fixed);
            break;
            
        case 2: // Stages
//            ix = value / 6;
            if(value < ZONE_STAGE_2)
            {
                ix = 0;
            }
            else if(value < ZONE_STAGE_4)
            {
                ix = 1;
            }
            else if(value < ZONE_STAGE_6)
            {
                ix = 2;                
            }
            else if(value < ZONE_STAGE_8)
            {
                ix = 3;
            }
            else if(value < ZONE_STAGE_10)
            {
                ix = 4;
            }
            else if(value < ZONE_STAGE_12)
            {
                ix = 5;
            }
            
            setStages(ix);
            
            if(ix != prevStage)
            {
                FlashPresetLed();            
            }
            
            prevStage = ix;
            
            break;
            
        case 3: // Rate
            rt = (float)value / (float)255;
            rt_fixed = rt * 0x800000;

            SIGMA_WRITE_SAFELOAD(0, MOD_RATEGEN_CTRL_RATE_ALG0_TARGET_ADDR, rt_fixed);
            break;
            
        case 4: // Waveform
            if(value < ZONE_WAVE_TRIANGLE)
            {
                wave = 5; // Triangle
            }
            else if(value < ZONE_WAVE_SINE)
            {
                wave = 0; // Sine
            }
            else if(value < ZONE_WAVE_RAMPUP)
            {
                wave = 3; // Rampup
            }
            else if(value < ZONE_WAVE_RAMPDOWN)
            {
                wave = 4; // Rampdown
            }
            else if(value < ZONE_WAVE_SQUARE)
            {
                wave = 1;// Square
            }
            else if(value < ZONE_WAVE_STEP)
            {
                wave = 2; // Step
            }
            else if(value < ZONE_WAVE_STOP)
            {
                wave = 6; // Stop
            }


            else wave = 0;  // 

            SIGMA_WRITE_SAFELOAD(0, MOD_WAVEGEN_CTRL_WAVE_MONOSWSLEW_ADDR, wave);
            
            if(wave != prevWave)
            {
                FlashPresetLed();
            }
            
            prevWave = wave;
            
            break;
        case 5:
            // ..
            break;
        case 6:
            //..
            break;
        case 7:
            if(value < ZONE_MOD_DISABLED)
            {
                ix = 0;
            }
            else if(value < ZONE_MOD_SPEED_UP)
            {
                ix = 1;
                sens = ((((float)value - (float)ZONE_MOD_DISABLED) / ((float)ZONE_MOD_SPEED_DOWN - (float)ZONE_MOD_SPEED_UP)) / (float)6);
                sens_fixed  = sens * 0x800000;
            }
            else if(value < ZONE_MOD_SPEED_DOWN)
            {
                ix = 2;
                sens = (((float)value - (float)ZONE_MOD_SPEED_UP) / (float)(  ZONE_MOD_MIX - ZONE_MOD_SPEED_DOWN)) / (float)6;
                sens_fixed  = sens * 0x800000;
            }
            else ix = 0;

            SIGMA_WRITE_SAFELOAD(0, MOD_RATEGEN_CTRL_MOD_SELECT_MONOSWSLEW_ADDR, ix);
            __delay_ms(1);
            SIGMA_WRITE_SAFELOAD(0, MOD_RATEGEN_CTRL_MOD_SENS_GAIN1940ALGNS4_ADDR, sens_fixed);
            
            if(ix != prevMod)
            {
                FlashPresetLed();
            }
            
            prevMod = ix;
                
            break;
            
        default:
            break;
    }
}


void setStages(uint8_t stages)
{
    float offset = 0.88; // 0.88 is default offset for 4stage. A LOWER offset will result in HIGHER notch frequencies
    float width = 0.089; // 0.089 is default for 4stage. 
    
    switch(stages)
    {
        case 0:
            offset = 0.87;
            width = 0.09;
            break;
            
        case 1:
            // 4 stages
            offset = 0.88;
            width = 0.089;
            break;
        case 2:
            // 6 stages
            offset = 0.86;
            width = 0.08;
            break;
        case 3:
            // 8 stages
            offset = 0.83;
            width = 0.078;
            break;
        case 4:
            // 10 stages
            offset = 0.83;
            width = 0.078;
            break;
        case 5:
            // 12 stages
            offset = 0.83;
            width = 0.078;
            break;
        default:
            break;
    }
    
    // In this case, set the stages (4/6/8/10/12)    
    SIGMA_WRITE_SAFELOAD(0, MOD_CTRL_OFFSET_DCINPALG1_ADDR, (uint32_t)(offset * 0x800000));
    SIGMA_WRITE_SAFELOAD(0, MOD_CTRL_WIDTH_GAIN1940ALGNS1_ADDR, (uint32_t)(width * 0x800000));
    SIGMA_WRITE_SAFELOAD(0, MOD_CTRL_STAGES_MONOSWSLEW_ADDR, stages);
}

void FlashPresetLed(void)
{    
    // Briefly flash the preset led
    switch(preset)
    {
        case 0:
            IO_LEDp2_SetHigh();
            __delay_ms(PRESET_LED_FLASH_TIME);
            IO_LEDp2_SetLow();
            break;
        case 1:
            IO_LEDp1_SetLow();
            __delay_ms(PRESET_LED_FLASH_TIME);
            IO_LEDp1_SetHigh();
            break;
        case 2:
            IO_LEDp2_SetLow();
            __delay_ms(PRESET_LED_FLASH_TIME);
            IO_LEDp2_SetHigh();
            break;
        case 3:
            IO_LEDp3_SetLow();
            __delay_ms(PRESET_LED_FLASH_TIME);
            IO_LEDp3_SetHigh();
            break;  
        default:
            break;
    }    
}