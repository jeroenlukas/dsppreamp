/*
 * File:   24aa64.c
 * Author: Jeroen
 *
 * Created on August 15, 2020, 8:21 PM
 */


#include "xc.h"
#include <stdint.h>
#include "config.h"
#include "i2c_simplifier.h"
#include "24aa64.h"

void eeprom_write_one_byte(uint16_t address, uint8_t value)
{
    uint8_t i2c_data[3];
    i2c_data[0] = (address >> 8) & 0xFF; // Address high byte
    i2c_data[1] = (address >> 0) & 0xFF; // Address low byte
    i2c_data[2] = value; // Data
    //i2c_simple_write(I2C_ADDRESS_EEPROM_WRITE, 3, i2c_data);
}

uint8_t eeprom_read_one_byte(uint16_t address)
{
    uint8_t i2c_data[3];
    
    // ...
}

uint8_t eeprom_read_model_parameter(uint8_t model_id, uint8_t parameter)
{
   return eeprom_read_one_byte(EEPROM_MODEL_START + (model_id * EEPROM_MODEL_SIZE) + parameter);
}