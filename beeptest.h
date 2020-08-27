#ifndef FX_BEEPTEST_H
#define	FX_BEEPTEST_H


#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
//#include "sigma/phaser4_IC_1.h"

/* Zones */
#define ZONE_WAVE_SINE          30
#define ZONE_WAVE_SQUARE        60
#define ZONE_WAVE_STEP          90
#define ZONE_WAVE_TRIANGLE      120
#define ZONE_WAVE_STATIC        150

#define ZONE_MOD_DISABLED       30
#define ZONE_MOD_SPEED_UP       80
#define ZONE_MOD_SPEED_DOWN     130
#define ZONE_MOD_MIX            190

void btnPresetPushed();

void potDepthChange(uint8_t value);

void potWidthChange(uint8_t value);

void potRateChange(uint8_t value);

void potWaveChange(uint8_t value);

void potModChange(uint8_t value);

#endif