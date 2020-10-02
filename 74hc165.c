/*
 * File:   74hc165.c
 * Author: Jeroen
 *
 * Created on August 15, 2020, 8:49 PM
 */


#include "xc.h"
#include "mcc_generated_files/mcc.h"
#include <stdint.h>

uint32_t sn74hc165_read(void)
{
    uint32_t shift_input = 0;
	char i;    
	
    front_SCK_SetLow();
	
    front_LOAD_SetLow();
	__delay_us(1);
	
    front_LOAD_SetHigh();
	__delay_us(1);

	
    if(front_MISO_GetValue()) shift_input++;
	shift_input = shift_input << 1;
    
        
	for(i = 0; i < 24; i++)
	{		
        front_SCK_SetHigh();
		if(front_MISO_GetValue()) shift_input++;
		front_SCK_SetLow();
	
        shift_input = shift_input << 1;
	}
    
	return shift_input;
}