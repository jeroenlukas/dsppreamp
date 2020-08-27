/*
 * File:   s_beeptest.c
 * Author: Jeroen
 *
 * Created on 22 september 2017, 21:21
 */

#include <xc.h>
#include <stdint.h>
#include "fx_phaser4.h"
#include "sigma/beeptest_IC_1.h"
#include "sigma/beeptest_IC_1_PARAM.h"
#include "sigma/beeptest_IC_1_REG.h"
#include "mcc_generated_files/mcc.h"

// Sigma project related
#define DEVICE_ADDR_ 0x68

unsigned char preset = 0; // 0 is no preset

void btnPresetPushed()
{
    
}

void potDepthChange(uint8_t value)
{
}

void potWidthChange(uint8_t value)
{
   
}

void potRateChange(uint8_t value)
{
   
}


void potWaveChange(uint8_t value)
{
    
}
 
 void potModChange(uint8_t value)
 {
   
 }