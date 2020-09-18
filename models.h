/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_MODELS_H
#define	XC_HEADER_MODELS_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

typedef struct model
{
    char name[8];
    uint8_t channel;
    uint16_t zinput;
    
    
    uint8_t pregain_bypass;
    uint16_t pre_cutoff_freq;
    uint8_t pre_order;
    
    int8_t dspdistortion_gain_min;
    int8_t dspdistortion_gain_max;
    uint8_t dspdistortion_bypass;
    double dspdistortion_alpha;
    double dspdistortion_asymmetry;
    int8_t dspdistortion_volume;
    
    /* Post gain*/
    uint16_t post_low_cutoff_freq; // not implemented yet
    uint8_t post_low_order; // not implemented yet
    
    int8_t post_low_gain_min;
    int8_t post_low_gain_max;
    
    int8_t post_mid_gain_min;
    int8_t post_mid_gain_max;
    double post_mid_Q;
    int16_t post_mid_freq;
    
    int8_t post_high_gain_min;
    int8_t post_high_gain_max;
    
    int16_t post_presence_freq_min;
    int16_t post_presence_freq_max;
    
    //uint8_t post_pres_gain_min;
    
    
    //...
} model_t;

void model_read_model_from_eeprom(uint8_t model_id);
void model_apply_model(model_t model);
void model_current_store(uint8_t model_id);
void model_store(uint8_t model_id, model_t model_data);
void model_initialize(uint8_t code);

void model_current_set_name(char * name);
void model_current_set_pregain_lowcut(uint16_t value);
void model_current_set_postgain_bypass(uint8_t bypass);
void model_current_set_dspdistortion_bypass(uint8_t bypass);
void model_current_set_dspdistortion_alpha(double alpha);
void model_current_set_dspdistortion_gain(double gain_db);
void model_current_set_dspdistortion_volume(int8_t gain_db);
void model_current_set_analog_bypass(uint8_t bypass);
void model_current_set_dspdistortion_asymmetry(double asymm);
void model_current_set_postgain_mid_Q(double Q);
void model_current_set_postgain_mid_freq(int16_t freq);
void model_current_set_postgain_mid_boost(int16_t boost);

//model_t models[10];

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

