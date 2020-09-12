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
#ifndef XC_24AA64_H
#define	XC_24AA64_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

typedef struct patch_eeprom 
{
    char name[9];
    uint8_t model_id;    
    uint8_t gain;
    uint8_t low;
    uint8_t mid;
    uint8_t high;
    uint8_t presence;
    uint8_t volume;
    uint8_t noise_gate;
} eeprom_patch_t;

void eeprom_write_one_byte(uint16_t address, uint8_t value);
uint8_t eeprom_read_one_byte(uint16_t address);
uint8_t eeprom_read_model_parameter(uint8_t model_id, uint8_t parameter);

void eeprom_write_multi(uint16_t data_address, void *pData, uint16_t nCount);
uint8_t eeprom_read_multi(uint16_t address, void *pData, uint16_t nCount);


#endif	/* XC_HEADER_TEMPLATE_H */

