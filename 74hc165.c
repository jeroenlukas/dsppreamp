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
    // CP -> front_SCK   PL -> front_LOAD P_SI_Q7 -> front_MISO
	//P_SI_CP = LOW; 
    front_SCK_SetLow();
	//P_SI_PL = LOW;
    front_LOAD_SetLow();
	__delay_us(1);
	//P_SI_PL = HIGH;	
    front_LOAD_SetHigh();
	__delay_us(1);

	//if(P_SI_Q7) shift_input++;
    if(front_MISO_GetValue()) shift_input++;
	shift_input = shift_input << 1;

	for(i = 0; i < 24; i++)
	{		
        front_SCK_SetHigh();
		if(front_MISO_GetValue()) shift_input++;
		if(i < 24) shift_input = shift_input << 1;
		front_SCK_SetLow();
	
        _delay(1);
	}
	return shift_input;
}