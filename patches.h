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
#ifndef XC_HEADER_PATCHES_H
#define	XC_HEADER_PATCHES_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include "models.h"
#include "24aa64.h"

typedef struct patch 
{
    char name[9]; // 8 Characters including 0 at the end
    uint8_t model_id;    
    uint8_t gain;
    uint8_t low;
    uint8_t mid;
    uint8_t high;
    uint8_t presence;
    uint8_t volume;
    uint8_t noise_gate;
    
    model_t model;
} patch_t;

// Global
patch_t current_patch;
uint8_t current_patch_no;

void patch_initialize(uint8_t code);

void patch_load(uint8_t patch_no);
void patch_current_store(uint8_t patch_no);
void patch_store(uint8_t patch_no, eeprom_patch_t patch_data);

void patch_current_set_model(uint8_t model_id);

void patch_current_set_name(char * name);

void patch_current_set_gain(uint8_t value, uint8_t sender);
void patch_current_set_low(uint8_t value, uint8_t sender);
void patch_current_set_mid(uint8_t value, uint8_t sender);
void patch_current_set_volume(uint8_t value, uint8_t sender);
void patch_current_set_high(uint8_t value, uint8_t sender);
void patch_current_set_presence(uint8_t value, uint8_t sender);

int16_t patch_scale_value(int16_t min, int16_t max, int16_t perc);
patch_t patch_get_current(void);

void patch_current_set_tonecontrol_center_frequency(double frequency);
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

