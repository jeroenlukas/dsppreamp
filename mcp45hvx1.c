/*
 * File:   mcp45hvx1.c
 * Author: Jeroen
 *
 * Created on August 13, 2020, 8:13 PM
 */


#include "xc.h"

#include <stdint.h>

#include "i2c_simplifier.h"

void mcp45hvx1_set_wiper(uint8_t device_address, uint8_t value)
{
    uint8_t i2c_data[2];
    i2c_data[0] = 0b00000000; // Write data to address 00 (wiper value)
    i2c_data[1] = value;
    
    i2c_simple_write(device_address, 2, i2c_data);
}