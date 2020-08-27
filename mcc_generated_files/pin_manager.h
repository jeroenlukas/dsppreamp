/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.35.9
        Device            :  PIC18F27K40
        Version           :  1.01
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


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set front_led_store aliases
#define front_led_store_TRIS               TRISAbits.TRISA0
#define front_led_store_LAT                LATAbits.LATA0
#define front_led_store_PORT               PORTAbits.RA0
#define front_led_store_WPU                WPUAbits.WPUA0
#define front_led_store_OD                ODCONAbits.ODCA0
#define front_led_store_ANS                ANSELAbits.ANSELA0
#define front_led_store_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define front_led_store_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define front_led_store_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define front_led_store_GetValue()           PORTAbits.RA0
#define front_led_store_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define front_led_store_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define front_led_store_SetPullup()      do { WPUAbits.WPUA0 = 1; } while(0)
#define front_led_store_ResetPullup()    do { WPUAbits.WPUA0 = 0; } while(0)
#define front_led_store_SetPushPull()    do { ODCONAbits.ODCA0 = 0; } while(0)
#define front_led_store_SetOpenDrain()   do { ODCONAbits.ODCA0 = 1; } while(0)
#define front_led_store_SetAnalogMode()  do { ANSELAbits.ANSELA0 = 1; } while(0)
#define front_led_store_SetDigitalMode() do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set front_led_midi aliases
#define front_led_midi_TRIS               TRISAbits.TRISA1
#define front_led_midi_LAT                LATAbits.LATA1
#define front_led_midi_PORT               PORTAbits.RA1
#define front_led_midi_WPU                WPUAbits.WPUA1
#define front_led_midi_OD                ODCONAbits.ODCA1
#define front_led_midi_ANS                ANSELAbits.ANSELA1
#define front_led_midi_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define front_led_midi_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define front_led_midi_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define front_led_midi_GetValue()           PORTAbits.RA1
#define front_led_midi_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define front_led_midi_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define front_led_midi_SetPullup()      do { WPUAbits.WPUA1 = 1; } while(0)
#define front_led_midi_ResetPullup()    do { WPUAbits.WPUA1 = 0; } while(0)
#define front_led_midi_SetPushPull()    do { ODCONAbits.ODCA1 = 0; } while(0)
#define front_led_midi_SetOpenDrain()   do { ODCONAbits.ODCA1 = 1; } while(0)
#define front_led_midi_SetAnalogMode()  do { ANSELAbits.ANSELA1 = 1; } while(0)
#define front_led_midi_SetDigitalMode() do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set front_led_signal_red aliases
#define front_led_signal_red_TRIS               TRISAbits.TRISA2
#define front_led_signal_red_LAT                LATAbits.LATA2
#define front_led_signal_red_PORT               PORTAbits.RA2
#define front_led_signal_red_WPU                WPUAbits.WPUA2
#define front_led_signal_red_OD                ODCONAbits.ODCA2
#define front_led_signal_red_ANS                ANSELAbits.ANSELA2
#define front_led_signal_red_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define front_led_signal_red_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define front_led_signal_red_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define front_led_signal_red_GetValue()           PORTAbits.RA2
#define front_led_signal_red_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define front_led_signal_red_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define front_led_signal_red_SetPullup()      do { WPUAbits.WPUA2 = 1; } while(0)
#define front_led_signal_red_ResetPullup()    do { WPUAbits.WPUA2 = 0; } while(0)
#define front_led_signal_red_SetPushPull()    do { ODCONAbits.ODCA2 = 0; } while(0)
#define front_led_signal_red_SetOpenDrain()   do { ODCONAbits.ODCA2 = 1; } while(0)
#define front_led_signal_red_SetAnalogMode()  do { ANSELAbits.ANSELA2 = 1; } while(0)
#define front_led_signal_red_SetDigitalMode() do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set front_btn_models aliases
#define front_btn_models_TRIS               TRISAbits.TRISA3
#define front_btn_models_LAT                LATAbits.LATA3
#define front_btn_models_PORT               PORTAbits.RA3
#define front_btn_models_WPU                WPUAbits.WPUA3
#define front_btn_models_OD                ODCONAbits.ODCA3
#define front_btn_models_ANS                ANSELAbits.ANSELA3
#define front_btn_models_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define front_btn_models_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define front_btn_models_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define front_btn_models_GetValue()           PORTAbits.RA3
#define front_btn_models_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define front_btn_models_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define front_btn_models_SetPullup()      do { WPUAbits.WPUA3 = 1; } while(0)
#define front_btn_models_ResetPullup()    do { WPUAbits.WPUA3 = 0; } while(0)
#define front_btn_models_SetPushPull()    do { ODCONAbits.ODCA3 = 0; } while(0)
#define front_btn_models_SetOpenDrain()   do { ODCONAbits.ODCA3 = 1; } while(0)
#define front_btn_models_SetAnalogMode()  do { ANSELAbits.ANSELA3 = 1; } while(0)
#define front_btn_models_SetDigitalMode() do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set front_btn_system aliases
#define front_btn_system_TRIS               TRISAbits.TRISA4
#define front_btn_system_LAT                LATAbits.LATA4
#define front_btn_system_PORT               PORTAbits.RA4
#define front_btn_system_WPU                WPUAbits.WPUA4
#define front_btn_system_OD                ODCONAbits.ODCA4
#define front_btn_system_ANS                ANSELAbits.ANSELA4
#define front_btn_system_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define front_btn_system_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define front_btn_system_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define front_btn_system_GetValue()           PORTAbits.RA4
#define front_btn_system_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define front_btn_system_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define front_btn_system_SetPullup()      do { WPUAbits.WPUA4 = 1; } while(0)
#define front_btn_system_ResetPullup()    do { WPUAbits.WPUA4 = 0; } while(0)
#define front_btn_system_SetPushPull()    do { ODCONAbits.ODCA4 = 0; } while(0)
#define front_btn_system_SetOpenDrain()   do { ODCONAbits.ODCA4 = 1; } while(0)
#define front_btn_system_SetAnalogMode()  do { ANSELAbits.ANSELA4 = 1; } while(0)
#define front_btn_system_SetDigitalMode() do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set front_LOAD aliases
#define front_LOAD_TRIS               TRISAbits.TRISA5
#define front_LOAD_LAT                LATAbits.LATA5
#define front_LOAD_PORT               PORTAbits.RA5
#define front_LOAD_WPU                WPUAbits.WPUA5
#define front_LOAD_OD                ODCONAbits.ODCA5
#define front_LOAD_ANS                ANSELAbits.ANSELA5
#define front_LOAD_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define front_LOAD_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define front_LOAD_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define front_LOAD_GetValue()           PORTAbits.RA5
#define front_LOAD_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define front_LOAD_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define front_LOAD_SetPullup()      do { WPUAbits.WPUA5 = 1; } while(0)
#define front_LOAD_ResetPullup()    do { WPUAbits.WPUA5 = 0; } while(0)
#define front_LOAD_SetPushPull()    do { ODCONAbits.ODCA5 = 0; } while(0)
#define front_LOAD_SetOpenDrain()   do { ODCONAbits.ODCA5 = 1; } while(0)
#define front_LOAD_SetAnalogMode()  do { ANSELAbits.ANSELA5 = 1; } while(0)
#define front_LOAD_SetDigitalMode() do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set RB0 procedures
#define RB0_SetHigh()    do { LATBbits.LATB0 = 1; } while(0)
#define RB0_SetLow()   do { LATBbits.LATB0 = 0; } while(0)
#define RB0_Toggle()   do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define RB0_GetValue()         PORTBbits.RB0
#define RB0_SetDigitalInput()   do { TRISBbits.TRISB0 = 1; } while(0)
#define RB0_SetDigitalOutput()  do { TRISBbits.TRISB0 = 0; } while(0)
#define RB0_SetPullup()     do { WPUBbits.WPUB0 = 1; } while(0)
#define RB0_ResetPullup()   do { WPUBbits.WPUB0 = 0; } while(0)
#define RB0_SetAnalogMode() do { ANSELBbits.ANSELB0 = 1; } while(0)
#define RB0_SetDigitalMode()do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set RB1 procedures
#define RB1_SetHigh()    do { LATBbits.LATB1 = 1; } while(0)
#define RB1_SetLow()   do { LATBbits.LATB1 = 0; } while(0)
#define RB1_Toggle()   do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define RB1_GetValue()         PORTBbits.RB1
#define RB1_SetDigitalInput()   do { TRISBbits.TRISB1 = 1; } while(0)
#define RB1_SetDigitalOutput()  do { TRISBbits.TRISB1 = 0; } while(0)
#define RB1_SetPullup()     do { WPUBbits.WPUB1 = 1; } while(0)
#define RB1_ResetPullup()   do { WPUBbits.WPUB1 = 0; } while(0)
#define RB1_SetAnalogMode() do { ANSELBbits.ANSELB1 = 1; } while(0)
#define RB1_SetDigitalMode()do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set RB2 procedures
#define RB2_SetHigh()    do { LATBbits.LATB2 = 1; } while(0)
#define RB2_SetLow()   do { LATBbits.LATB2 = 0; } while(0)
#define RB2_Toggle()   do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define RB2_GetValue()         PORTBbits.RB2
#define RB2_SetDigitalInput()   do { TRISBbits.TRISB2 = 1; } while(0)
#define RB2_SetDigitalOutput()  do { TRISBbits.TRISB2 = 0; } while(0)
#define RB2_SetPullup()     do { WPUBbits.WPUB2 = 1; } while(0)
#define RB2_ResetPullup()   do { WPUBbits.WPUB2 = 0; } while(0)
#define RB2_SetAnalogMode() do { ANSELBbits.ANSELB2 = 1; } while(0)
#define RB2_SetDigitalMode()do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set front_btn_next aliases
#define front_btn_next_TRIS               TRISBbits.TRISB3
#define front_btn_next_LAT                LATBbits.LATB3
#define front_btn_next_PORT               PORTBbits.RB3
#define front_btn_next_WPU                WPUBbits.WPUB3
#define front_btn_next_OD                ODCONBbits.ODCB3
#define front_btn_next_ANS                ANSELBbits.ANSELB3
#define front_btn_next_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define front_btn_next_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define front_btn_next_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define front_btn_next_GetValue()           PORTBbits.RB3
#define front_btn_next_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define front_btn_next_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define front_btn_next_SetPullup()      do { WPUBbits.WPUB3 = 1; } while(0)
#define front_btn_next_ResetPullup()    do { WPUBbits.WPUB3 = 0; } while(0)
#define front_btn_next_SetPushPull()    do { ODCONBbits.ODCB3 = 0; } while(0)
#define front_btn_next_SetOpenDrain()   do { ODCONBbits.ODCB3 = 1; } while(0)
#define front_btn_next_SetAnalogMode()  do { ANSELBbits.ANSELB3 = 1; } while(0)
#define front_btn_next_SetDigitalMode() do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set dsp_level aliases
#define dsp_level_TRIS               TRISBbits.TRISB4
#define dsp_level_LAT                LATBbits.LATB4
#define dsp_level_PORT               PORTBbits.RB4
#define dsp_level_WPU                WPUBbits.WPUB4
#define dsp_level_OD                ODCONBbits.ODCB4
#define dsp_level_ANS                ANSELBbits.ANSELB4
#define dsp_level_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define dsp_level_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define dsp_level_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define dsp_level_GetValue()           PORTBbits.RB4
#define dsp_level_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define dsp_level_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define dsp_level_SetPullup()      do { WPUBbits.WPUB4 = 1; } while(0)
#define dsp_level_ResetPullup()    do { WPUBbits.WPUB4 = 0; } while(0)
#define dsp_level_SetPushPull()    do { ODCONBbits.ODCB4 = 0; } while(0)
#define dsp_level_SetOpenDrain()   do { ODCONBbits.ODCB4 = 1; } while(0)
#define dsp_level_SetAnalogMode()  do { ANSELBbits.ANSELB4 = 1; } while(0)
#define dsp_level_SetDigitalMode() do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set front_led_signal_green aliases
#define front_led_signal_green_TRIS               TRISBbits.TRISB5
#define front_led_signal_green_LAT                LATBbits.LATB5
#define front_led_signal_green_PORT               PORTBbits.RB5
#define front_led_signal_green_WPU                WPUBbits.WPUB5
#define front_led_signal_green_OD                ODCONBbits.ODCB5
#define front_led_signal_green_ANS                ANSELBbits.ANSELB5
#define front_led_signal_green_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define front_led_signal_green_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define front_led_signal_green_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define front_led_signal_green_GetValue()           PORTBbits.RB5
#define front_led_signal_green_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define front_led_signal_green_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define front_led_signal_green_SetPullup()      do { WPUBbits.WPUB5 = 1; } while(0)
#define front_led_signal_green_ResetPullup()    do { WPUBbits.WPUB5 = 0; } while(0)
#define front_led_signal_green_SetPushPull()    do { ODCONBbits.ODCB5 = 0; } while(0)
#define front_led_signal_green_SetOpenDrain()   do { ODCONBbits.ODCB5 = 1; } while(0)
#define front_led_signal_green_SetAnalogMode()  do { ANSELBbits.ANSELB5 = 1; } while(0)
#define front_led_signal_green_SetDigitalMode() do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set front_MISO aliases
#define front_MISO_TRIS               TRISCbits.TRISC0
#define front_MISO_LAT                LATCbits.LATC0
#define front_MISO_PORT               PORTCbits.RC0
#define front_MISO_WPU                WPUCbits.WPUC0
#define front_MISO_OD                ODCONCbits.ODCC0
#define front_MISO_ANS                ANSELCbits.ANSELC0
#define front_MISO_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define front_MISO_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define front_MISO_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define front_MISO_GetValue()           PORTCbits.RC0
#define front_MISO_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define front_MISO_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define front_MISO_SetPullup()      do { WPUCbits.WPUC0 = 1; } while(0)
#define front_MISO_ResetPullup()    do { WPUCbits.WPUC0 = 0; } while(0)
#define front_MISO_SetPushPull()    do { ODCONCbits.ODCC0 = 0; } while(0)
#define front_MISO_SetOpenDrain()   do { ODCONCbits.ODCC0 = 1; } while(0)
#define front_MISO_SetAnalogMode()  do { ANSELCbits.ANSELC0 = 1; } while(0)
#define front_MISO_SetDigitalMode() do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set front_SCK aliases
#define front_SCK_TRIS               TRISCbits.TRISC1
#define front_SCK_LAT                LATCbits.LATC1
#define front_SCK_PORT               PORTCbits.RC1
#define front_SCK_WPU                WPUCbits.WPUC1
#define front_SCK_OD                ODCONCbits.ODCC1
#define front_SCK_ANS                ANSELCbits.ANSELC1
#define front_SCK_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define front_SCK_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define front_SCK_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define front_SCK_GetValue()           PORTCbits.RC1
#define front_SCK_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define front_SCK_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define front_SCK_SetPullup()      do { WPUCbits.WPUC1 = 1; } while(0)
#define front_SCK_ResetPullup()    do { WPUCbits.WPUC1 = 0; } while(0)
#define front_SCK_SetPushPull()    do { ODCONCbits.ODCC1 = 0; } while(0)
#define front_SCK_SetOpenDrain()   do { ODCONCbits.ODCC1 = 1; } while(0)
#define front_SCK_SetAnalogMode()  do { ANSELCbits.ANSELC1 = 1; } while(0)
#define front_SCK_SetDigitalMode() do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set mux_A aliases
#define mux_A_TRIS               TRISCbits.TRISC2
#define mux_A_LAT                LATCbits.LATC2
#define mux_A_PORT               PORTCbits.RC2
#define mux_A_WPU                WPUCbits.WPUC2
#define mux_A_OD                ODCONCbits.ODCC2
#define mux_A_ANS                ANSELCbits.ANSELC2
#define mux_A_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define mux_A_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define mux_A_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define mux_A_GetValue()           PORTCbits.RC2
#define mux_A_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define mux_A_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define mux_A_SetPullup()      do { WPUCbits.WPUC2 = 1; } while(0)
#define mux_A_ResetPullup()    do { WPUCbits.WPUC2 = 0; } while(0)
#define mux_A_SetPushPull()    do { ODCONCbits.ODCC2 = 0; } while(0)
#define mux_A_SetOpenDrain()   do { ODCONCbits.ODCC2 = 1; } while(0)
#define mux_A_SetAnalogMode()  do { ANSELCbits.ANSELC2 = 1; } while(0)
#define mux_A_SetDigitalMode() do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set mux_B aliases
#define mux_B_TRIS               TRISCbits.TRISC3
#define mux_B_LAT                LATCbits.LATC3
#define mux_B_PORT               PORTCbits.RC3
#define mux_B_WPU                WPUCbits.WPUC3
#define mux_B_OD                ODCONCbits.ODCC3
#define mux_B_ANS                ANSELCbits.ANSELC3
#define mux_B_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define mux_B_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define mux_B_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define mux_B_GetValue()           PORTCbits.RC3
#define mux_B_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define mux_B_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define mux_B_SetPullup()      do { WPUCbits.WPUC3 = 1; } while(0)
#define mux_B_ResetPullup()    do { WPUCbits.WPUC3 = 0; } while(0)
#define mux_B_SetPushPull()    do { ODCONCbits.ODCC3 = 0; } while(0)
#define mux_B_SetOpenDrain()   do { ODCONCbits.ODCC3 = 1; } while(0)
#define mux_B_SetAnalogMode()  do { ANSELCbits.ANSELC3 = 1; } while(0)
#define mux_B_SetDigitalMode() do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set SCL1 aliases
#define SCL1_TRIS               TRISCbits.TRISC4
#define SCL1_LAT                LATCbits.LATC4
#define SCL1_PORT               PORTCbits.RC4
#define SCL1_WPU                WPUCbits.WPUC4
#define SCL1_OD                ODCONCbits.ODCC4
#define SCL1_ANS                ANSELCbits.ANSELC4
#define SCL1_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define SCL1_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define SCL1_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define SCL1_GetValue()           PORTCbits.RC4
#define SCL1_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define SCL1_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define SCL1_SetPullup()      do { WPUCbits.WPUC4 = 1; } while(0)
#define SCL1_ResetPullup()    do { WPUCbits.WPUC4 = 0; } while(0)
#define SCL1_SetPushPull()    do { ODCONCbits.ODCC4 = 0; } while(0)
#define SCL1_SetOpenDrain()   do { ODCONCbits.ODCC4 = 1; } while(0)
#define SCL1_SetAnalogMode()  do { ANSELCbits.ANSELC4 = 1; } while(0)
#define SCL1_SetDigitalMode() do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set SDA1 aliases
#define SDA1_TRIS               TRISCbits.TRISC5
#define SDA1_LAT                LATCbits.LATC5
#define SDA1_PORT               PORTCbits.RC5
#define SDA1_WPU                WPUCbits.WPUC5
#define SDA1_OD                ODCONCbits.ODCC5
#define SDA1_ANS                ANSELCbits.ANSELC5
#define SDA1_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define SDA1_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define SDA1_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define SDA1_GetValue()           PORTCbits.RC5
#define SDA1_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define SDA1_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define SDA1_SetPullup()      do { WPUCbits.WPUC5 = 1; } while(0)
#define SDA1_ResetPullup()    do { WPUCbits.WPUC5 = 0; } while(0)
#define SDA1_SetPushPull()    do { ODCONCbits.ODCC5 = 0; } while(0)
#define SDA1_SetOpenDrain()   do { ODCONCbits.ODCC5 = 1; } while(0)
#define SDA1_SetAnalogMode()  do { ANSELCbits.ANSELC5 = 1; } while(0)
#define SDA1_SetDigitalMode() do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()    do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()   do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()   do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()         PORTCbits.RC6
#define RC6_SetDigitalInput()   do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()  do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()     do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()   do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode() do { ANSELCbits.ANSELC6 = 1; } while(0)
#define RC6_SetDigitalMode()do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()    do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()   do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()   do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()         PORTCbits.RC7
#define RC7_SetDigitalInput()   do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()  do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()     do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()   do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode() do { ANSELCbits.ANSELC7 = 1; } while(0)
#define RC7_SetDigitalMode()do { ANSELCbits.ANSELC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/