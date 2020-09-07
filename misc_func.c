/*
 * File:   misc_func.c
 * Author: Jeroen
 *
 * Created on 24 augustus 2020, 13:05
 */


#include "xc.h"
#include <stdint.h>
#include "mcc_generated_files/mcc.h"

uint32_t millis_since_startup;

uint32_t millis(void)
{
    return millis_since_startup;
}

void millis_inc(void)
{
    millis_since_startup++;
}

void uitoa(uint16_t Value, char * Buffer)
{
 	uint8_t i;
 	uint16_t Digit;
 	uint16_t Divisor;
 	bool Printed = false;
 
 	if(Value)
 	{
 		for(i = 0, Divisor = 10000; i < 5u; i++)
 		{
 			Digit = Value/Divisor;
 			if(Digit || Printed)
 			{
 				*Buffer++ = '0' + Digit;
 				Value -= Digit*Divisor;
 				Printed = true;
 			}
 			Divisor /= 10;
 		}
 	}
 	else
 	{
 		*Buffer++ = '0';
 	}
 
 	*Buffer = '\0';
 }	