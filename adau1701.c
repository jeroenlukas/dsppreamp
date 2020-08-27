/*
 * File:   adau1701.c
 * Author: Jeroen
 *
 * Created on 15 augustus 2020, 13:44
 */


#include "xc.h"
#include "config.h"

#include "sigma/phaser4_IC_1.h"
#include "sigma/phaser4_IC_1_PARAM.h"
#include "sigma/phaser4_IC_1_REG.h"

void adau1701_write( uint16_t address, uint32_t value)
{
    float dp;    
            
    uint32_t dp_fixed;
    

    dp = (float)value / (float)255;

    dp_fixed = dp * 0x800000;    

    SIGMA_WRITE_SAFELOAD(0, address, dp_fixed);
}