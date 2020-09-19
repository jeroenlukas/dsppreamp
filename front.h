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
#ifndef FRONT_H
#define	FRONT_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

volatile bool f_front_event = false;
volatile bool f_front_btn_models_pressed = false;
volatile bool f_front_btn_system_pressed = false;
volatile bool f_front_btn_next_pressed = false;

bool f_rot_enc_gain_up = false;
bool f_rot_enc_gain_down = false;
bool f_rot_enc_low_up = false;
bool f_rot_enc_low_down = false;
bool f_rot_enc_mid_up = false;
bool f_rot_enc_mid_down = false;
bool f_rot_enc_high_up = false;
bool f_rot_enc_high_down = false;
bool f_rot_enc_pres_up = false;
bool f_rot_enc_pres_down = false;
bool f_rot_enc_vol_up = false;
bool f_rot_enc_vol_down = false;
bool f_rot_enc_value_up = false;
bool f_rot_enc_value_down = false;



void lcd_display_basic_info(void);
void lcd_display_temporary(char * text);

void front_check_buttons(void);

uint8_t front_rot_enc_increment(void);


#endif	/* XC_HEADER_TEMPLATE_H */

