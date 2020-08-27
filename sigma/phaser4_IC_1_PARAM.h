/*
 * File:           C:\Users\Jeroen\Google Drive\DIY\GuitarDSP\Software\sigma\phaser4_IC_1_PARAM.h
 *
 * Created:        Tuesday, February 27, 2018 7:13:36 PM
 * Description:    phaser4:IC 1 parameter RAM definitions.
 *
 * This software is distributed in the hope that it will be useful,
 * but is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * This software may only be used to program products purchased from
 * Analog Devices for incorporation by you into audio products that
 * are intended for resale to audio product end users. This software
 * may not be distributed whole or in any part to third parties.
 *
 * Copyright ©2018 Analog Devices, Inc. All rights reserved.
 */
#ifndef __PHASER4_IC_1_PARAM_H__
#define __PHASER4_IC_1_PARAM_H__


/* Module DC2_2 - DC Input Entry*/
#define MOD_WAVEGEN_DC2_2_COUNT                        2
#define MOD_WAVEGEN_DC2_2_DEVICE                       "IC1"
#define MOD_WAVEGEN_DC2_2_ALG0_DCINPALG8_ADDR          0
#define MOD_WAVEGEN_DC2_2_ALG0_DCINPALG8_FIXPT         0x000000A7
#define MOD_WAVEGEN_DC2_2_ALG0_DCINPALG8_VALUE         SIGMASTUDIOTYPE_FIXPOINT_CONVERT(2E-05)
#define MOD_WAVEGEN_DC2_2_ALG0_DCINPALG8_TYPE          SIGMASTUDIOTYPE_FIXPOINT
#define MOD_DC2_2_ALG0_DCINPALG3_ADDR                  21
#define MOD_DC2_2_ALG0_DCINPALG3_FIXPT                 0x00001450
#define MOD_DC2_2_ALG0_DCINPALG3_VALUE                 SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.00062)
#define MOD_DC2_2_ALG0_DCINPALG3_TYPE                  SIGMASTUDIOTYPE_FIXPOINT

/* Module DC2_3 - DC Input Entry*/
#define MOD_WAVEGEN_DC2_3_COUNT                        1
#define MOD_WAVEGEN_DC2_3_DEVICE                       "IC1"
#define MOD_WAVEGEN_DC2_3_DCINPALG9_ADDR               1
#define MOD_WAVEGEN_DC2_3_DCINPALG9_FIXPT              0x00800000
#define MOD_WAVEGEN_DC2_3_DCINPALG9_VALUE              SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD_WAVEGEN_DC2_3_DCINPALG9_TYPE               SIGMASTUDIOTYPE_FIXPOINT

/* Module DC2_4 - DC Input Entry*/
#define MOD_WAVEGEN_DC2_4_COUNT                        1
#define MOD_WAVEGEN_DC2_4_DEVICE                       "IC1"
#define MOD_WAVEGEN_DC2_4_DCINPALG10_ADDR              2
#define MOD_WAVEGEN_DC2_4_DCINPALG10_FIXPT             0xFF800000
#define MOD_WAVEGEN_DC2_4_DCINPALG10_VALUE             SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-1)
#define MOD_WAVEGEN_DC2_4_DCINPALG10_TYPE              SIGMASTUDIOTYPE_FIXPOINT

/* Module DC2_7 - DC Input Entry*/
#define MOD_WAVEGEN_DC2_7_COUNT                        1
#define MOD_WAVEGEN_DC2_7_DEVICE                       "IC1"
#define MOD_WAVEGEN_DC2_7_DCINPALG11_ADDR              3
#define MOD_WAVEGEN_DC2_7_DCINPALG11_FIXPT             0x00001450
#define MOD_WAVEGEN_DC2_7_DCINPALG11_VALUE             SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.00062)
#define MOD_WAVEGEN_DC2_7_DCINPALG11_TYPE              SIGMASTUDIOTYPE_FIXPOINT

/* Module W Noise1 - White Noise*/
#define MOD_WAVEGEN_WNOISE1_COUNT                      3
#define MOD_WAVEGEN_WNOISE1_DEVICE                     "IC1"
#define MOD_WAVEGEN_WNOISE1_ALG0_ENABLENOISE_ADDR      4
#define MOD_WAVEGEN_WNOISE1_ALG0_ENABLENOISE_FIXPT     0x00800000
#define MOD_WAVEGEN_WNOISE1_ALG0_ENABLENOISE_VALUE     SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD_WAVEGEN_WNOISE1_ALG0_ENABLENOISE_TYPE      SIGMASTUDIOTYPE_FIXPOINT
#define MOD_WAVEGEN_WNOISE1_ALG0_SEED_ADDR             5
#define MOD_WAVEGEN_WNOISE1_ALG0_SEED_FIXPT            0x0046EAAD
#define MOD_WAVEGEN_WNOISE1_ALG0_SEED_VALUE            SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.554036785985553)
#define MOD_WAVEGEN_WNOISE1_ALG0_SEED_TYPE             SIGMASTUDIOTYPE_FIXPOINT
#define MOD_WAVEGEN_WNOISE1_ALG0_MXX_ADDR              6
#define MOD_WAVEGEN_WNOISE1_ALG0_MXX_FIXPT             0x0005464B
#define MOD_WAVEGEN_WNOISE1_ALG0_MXX_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(345675)
#define MOD_WAVEGEN_WNOISE1_ALG0_MXX_TYPE              SIGMASTUDIOTYPE_INTEGER

/* Module DC2_14 - DC Input Entry*/
#define MOD_WAVEGEN_DC2_14_COUNT                       1
#define MOD_WAVEGEN_DC2_14_DEVICE                      "IC1"
#define MOD_WAVEGEN_DC2_14_DCINPALG17_ADDR             7
#define MOD_WAVEGEN_DC2_14_DCINPALG17_FIXPT            0x00800000
#define MOD_WAVEGEN_DC2_14_DCINPALG17_VALUE            SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD_WAVEGEN_DC2_14_DCINPALG17_TYPE             SIGMASTUDIOTYPE_FIXPOINT

/* Module DC2_15 - DC Input Entry*/
#define MOD_WAVEGEN_DC2_15_COUNT                       1
#define MOD_WAVEGEN_DC2_15_DEVICE                      "IC1"
#define MOD_WAVEGEN_DC2_15_DCINPALG18_ADDR             8
#define MOD_WAVEGEN_DC2_15_DCINPALG18_FIXPT            0xFF000000
#define MOD_WAVEGEN_DC2_15_DCINPALG18_VALUE            SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-2)
#define MOD_WAVEGEN_DC2_15_DCINPALG18_TYPE             SIGMASTUDIOTYPE_FIXPOINT

/* Module DC2_16 - DC Input Entry*/
#define MOD_WAVEGEN_DC2_16_COUNT                       1
#define MOD_WAVEGEN_DC2_16_DEVICE                      "IC1"
#define MOD_WAVEGEN_DC2_16_DCINPALG19_ADDR             9
#define MOD_WAVEGEN_DC2_16_DCINPALG19_FIXPT            0x00000000
#define MOD_WAVEGEN_DC2_16_DCINPALG19_VALUE            SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD_WAVEGEN_DC2_16_DCINPALG19_TYPE             SIGMASTUDIOTYPE_FIXPOINT

/* Module DC2_17 - DC Input Entry*/
#define MOD_WAVEGEN_DC2_17_COUNT                       1
#define MOD_WAVEGEN_DC2_17_DEVICE                      "IC1"
#define MOD_WAVEGEN_DC2_17_DCINPALG14_ADDR             10
#define MOD_WAVEGEN_DC2_17_DCINPALG14_FIXPT            0x00000000
#define MOD_WAVEGEN_DC2_17_DCINPALG14_VALUE            SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD_WAVEGEN_DC2_17_DCINPALG14_TYPE             SIGMASTUDIOTYPE_FIXPOINT

/* Module DC2_18 - DC Input Entry*/
#define MOD_WAVEGEN_DC2_18_COUNT                       1
#define MOD_WAVEGEN_DC2_18_DEVICE                      "IC1"
#define MOD_WAVEGEN_DC2_18_DCINPALG15_ADDR             11
#define MOD_WAVEGEN_DC2_18_DCINPALG15_FIXPT            0x00000000
#define MOD_WAVEGEN_DC2_18_DCINPALG15_VALUE            SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD_WAVEGEN_DC2_18_DCINPALG15_TYPE             SIGMASTUDIOTYPE_FIXPOINT

/* Module DC2_19 - DC Input Entry*/
#define MOD_WAVEGEN_DC2_19_COUNT                       1
#define MOD_WAVEGEN_DC2_19_DEVICE                      "IC1"
#define MOD_WAVEGEN_DC2_19_DCINPALG16_ADDR             12
#define MOD_WAVEGEN_DC2_19_DCINPALG16_FIXPT            0x00000000
#define MOD_WAVEGEN_DC2_19_DCINPALG16_VALUE            SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD_WAVEGEN_DC2_19_DCINPALG16_TYPE             SIGMASTUDIOTYPE_FIXPOINT

/* Module DC2_20 - DC Input Entry*/
#define MOD_WAVEGEN_DC2_20_COUNT                       1
#define MOD_WAVEGEN_DC2_20_DEVICE                      "IC1"
#define MOD_WAVEGEN_DC2_20_DCINPALG20_ADDR             13
#define MOD_WAVEGEN_DC2_20_DCINPALG20_FIXPT            0x00000000
#define MOD_WAVEGEN_DC2_20_DCINPALG20_VALUE            SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD_WAVEGEN_DC2_20_DCINPALG20_TYPE             SIGMASTUDIOTYPE_FIXPOINT

/* Module DC2_21 - DC Input Entry*/
#define MOD_WAVEGEN_DC2_21_COUNT                       1
#define MOD_WAVEGEN_DC2_21_DEVICE                      "IC1"
#define MOD_WAVEGEN_DC2_21_DCINPALG21_ADDR             14
#define MOD_WAVEGEN_DC2_21_DCINPALG21_FIXPT            0x00400000
#define MOD_WAVEGEN_DC2_21_DCINPALG21_VALUE            SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.5)
#define MOD_WAVEGEN_DC2_21_DCINPALG21_TYPE             SIGMASTUDIOTYPE_FIXPOINT

/* Module DC2_11 - DC Input Entry*/
#define MOD_WAVEGEN_DC2_11_COUNT                       1
#define MOD_WAVEGEN_DC2_11_DEVICE                      "IC1"
#define MOD_WAVEGEN_DC2_11_DCINPALG22_ADDR             15
#define MOD_WAVEGEN_DC2_11_DCINPALG22_FIXPT            0x00400000
#define MOD_WAVEGEN_DC2_11_DCINPALG22_VALUE            SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.5)
#define MOD_WAVEGEN_DC2_11_DCINPALG22_TYPE             SIGMASTUDIOTYPE_FIXPOINT

/* Module DC2_5 - DC Input Entry*/
#define MOD_RATEGEN_DC2_5_COUNT                        1
#define MOD_RATEGEN_DC2_5_DEVICE                       "IC1"
#define MOD_RATEGEN_DC2_5_DCINPALG6_ADDR               16
#define MOD_RATEGEN_DC2_5_DCINPALG6_FIXPT              0x00000000
#define MOD_RATEGEN_DC2_5_DCINPALG6_VALUE              SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD_RATEGEN_DC2_5_DCINPALG6_TYPE               SIGMASTUDIOTYPE_FIXPOINT

/* Module DC2_6 - DC Input Entry*/
#define MOD_RATEGEN_DC2_6_COUNT                        1
#define MOD_RATEGEN_DC2_6_DEVICE                       "IC1"
#define MOD_RATEGEN_DC2_6_DCINPALG7_ADDR               17
#define MOD_RATEGEN_DC2_6_DCINPALG7_FIXPT              0xFFC00000
#define MOD_RATEGEN_DC2_6_DCINPALG7_VALUE              SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-0.5)
#define MOD_RATEGEN_DC2_6_DCINPALG7_TYPE               SIGMASTUDIOTYPE_FIXPOINT

/* Module DC2_9 - DC Input Entry*/
#define MOD_RATEGEN_DC2_9_COUNT                        1
#define MOD_RATEGEN_DC2_9_DEVICE                       "IC1"
#define MOD_RATEGEN_DC2_9_DCINPALG4_ADDR               18
#define MOD_RATEGEN_DC2_9_DCINPALG4_FIXPT              0x00333333
#define MOD_RATEGEN_DC2_9_DCINPALG4_VALUE              SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.4)
#define MOD_RATEGEN_DC2_9_DCINPALG4_TYPE               SIGMASTUDIOTYPE_FIXPOINT

/* Module DC2_8 - DC Input Entry*/
#define MOD_RATEGEN_DC2_8_COUNT                        1
#define MOD_RATEGEN_DC2_8_DEVICE                       "IC1"
#define MOD_RATEGEN_DC2_8_DCINPALG12_ADDR              19
#define MOD_RATEGEN_DC2_8_DCINPALG12_FIXPT             0x00199999
#define MOD_RATEGEN_DC2_8_DCINPALG12_VALUE             SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.2)
#define MOD_RATEGEN_DC2_8_DCINPALG12_TYPE              SIGMASTUDIOTYPE_FIXPOINT

/* Module DC2_10 - DC Input Entry*/
#define MOD_RATEGEN_DC2_10_COUNT                       1
#define MOD_RATEGEN_DC2_10_DEVICE                      "IC1"
#define MOD_RATEGEN_DC2_10_DCINPALG13_ADDR             20
#define MOD_RATEGEN_DC2_10_DCINPALG13_FIXPT            0x00000000
#define MOD_RATEGEN_DC2_10_DCINPALG13_VALUE            SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD_RATEGEN_DC2_10_DCINPALG13_TYPE             SIGMASTUDIOTYPE_FIXPOINT

/* Module DC1_4 - DC Input Entry*/
#define MOD_DC1_4_COUNT                                1
#define MOD_DC1_4_DEVICE                               "IC1"
#define MOD_DC1_4_DCINPALG5_ADDR                       22
#define MOD_DC1_4_DCINPALG5_FIXPT                      0x00000000
#define MOD_DC1_4_DCINPALG5_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD_DC1_4_DCINPALG5_TYPE                       SIGMASTUDIOTYPE_FIXPOINT

/* Module CTRL_OFFSET - DC Input Entry*/
#define MOD_CTRL_OFFSET_COUNT                          1
#define MOD_CTRL_OFFSET_DEVICE                         "IC1"
#define MOD_CTRL_OFFSET_DCINPALG1_ADDR                 23
#define MOD_CTRL_OFFSET_DCINPALG1_FIXPT                0x0070A3D7
#define MOD_CTRL_OFFSET_DCINPALG1_VALUE                SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.88)
#define MOD_CTRL_OFFSET_DCINPALG1_TYPE                 SIGMASTUDIOTYPE_FIXPOINT

/* Module DC1_5 - DC Input Entry*/
#define MOD_DC1_5_COUNT                                1
#define MOD_DC1_5_DEVICE                               "IC1"
#define MOD_DC1_5_DCINPALG2_ADDR                       24
#define MOD_DC1_5_DCINPALG2_FIXPT                      0x00000000
#define MOD_DC1_5_DCINPALG2_VALUE                      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD_DC1_5_DCINPALG2_TYPE                       SIGMASTUDIOTYPE_FIXPOINT

/* Module Gain2 - Linear Gain*/
#define MOD_WAVEGEN_GAIN2_COUNT                        1
#define MOD_WAVEGEN_GAIN2_DEVICE                       "IC1"
#define MOD_WAVEGEN_GAIN2_GAIN1940ALGNS7_ADDR          25
#define MOD_WAVEGEN_GAIN2_GAIN1940ALGNS7_FIXPT         0x01400000
#define MOD_WAVEGEN_GAIN2_GAIN1940ALGNS7_VALUE         SIGMASTUDIOTYPE_FIXPOINT_CONVERT(2.5)
#define MOD_WAVEGEN_GAIN2_GAIN1940ALGNS7_TYPE          SIGMASTUDIOTYPE_FIXPOINT

/* Module CTRL_RATE - Single SW slew vol (adjustable)*/
#define MOD_RATEGEN_CTRL_RATE_COUNT                    2
#define MOD_RATEGEN_CTRL_RATE_DEVICE                   "IC1"
#define MOD_RATEGEN_CTRL_RATE_ALG0_TARGET_ADDR         26
#define MOD_RATEGEN_CTRL_RATE_ALG0_TARGET_FIXPT        0x00800000
#define MOD_RATEGEN_CTRL_RATE_ALG0_TARGET_VALUE        SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD_RATEGEN_CTRL_RATE_ALG0_TARGET_TYPE         SIGMASTUDIOTYPE_FIXPOINT
#define MOD_RATEGEN_CTRL_RATE_ALG0_STEP_ADDR           27
#define MOD_RATEGEN_CTRL_RATE_ALG0_STEP_FIXPT          0x00200000
#define MOD_RATEGEN_CTRL_RATE_ALG0_STEP_VALUE          SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.25)
#define MOD_RATEGEN_CTRL_RATE_ALG0_STEP_TYPE           SIGMASTUDIOTYPE_FIXPOINT

/* Module Gain3 - Linear Gain*/
#define MOD_GAIN3_COUNT                                1
#define MOD_GAIN3_DEVICE                               "IC1"
#define MOD_GAIN3_GAIN1940ALGNS3_ADDR                  28
#define MOD_GAIN3_GAIN1940ALGNS3_FIXPT                 0x006CCCCC
#define MOD_GAIN3_GAIN1940ALGNS3_VALUE                 SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.85)
#define MOD_GAIN3_GAIN1940ALGNS3_TYPE                  SIGMASTUDIOTYPE_FIXPOINT

/* Module PreGain - Linear Gain*/
#define MOD_PREGAIN_COUNT                              1
#define MOD_PREGAIN_DEVICE                             "IC1"
#define MOD_PREGAIN_GAIN1940ALGNS9_ADDR                29
#define MOD_PREGAIN_GAIN1940ALGNS9_FIXPT               0x02000000
#define MOD_PREGAIN_GAIN1940ALGNS9_VALUE               SIGMASTUDIOTYPE_FIXPOINT_CONVERT(4)
#define MOD_PREGAIN_GAIN1940ALGNS9_TYPE                SIGMASTUDIOTYPE_FIXPOINT

/* Module CTRL_FEEDBACK - Single SW slew vol (adjustable)*/
#define MOD_CTRL_FEEDBACK_COUNT                        2
#define MOD_CTRL_FEEDBACK_DEVICE                       "IC1"
#define MOD_CTRL_FEEDBACK_ALG0_TARGET_ADDR             30
#define MOD_CTRL_FEEDBACK_ALG0_TARGET_FIXPT            0x00075D9A
#define MOD_CTRL_FEEDBACK_ALG0_TARGET_VALUE            SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.0575439937337157)
#define MOD_CTRL_FEEDBACK_ALG0_TARGET_TYPE             SIGMASTUDIOTYPE_FIXPOINT
#define MOD_CTRL_FEEDBACK_ALG0_STEP_ADDR               31
#define MOD_CTRL_FEEDBACK_ALG0_STEP_FIXPT              0x00080000
#define MOD_CTRL_FEEDBACK_ALG0_STEP_VALUE              SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.0625)
#define MOD_CTRL_FEEDBACK_ALG0_STEP_TYPE               SIGMASTUDIOTYPE_FIXPOINT

/* Module Gain2_6 - Linear Gain*/
#define MOD_WAVEGEN_GAIN2_6_COUNT                      1
#define MOD_WAVEGEN_GAIN2_6_DEVICE                     "IC1"
#define MOD_WAVEGEN_GAIN2_6_GAIN1940ALGNS12_ADDR       32
#define MOD_WAVEGEN_GAIN2_6_GAIN1940ALGNS12_FIXPT      0x01000000
#define MOD_WAVEGEN_GAIN2_6_GAIN1940ALGNS12_VALUE      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(2)
#define MOD_WAVEGEN_GAIN2_6_GAIN1940ALGNS12_TYPE       SIGMASTUDIOTYPE_FIXPOINT

/* Module Gain1_2 - Linear Gain*/
#define MOD_RATEGEN_GAIN1_2_COUNT                      1
#define MOD_RATEGEN_GAIN1_2_DEVICE                     "IC1"
#define MOD_RATEGEN_GAIN1_2_GAIN1940ALGNS5_ADDR        33
#define MOD_RATEGEN_GAIN1_2_GAIN1940ALGNS5_FIXPT       0x02800000
#define MOD_RATEGEN_GAIN1_2_GAIN1940ALGNS5_VALUE       SIGMASTUDIOTYPE_FIXPOINT_CONVERT(5)
#define MOD_RATEGEN_GAIN1_2_GAIN1940ALGNS5_TYPE        SIGMASTUDIOTYPE_FIXPOINT

/* Module Delay1 - Delay*/
#define MOD_ALLPASSFILTER_DELAY1_COUNT                 12
#define MOD_ALLPASSFILTER_DELAY1_DEVICE                "IC1"
#define MOD_ALLPASSFILTER_DELAY1_ALG0_DELAYAMT_ADDR    34
#define MOD_ALLPASSFILTER_DELAY1_ALG0_DELAYAMT_FIXPT   0x00000001
#define MOD_ALLPASSFILTER_DELAY1_ALG0_DELAYAMT_VALUE   SIGMASTUDIOTYPE_INTEGER_CONVERT(1)
#define MOD_ALLPASSFILTER_DELAY1_ALG0_DELAYAMT_TYPE    SIGMASTUDIOTYPE_INTEGER
#define MOD_ALLPASSFILTER_2_DELAY1_ALG0_DELAYAMT_ADDR  59
#define MOD_ALLPASSFILTER_2_DELAY1_ALG0_DELAYAMT_FIXPT 0x00000001
#define MOD_ALLPASSFILTER_2_DELAY1_ALG0_DELAYAMT_VALUE SIGMASTUDIOTYPE_INTEGER_CONVERT(1)
#define MOD_ALLPASSFILTER_2_DELAY1_ALG0_DELAYAMT_TYPE  SIGMASTUDIOTYPE_INTEGER
#define MOD_ALLPASSFILTER_3_DELAY1_ALG0_DELAYAMT_ADDR  61
#define MOD_ALLPASSFILTER_3_DELAY1_ALG0_DELAYAMT_FIXPT 0x00000001
#define MOD_ALLPASSFILTER_3_DELAY1_ALG0_DELAYAMT_VALUE SIGMASTUDIOTYPE_INTEGER_CONVERT(1)
#define MOD_ALLPASSFILTER_3_DELAY1_ALG0_DELAYAMT_TYPE  SIGMASTUDIOTYPE_INTEGER
#define MOD_ALLPASSFILTER_4_DELAY1_ALG0_DELAYAMT_ADDR  63
#define MOD_ALLPASSFILTER_4_DELAY1_ALG0_DELAYAMT_FIXPT 0x00000001
#define MOD_ALLPASSFILTER_4_DELAY1_ALG0_DELAYAMT_VALUE SIGMASTUDIOTYPE_INTEGER_CONVERT(1)
#define MOD_ALLPASSFILTER_4_DELAY1_ALG0_DELAYAMT_TYPE  SIGMASTUDIOTYPE_INTEGER
#define MOD_ALLPASSFILTER_5_DELAY1_ALG0_DELAYAMT_ADDR  65
#define MOD_ALLPASSFILTER_5_DELAY1_ALG0_DELAYAMT_FIXPT 0x00000001
#define MOD_ALLPASSFILTER_5_DELAY1_ALG0_DELAYAMT_VALUE SIGMASTUDIOTYPE_INTEGER_CONVERT(1)
#define MOD_ALLPASSFILTER_5_DELAY1_ALG0_DELAYAMT_TYPE  SIGMASTUDIOTYPE_INTEGER
#define MOD_ALLPASSFILTER_6_DELAY1_ALG0_DELAYAMT_ADDR  67
#define MOD_ALLPASSFILTER_6_DELAY1_ALG0_DELAYAMT_FIXPT 0x00000001
#define MOD_ALLPASSFILTER_6_DELAY1_ALG0_DELAYAMT_VALUE SIGMASTUDIOTYPE_INTEGER_CONVERT(1)
#define MOD_ALLPASSFILTER_6_DELAY1_ALG0_DELAYAMT_TYPE  SIGMASTUDIOTYPE_INTEGER
#define MOD_ALLPASSFILTER_7_DELAY1_ALG0_DELAYAMT_ADDR  69
#define MOD_ALLPASSFILTER_7_DELAY1_ALG0_DELAYAMT_FIXPT 0x00000001
#define MOD_ALLPASSFILTER_7_DELAY1_ALG0_DELAYAMT_VALUE SIGMASTUDIOTYPE_INTEGER_CONVERT(1)
#define MOD_ALLPASSFILTER_7_DELAY1_ALG0_DELAYAMT_TYPE  SIGMASTUDIOTYPE_INTEGER
#define MOD_ALLPASSFILTER_8_DELAY1_ALG0_DELAYAMT_ADDR  71
#define MOD_ALLPASSFILTER_8_DELAY1_ALG0_DELAYAMT_FIXPT 0x00000001
#define MOD_ALLPASSFILTER_8_DELAY1_ALG0_DELAYAMT_VALUE SIGMASTUDIOTYPE_INTEGER_CONVERT(1)
#define MOD_ALLPASSFILTER_8_DELAY1_ALG0_DELAYAMT_TYPE  SIGMASTUDIOTYPE_INTEGER
#define MOD_ALLPASSFILTER_9_DELAY1_ALG0_DELAYAMT_ADDR  73
#define MOD_ALLPASSFILTER_9_DELAY1_ALG0_DELAYAMT_FIXPT 0x00000001
#define MOD_ALLPASSFILTER_9_DELAY1_ALG0_DELAYAMT_VALUE SIGMASTUDIOTYPE_INTEGER_CONVERT(1)
#define MOD_ALLPASSFILTER_9_DELAY1_ALG0_DELAYAMT_TYPE  SIGMASTUDIOTYPE_INTEGER
#define MOD_ALLPASSFILTER_10_DELAY1_ALG0_DELAYAMT_ADDR 75
#define MOD_ALLPASSFILTER_10_DELAY1_ALG0_DELAYAMT_FIXPT 0x00000001
#define MOD_ALLPASSFILTER_10_DELAY1_ALG0_DELAYAMT_VALUE SIGMASTUDIOTYPE_INTEGER_CONVERT(1)
#define MOD_ALLPASSFILTER_10_DELAY1_ALG0_DELAYAMT_TYPE SIGMASTUDIOTYPE_INTEGER
#define MOD_ALLPASSFILTER_11_DELAY1_ALG0_DELAYAMT_ADDR 77
#define MOD_ALLPASSFILTER_11_DELAY1_ALG0_DELAYAMT_FIXPT 0x00000001
#define MOD_ALLPASSFILTER_11_DELAY1_ALG0_DELAYAMT_VALUE SIGMASTUDIOTYPE_INTEGER_CONVERT(1)
#define MOD_ALLPASSFILTER_11_DELAY1_ALG0_DELAYAMT_TYPE SIGMASTUDIOTYPE_INTEGER
#define MOD_ALLPASSFILTER_12_DELAY1_ALG0_DELAYAMT_ADDR 79
#define MOD_ALLPASSFILTER_12_DELAY1_ALG0_DELAYAMT_FIXPT 0x00000001
#define MOD_ALLPASSFILTER_12_DELAY1_ALG0_DELAYAMT_VALUE SIGMASTUDIOTYPE_INTEGER_CONVERT(1)
#define MOD_ALLPASSFILTER_12_DELAY1_ALG0_DELAYAMT_TYPE SIGMASTUDIOTYPE_INTEGER

/* Module PeakEnv1 - Envelope Peak*/
#define MOD_RATEGEN_PEAKENV1_COUNT                     2
#define MOD_RATEGEN_PEAKENV1_DEVICE                    "IC1"
#define MOD_RATEGEN_PEAKENV1_ALG0_MONOENVELOPEPEAKALG1HOLD_ADDR 35
#define MOD_RATEGEN_PEAKENV1_ALG0_MONOENVELOPEPEAKALG1HOLD_FIXPT 0x000001E0
#define MOD_RATEGEN_PEAKENV1_ALG0_MONOENVELOPEPEAKALG1HOLD_VALUE SIGMASTUDIOTYPE_INTEGER_CONVERT(480)
#define MOD_RATEGEN_PEAKENV1_ALG0_MONOENVELOPEPEAKALG1HOLD_TYPE SIGMASTUDIOTYPE_INTEGER
#define MOD_RATEGEN_PEAKENV1_ALG0_MONOENVELOPEPEAKALG1DECAY_ADDR 36
#define MOD_RATEGEN_PEAKENV1_ALG0_MONOENVELOPEPEAKALG1DECAY_FIXPT 0x00000111
#define MOD_RATEGEN_PEAKENV1_ALG0_MONOENVELOPEPEAKALG1DECAY_VALUE SIGMASTUDIOTYPE_FIXPOINT_CONVERT(3.25520833333333E-05)
#define MOD_RATEGEN_PEAKENV1_ALG0_MONOENVELOPEPEAKALG1DECAY_TYPE SIGMASTUDIOTYPE_FIXPOINT

/* Module CTRL_MOD_SENS - Single Volume*/
#define MOD_RATEGEN_CTRL_MOD_SENS_COUNT                1
#define MOD_RATEGEN_CTRL_MOD_SENS_DEVICE               "IC1"
#define MOD_RATEGEN_CTRL_MOD_SENS_GAIN1940ALGNS4_ADDR  37
#define MOD_RATEGEN_CTRL_MOD_SENS_GAIN1940ALGNS4_FIXPT 0x000CCCCC
#define MOD_RATEGEN_CTRL_MOD_SENS_GAIN1940ALGNS4_VALUE SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.1)
#define MOD_RATEGEN_CTRL_MOD_SENS_GAIN1940ALGNS4_TYPE  SIGMASTUDIOTYPE_FIXPOINT

/* Module CTRL_MOD_SELECT - Mono Switch Nx1*/
#define MOD_RATEGEN_CTRL_MOD_SELECT_COUNT              1
#define MOD_RATEGEN_CTRL_MOD_SELECT_DEVICE             "IC1"
#define MOD_RATEGEN_CTRL_MOD_SELECT_MONOSWSLEW_ADDR    38
#define MOD_RATEGEN_CTRL_MOD_SELECT_MONOSWSLEW_FIXPT   0x00000000
#define MOD_RATEGEN_CTRL_MOD_SELECT_MONOSWSLEW_VALUE   SIGMASTUDIOTYPE_INTEGER_CONVERT(0)
#define MOD_RATEGEN_CTRL_MOD_SELECT_MONOSWSLEW_TYPE    SIGMASTUDIOTYPE_INTEGER

/* Module SW vol 2 - Single slew ext vol*/
#define MOD_SWVOL2_COUNT                               1
#define MOD_SWVOL2_DEVICE                              "IC1"
#define MOD_SWVOL2_EXTSWGAINDB1STEP_ADDR               39
#define MOD_SWVOL2_EXTSWGAINDB1STEP_FIXPT              0x00000800
#define MOD_SWVOL2_EXTSWGAINDB1STEP_VALUE              SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.000244140625)
#define MOD_SWVOL2_EXTSWGAINDB1STEP_TYPE               SIGMASTUDIOTYPE_FIXPOINT

/* Module Pulse2 - Pulse*/
#define MOD_WAVEGEN_PULSE2_COUNT                       1
#define MOD_WAVEGEN_PULSE2_DEVICE                      "IC1"
#define MOD_WAVEGEN_PULSE2_ISROUNDED_ADDR              40
#define MOD_WAVEGEN_PULSE2_ISROUNDED_FIXPT             0x00000000
#define MOD_WAVEGEN_PULSE2_ISROUNDED_VALUE             SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0)
#define MOD_WAVEGEN_PULSE2_ISROUNDED_TYPE              SIGMASTUDIOTYPE_FIXPOINT

/* Module VCO1 - VCO*/
#define MOD_WAVEGEN_VCO1_COUNT                         1
#define MOD_WAVEGEN_VCO1_DEVICE                        "IC1"
#define MOD_WAVEGEN_VCO1_VCOALG1MASK_ADDR              41
#define MOD_WAVEGEN_VCO1_VCOALG1MASK_FIXPT             0x000000FF
#define MOD_WAVEGEN_VCO1_VCOALG1MASK_VALUE             SIGMASTUDIOTYPE_INTEGER_CONVERT(255)
#define MOD_WAVEGEN_VCO1_VCOALG1MASK_TYPE              SIGMASTUDIOTYPE_INTEGER

/* Module Gain2_2 - Linear Gain*/
#define MOD_WAVEGEN_GAIN2_2_COUNT                      1
#define MOD_WAVEGEN_GAIN2_2_DEVICE                     "IC1"
#define MOD_WAVEGEN_GAIN2_2_GAIN1940ALGNS6_ADDR        42
#define MOD_WAVEGEN_GAIN2_2_GAIN1940ALGNS6_FIXPT       0x00800000
#define MOD_WAVEGEN_GAIN2_2_GAIN1940ALGNS6_VALUE       SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD_WAVEGEN_GAIN2_2_GAIN1940ALGNS6_TYPE        SIGMASTUDIOTYPE_FIXPOINT

/* Module Gain2_5 - Linear Gain*/
#define MOD_WAVEGEN_GAIN2_5_COUNT                      1
#define MOD_WAVEGEN_GAIN2_5_DEVICE                     "IC1"
#define MOD_WAVEGEN_GAIN2_5_GAIN1940ALGNS11_ADDR       43
#define MOD_WAVEGEN_GAIN2_5_GAIN1940ALGNS11_FIXPT      0xFF800000
#define MOD_WAVEGEN_GAIN2_5_GAIN1940ALGNS11_VALUE      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-1)
#define MOD_WAVEGEN_GAIN2_5_GAIN1940ALGNS11_TYPE       SIGMASTUDIOTYPE_FIXPOINT

/* Module VCO1_2 - VCO*/
#define MOD_WAVEGEN_VCO1_2_COUNT                       1
#define MOD_WAVEGEN_VCO1_2_DEVICE                      "IC1"
#define MOD_WAVEGEN_VCO1_2_VCOALG2MASK_ADDR            44
#define MOD_WAVEGEN_VCO1_2_VCOALG2MASK_FIXPT           0x000000FF
#define MOD_WAVEGEN_VCO1_2_VCOALG2MASK_VALUE           SIGMASTUDIOTYPE_INTEGER_CONVERT(255)
#define MOD_WAVEGEN_VCO1_2_VCOALG2MASK_TYPE            SIGMASTUDIOTYPE_INTEGER

/* Module Gain2_7 - Linear Gain*/
#define MOD_WAVEGEN_GAIN2_7_COUNT                      1
#define MOD_WAVEGEN_GAIN2_7_DEVICE                     "IC1"
#define MOD_WAVEGEN_GAIN2_7_GAIN1940ALGNS14_ADDR       45
#define MOD_WAVEGEN_GAIN2_7_GAIN1940ALGNS14_FIXPT      0x07FFFFF7
#define MOD_WAVEGEN_GAIN2_7_GAIN1940ALGNS14_VALUE      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(15.999999)
#define MOD_WAVEGEN_GAIN2_7_GAIN1940ALGNS14_TYPE       SIGMASTUDIOTYPE_FIXPOINT

/* Module Gain2_8 - Linear Gain*/
#define MOD_WAVEGEN_GAIN2_8_COUNT                      1
#define MOD_WAVEGEN_GAIN2_8_DEVICE                     "IC1"
#define MOD_WAVEGEN_GAIN2_8_GAIN1940ALGNS15_ADDR       46
#define MOD_WAVEGEN_GAIN2_8_GAIN1940ALGNS15_FIXPT      0x07FFFFF7
#define MOD_WAVEGEN_GAIN2_8_GAIN1940ALGNS15_VALUE      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(15.999999)
#define MOD_WAVEGEN_GAIN2_8_GAIN1940ALGNS15_TYPE       SIGMASTUDIOTYPE_FIXPOINT

/* Module Gain2_9 - Linear Gain*/
#define MOD_WAVEGEN_GAIN2_9_COUNT                      1
#define MOD_WAVEGEN_GAIN2_9_DEVICE                     "IC1"
#define MOD_WAVEGEN_GAIN2_9_GAIN1940ALGNS16_ADDR       47
#define MOD_WAVEGEN_GAIN2_9_GAIN1940ALGNS16_FIXPT      0x07FFFFF7
#define MOD_WAVEGEN_GAIN2_9_GAIN1940ALGNS16_VALUE      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(15.999999)
#define MOD_WAVEGEN_GAIN2_9_GAIN1940ALGNS16_TYPE       SIGMASTUDIOTYPE_FIXPOINT

/* Module SW vol 1 - Single SW slew vol (adjustable)*/
#define MOD_WAVEGEN_SWVOL1_COUNT                       2
#define MOD_WAVEGEN_SWVOL1_DEVICE                      "IC1"
#define MOD_WAVEGEN_SWVOL1_ALG0_TARGET_ADDR            48
#define MOD_WAVEGEN_SWVOL1_ALG0_TARGET_FIXPT           0x00800000
#define MOD_WAVEGEN_SWVOL1_ALG0_TARGET_VALUE           SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD_WAVEGEN_SWVOL1_ALG0_TARGET_TYPE            SIGMASTUDIOTYPE_FIXPOINT
#define MOD_WAVEGEN_SWVOL1_ALG0_STEP_ADDR              49
#define MOD_WAVEGEN_SWVOL1_ALG0_STEP_FIXPT             0x00000010
#define MOD_WAVEGEN_SWVOL1_ALG0_STEP_VALUE             SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1.9073486328125E-06)
#define MOD_WAVEGEN_SWVOL1_ALG0_STEP_TYPE              SIGMASTUDIOTYPE_FIXPOINT

/* Module Gain2_3 - Linear Gain*/
#define MOD_WAVEGEN_GAIN2_3_COUNT                      1
#define MOD_WAVEGEN_GAIN2_3_DEVICE                     "IC1"
#define MOD_WAVEGEN_GAIN2_3_GAIN1940ALGNS8_ADDR        50
#define MOD_WAVEGEN_GAIN2_3_GAIN1940ALGNS8_FIXPT       0x00800000
#define MOD_WAVEGEN_GAIN2_3_GAIN1940ALGNS8_VALUE       SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD_WAVEGEN_GAIN2_3_GAIN1940ALGNS8_TYPE        SIGMASTUDIOTYPE_FIXPOINT

/* Module Gain2_4 - Linear Gain*/
#define MOD_WAVEGEN_GAIN2_4_COUNT                      1
#define MOD_WAVEGEN_GAIN2_4_DEVICE                     "IC1"
#define MOD_WAVEGEN_GAIN2_4_GAIN1940ALGNS10_ADDR       51
#define MOD_WAVEGEN_GAIN2_4_GAIN1940ALGNS10_FIXPT      0xFF800000
#define MOD_WAVEGEN_GAIN2_4_GAIN1940ALGNS10_VALUE      SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-1)
#define MOD_WAVEGEN_GAIN2_4_GAIN1940ALGNS10_TYPE       SIGMASTUDIOTYPE_FIXPOINT

/* Module Gain2_10 - Linear Gain*/
#define MOD_WAVEGEN_GAIN2_10_COUNT                     1
#define MOD_WAVEGEN_GAIN2_10_DEVICE                    "IC1"
#define MOD_WAVEGEN_GAIN2_10_GAIN1940ALGNS17_ADDR      52
#define MOD_WAVEGEN_GAIN2_10_GAIN1940ALGNS17_FIXPT     0x01000000
#define MOD_WAVEGEN_GAIN2_10_GAIN1940ALGNS17_VALUE     SIGMASTUDIOTYPE_FIXPOINT_CONVERT(2)
#define MOD_WAVEGEN_GAIN2_10_GAIN1940ALGNS17_TYPE      SIGMASTUDIOTYPE_FIXPOINT

/* Module CTRL_WAVE - Mono Switch Nx1*/
#define MOD_WAVEGEN_CTRL_WAVE_COUNT                    1
#define MOD_WAVEGEN_CTRL_WAVE_DEVICE                   "IC1"
#define MOD_WAVEGEN_CTRL_WAVE_MONOSWSLEW_ADDR          53
#define MOD_WAVEGEN_CTRL_WAVE_MONOSWSLEW_FIXPT         0x00000000
#define MOD_WAVEGEN_CTRL_WAVE_MONOSWSLEW_VALUE         SIGMASTUDIOTYPE_INTEGER_CONVERT(0)
#define MOD_WAVEGEN_CTRL_WAVE_MONOSWSLEW_TYPE          SIGMASTUDIOTYPE_INTEGER

/* Module CTRL_WIDTH - Linear Gain*/
#define MOD_CTRL_WIDTH_COUNT                           1
#define MOD_CTRL_WIDTH_DEVICE                          "IC1"
#define MOD_CTRL_WIDTH_GAIN1940ALGNS1_ADDR             54
#define MOD_CTRL_WIDTH_GAIN1940ALGNS1_FIXPT            0x000B645A
#define MOD_CTRL_WIDTH_GAIN1940ALGNS1_VALUE            SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.089)
#define MOD_CTRL_WIDTH_GAIN1940ALGNS1_TYPE             SIGMASTUDIOTYPE_FIXPOINT

/* Module Gain1_3 - Linear Gain*/
#define MOD_GAIN1_3_COUNT                              1
#define MOD_GAIN1_3_DEVICE                             "IC1"
#define MOD_GAIN1_3_GAIN1940ALGNS2_ADDR                55
#define MOD_GAIN1_3_GAIN1940ALGNS2_FIXPT               0xFF99999A
#define MOD_GAIN1_3_GAIN1940ALGNS2_VALUE               SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-0.8)
#define MOD_GAIN1_3_GAIN1940ALGNS2_TYPE                SIGMASTUDIOTYPE_FIXPOINT

/* Module Inv1 - Signal Invert*/
#define MOD_ALLPASSFILTER_INV1_COUNT                   12
#define MOD_ALLPASSFILTER_INV1_DEVICE                  "IC1"
#define MOD_ALLPASSFILTER_INV1_ALG0_EQ1940INVERT1GAIN_ADDR 56
#define MOD_ALLPASSFILTER_INV1_ALG0_EQ1940INVERT1GAIN_FIXPT 0xFF800000
#define MOD_ALLPASSFILTER_INV1_ALG0_EQ1940INVERT1GAIN_VALUE SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-1)
#define MOD_ALLPASSFILTER_INV1_ALG0_EQ1940INVERT1GAIN_TYPE SIGMASTUDIOTYPE_FIXPOINT
#define MOD_ALLPASSFILTER_2_INV1_ALG0_EQ1940INVERT2GAIN_ADDR 60
#define MOD_ALLPASSFILTER_2_INV1_ALG0_EQ1940INVERT2GAIN_FIXPT 0xFF800000
#define MOD_ALLPASSFILTER_2_INV1_ALG0_EQ1940INVERT2GAIN_VALUE SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-1)
#define MOD_ALLPASSFILTER_2_INV1_ALG0_EQ1940INVERT2GAIN_TYPE SIGMASTUDIOTYPE_FIXPOINT
#define MOD_ALLPASSFILTER_3_INV1_ALG0_EQ1940INVERT3GAIN_ADDR 62
#define MOD_ALLPASSFILTER_3_INV1_ALG0_EQ1940INVERT3GAIN_FIXPT 0xFF800000
#define MOD_ALLPASSFILTER_3_INV1_ALG0_EQ1940INVERT3GAIN_VALUE SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-1)
#define MOD_ALLPASSFILTER_3_INV1_ALG0_EQ1940INVERT3GAIN_TYPE SIGMASTUDIOTYPE_FIXPOINT
#define MOD_ALLPASSFILTER_4_INV1_ALG0_EQ1940INVERT4GAIN_ADDR 64
#define MOD_ALLPASSFILTER_4_INV1_ALG0_EQ1940INVERT4GAIN_FIXPT 0xFF800000
#define MOD_ALLPASSFILTER_4_INV1_ALG0_EQ1940INVERT4GAIN_VALUE SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-1)
#define MOD_ALLPASSFILTER_4_INV1_ALG0_EQ1940INVERT4GAIN_TYPE SIGMASTUDIOTYPE_FIXPOINT
#define MOD_ALLPASSFILTER_5_INV1_ALG0_EQ1940INVERT5GAIN_ADDR 66
#define MOD_ALLPASSFILTER_5_INV1_ALG0_EQ1940INVERT5GAIN_FIXPT 0xFF800000
#define MOD_ALLPASSFILTER_5_INV1_ALG0_EQ1940INVERT5GAIN_VALUE SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-1)
#define MOD_ALLPASSFILTER_5_INV1_ALG0_EQ1940INVERT5GAIN_TYPE SIGMASTUDIOTYPE_FIXPOINT
#define MOD_ALLPASSFILTER_6_INV1_ALG0_EQ1940INVERT6GAIN_ADDR 68
#define MOD_ALLPASSFILTER_6_INV1_ALG0_EQ1940INVERT6GAIN_FIXPT 0xFF800000
#define MOD_ALLPASSFILTER_6_INV1_ALG0_EQ1940INVERT6GAIN_VALUE SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-1)
#define MOD_ALLPASSFILTER_6_INV1_ALG0_EQ1940INVERT6GAIN_TYPE SIGMASTUDIOTYPE_FIXPOINT
#define MOD_ALLPASSFILTER_7_INV1_ALG0_EQ1940INVERT7GAIN_ADDR 70
#define MOD_ALLPASSFILTER_7_INV1_ALG0_EQ1940INVERT7GAIN_FIXPT 0xFF800000
#define MOD_ALLPASSFILTER_7_INV1_ALG0_EQ1940INVERT7GAIN_VALUE SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-1)
#define MOD_ALLPASSFILTER_7_INV1_ALG0_EQ1940INVERT7GAIN_TYPE SIGMASTUDIOTYPE_FIXPOINT
#define MOD_ALLPASSFILTER_8_INV1_ALG0_EQ1940INVERT8GAIN_ADDR 72
#define MOD_ALLPASSFILTER_8_INV1_ALG0_EQ1940INVERT8GAIN_FIXPT 0xFF800000
#define MOD_ALLPASSFILTER_8_INV1_ALG0_EQ1940INVERT8GAIN_VALUE SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-1)
#define MOD_ALLPASSFILTER_8_INV1_ALG0_EQ1940INVERT8GAIN_TYPE SIGMASTUDIOTYPE_FIXPOINT
#define MOD_ALLPASSFILTER_9_INV1_ALG0_EQ1940INVERT9GAIN_ADDR 74
#define MOD_ALLPASSFILTER_9_INV1_ALG0_EQ1940INVERT9GAIN_FIXPT 0xFF800000
#define MOD_ALLPASSFILTER_9_INV1_ALG0_EQ1940INVERT9GAIN_VALUE SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-1)
#define MOD_ALLPASSFILTER_9_INV1_ALG0_EQ1940INVERT9GAIN_TYPE SIGMASTUDIOTYPE_FIXPOINT
#define MOD_ALLPASSFILTER_10_INV1_ALG0_EQ1940INVERT10GAIN_ADDR 76
#define MOD_ALLPASSFILTER_10_INV1_ALG0_EQ1940INVERT10GAIN_FIXPT 0xFF800000
#define MOD_ALLPASSFILTER_10_INV1_ALG0_EQ1940INVERT10GAIN_VALUE SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-1)
#define MOD_ALLPASSFILTER_10_INV1_ALG0_EQ1940INVERT10GAIN_TYPE SIGMASTUDIOTYPE_FIXPOINT
#define MOD_ALLPASSFILTER_11_INV1_ALG0_EQ1940INVERT11GAIN_ADDR 78
#define MOD_ALLPASSFILTER_11_INV1_ALG0_EQ1940INVERT11GAIN_FIXPT 0xFF800000
#define MOD_ALLPASSFILTER_11_INV1_ALG0_EQ1940INVERT11GAIN_VALUE SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-1)
#define MOD_ALLPASSFILTER_11_INV1_ALG0_EQ1940INVERT11GAIN_TYPE SIGMASTUDIOTYPE_FIXPOINT
#define MOD_ALLPASSFILTER_12_INV1_ALG0_EQ1940INVERT12GAIN_ADDR 80
#define MOD_ALLPASSFILTER_12_INV1_ALG0_EQ1940INVERT12GAIN_FIXPT 0xFF800000
#define MOD_ALLPASSFILTER_12_INV1_ALG0_EQ1940INVERT12GAIN_VALUE SIGMASTUDIOTYPE_FIXPOINT_CONVERT(-1)
#define MOD_ALLPASSFILTER_12_INV1_ALG0_EQ1940INVERT12GAIN_TYPE SIGMASTUDIOTYPE_FIXPOINT

/* Module NxM Mixer1 - NxM Mixer*/
#define MOD_NXMMIXER1_COUNT                            2
#define MOD_NXMMIXER1_DEVICE                           "IC1"
#define MOD_NXMMIXER1_ALG0_NXNMIXER1940ALG10000_ADDR   57
#define MOD_NXMMIXER1_ALG0_NXNMIXER1940ALG10000_FIXPT  0x008F9E4C
#define MOD_NXMMIXER1_ALG0_NXNMIXER1940ALG10000_VALUE  SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1.12201845430196)
#define MOD_NXMMIXER1_ALG0_NXNMIXER1940ALG10000_TYPE   SIGMASTUDIOTYPE_FIXPOINT
#define MOD_NXMMIXER1_ALG0_NXNMIXER1940ALG10001_ADDR   58
#define MOD_NXMMIXER1_ALG0_NXNMIXER1940ALG10001_FIXPT  0x00800000
#define MOD_NXMMIXER1_ALG0_NXNMIXER1940ALG10001_VALUE  SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD_NXMMIXER1_ALG0_NXNMIXER1940ALG10001_TYPE   SIGMASTUDIOTYPE_FIXPOINT

/* Module CTRL_STAGES - Mono Switch Nx1*/
#define MOD_CTRL_STAGES_COUNT                          1
#define MOD_CTRL_STAGES_DEVICE                         "IC1"
#define MOD_CTRL_STAGES_MONOSWSLEW_ADDR                81
#define MOD_CTRL_STAGES_MONOSWSLEW_FIXPT               0x00000000
#define MOD_CTRL_STAGES_MONOSWSLEW_VALUE               SIGMASTUDIOTYPE_INTEGER_CONVERT(0)
#define MOD_CTRL_STAGES_MONOSWSLEW_TYPE                SIGMASTUDIOTYPE_INTEGER

/* Module CTRL_DEPTH - Single SW slew vol (adjustable)*/
#define MOD_CTRL_DEPTH_COUNT                           2
#define MOD_CTRL_DEPTH_DEVICE                          "IC1"
#define MOD_CTRL_DEPTH_ALG0_TARGET_ADDR                82
#define MOD_CTRL_DEPTH_ALG0_TARGET_FIXPT               0x00588DEA
#define MOD_CTRL_DEPTH_ALG0_TARGET_VALUE               SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.691830970918937)
#define MOD_CTRL_DEPTH_ALG0_TARGET_TYPE                SIGMASTUDIOTYPE_FIXPOINT
#define MOD_CTRL_DEPTH_ALG0_STEP_ADDR                  83
#define MOD_CTRL_DEPTH_ALG0_STEP_FIXPT                 0x00080000
#define MOD_CTRL_DEPTH_ALG0_STEP_VALUE                 SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.0625)
#define MOD_CTRL_DEPTH_ALG0_STEP_TYPE                  SIGMASTUDIOTYPE_FIXPOINT

/* Module Gain3_2 - Linear Gain*/
#define MOD_GAIN3_2_COUNT                              1
#define MOD_GAIN3_2_DEVICE                             "IC1"
#define MOD_GAIN3_2_GAIN1940ALGNS13_ADDR               84
#define MOD_GAIN3_2_GAIN1940ALGNS13_FIXPT              0x00800000
#define MOD_GAIN3_2_GAIN1940ALGNS13_VALUE              SIGMASTUDIOTYPE_FIXPOINT_CONVERT(1)
#define MOD_GAIN3_2_GAIN1940ALGNS13_TYPE               SIGMASTUDIOTYPE_FIXPOINT

/* Module Mg2 - Signal Merger*/
#define MOD_MG2_COUNT                                  1
#define MOD_MG2_DEVICE                                 "IC1"
#define MOD_MG2_SINGLECTRLMIXER19402_ADDR              85
#define MOD_MG2_SINGLECTRLMIXER19402_FIXPT             0x00400000
#define MOD_MG2_SINGLECTRLMIXER19402_VALUE             SIGMASTUDIOTYPE_FIXPOINT_CONVERT(0.5)
#define MOD_MG2_SINGLECTRLMIXER19402_TYPE              SIGMASTUDIOTYPE_FIXPOINT

#endif
