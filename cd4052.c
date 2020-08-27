/*
 * File:   mux.c
 * Author: Jeroen
 *
 * Created on 15 augustus 2020, 19:35
 */


#include "xc.h"
#include "mcc_generated_files/mcc.h"

// Control CD4052
// Channel = 0..3
void mux_set_channel(uint8_t channel)
{
    mux_A_LAT = channel & 1;
    mux_B_LAT = channel & 2;
}