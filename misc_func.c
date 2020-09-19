/*
 * File:   misc_func.c
 * Author: Jeroen
 *
 * Created on 24 augustus 2020, 13:05
 */


#include "xc.h"
#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "lcd_pcf8574.h"
#include "patches.h"
#include "misc_func.h"

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

void lcd_display_normal(void)
{
    temporary_display = 0;
    LCD_SetCursor(0,1);
    char strbuf[16];
    LCD_Write_Str("M");
    uitoa(current_patch.model_id + 1, strbuf);
    LCD_Write_Str_Zero_Padded_Right(strbuf, 2);
    LCD_Write_Str("|NG|     ");
}

void lcd_display_temporary(char * str)
{
    LCD_SetCursor(0,1);
    LCD_Write_Str_Padded(str, 12);
    millis_temporary_display = millis() + 2000;
    temporary_display = 1;
}
