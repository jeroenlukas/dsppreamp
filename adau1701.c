/*
 * File:   adau1701.c
 * Author: Jeroen
 *
 * Created on 15 augustus 2020, 13:44
 */


#include "xc.h"
#include "config.h"
#include <stdint.h>

#include "sigma/DSPPreamp_IC_1.h"
#include "sigma/DSPPreamp_IC_1_PARAM.h"
#include "sigma/DSPPreamp_IC_1_REG.h"

void adau1701_write( uint16_t address, double value)
{
    double dp;    
            
    uint32_t dp_fixed;
    

    dp = value; // / (double)255;????

    //dp_fixed = dp * 0x80000000;    // TEST used to be 0x800000
    dp_fixed = dp * 0x00800000 ; 
    
    SIGMA_WRITE_SAFELOAD(0, address, dp_fixed);
}

void adau1701_write_orig( uint16_t address, float value)
{
    float dp;    
            
    uint32_t dp_fixed;
    

    dp = value / (float)255;

    dp_fixed = dp * 0x800000;    // original

    SIGMA_WRITE_SAFELOAD(0, address, dp_fixed);
}


// This function is easier for binary values such as setting switches etc
void adau1701_write_fixed( uint16_t address, uint32_t value)
{
    
    SIGMA_WRITE_SAFELOAD(0, address, value);
}