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