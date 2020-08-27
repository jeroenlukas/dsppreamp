#ifndef FX_PHASER4_H
#define	FX_PHASER4_H


#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
//#include "sigma/phaser4_IC_1.h"

/* Zones */
#define ZONE_WAVE_TRIANGLE      30
#define ZONE_WAVE_SINE          60
#define ZONE_WAVE_RAMPUP        90
#define ZONE_WAVE_RAMPDOWN      120
#define ZONE_WAVE_SQUARE        150
#define ZONE_WAVE_STEP          180
#define ZONE_WAVE_STOP          210

#define ZONE_MOD_DISABLED       30
#define ZONE_MOD_SPEED_UP       80
#define ZONE_MOD_SPEED_DOWN     130
#define ZONE_MOD_MIX            190

#define ZONE_STAGE_2            43         
#define ZONE_STAGE_4            85
#define ZONE_STAGE_6            128
#define ZONE_STAGE_8            170
#define ZONE_STAGE_10           213
#define ZONE_STAGE_12           255

void btnPresetPushed();

void potChanged(uint8_t pot, uint8_t value);

void setStages(uint8_t stages);

void FlashPresetLed(void);

#endif