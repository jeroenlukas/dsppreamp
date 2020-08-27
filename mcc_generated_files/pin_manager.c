/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.35.9
        Device            :  PIC18F27K40
        Driver Version    :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/

#include <xc.h>
#include "pin_manager.h"
#include "stdbool.h"



void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */   
    LATA = 0x00;    
    LATB = 0x00;    
    LATC = 0x30;    

    /**
    TRISx registers
    */    
    TRISA = 0xD8;
    TRISB = 0xDB;
    TRISC = 0x31;

    /**
    ANSELx registers
    */   
    ANSELC = 0x00;
    ANSELB = 0xD0;
    ANSELA = 0xC0;

    /**
    WPUx registers
    */ 
    WPUE = 0x00;
    WPUB = 0x08;
    WPUA = 0x18;
    WPUC = 0x80;

    /**
    ODx registers
    */   
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;
    


   
    
    
    bool state = (unsigned char)GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    RB2PPS = 0x0B;   //RB2->EUSART2:TX2;
    RC4PPS = 0x0F;   //RC4->MSSP1:SCL1;
    RX1PPSbits.RXPPS = 0x08;   //RB0->EUSART1:RX1;
    RC5PPS = 0x10;   //RC5->MSSP1:SDA1;
    RC6PPS = 0x14;   //RC6->CLKREF:CLKR;
    RC7PPS = 0x07;   //RC7->PWM3:PWM3;
    SSP1CLKPPSbits.SSPCLKPPS = 0x14;   //RC4->MSSP1:SCL1;
    RX2PPSbits.RXPPS = 0x09;   //RB1->EUSART2:RX2;
    ADACTPPSbits.ADACTPPS = 0x0C;   //RB4->ADCC:ADACT;
    SSP1DATPPSbits.SSPDATPPS = 0x15;   //RC5->MSSP1:SDA1;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS

    GIE = state;
}       

void PIN_MANAGER_IOC(void)
{   

}

/**
 End of File
*/