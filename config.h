#ifndef CONFIG_H
#define CONFIG_H

// I2C addresses
#define I2C_ADDRESS_ADAU1701            0x68
#define I2C_ADDRESS_MCP45_PRE_GAIN      0x78 //0b0111100 //0x21;//change this
#define I2C_ADDRESS_MCP45_POST_GAIN     0x7A //0b0111101 //0x21;//change this
#define I2C_ADDRESS_EEPROM_WRITE        0xA0// last bit is R(1) or W(0)
#define I2C_ADDRESS_EEPROM_READ         0xA1// last bit is R(1) or W(0)
#define I2C_ADDRESS_LCD                 0x4E // (0x27<<1)  

// EEPROM model map
#define EEPROM_SYSTEM_SIZE  255
#define EEPROM_MODEL_SIZE   30 
#define EEPROM_PATCH_SIZE   16 

#define EEPROM_SYSTEM_NUM   1
#define EEPROM_MODEL_NUM    10
#define EEPROM_PATCH_NUM    100

#define EEPROM_SYSTEM_START 0
#define EEPROM_MODEL_START  (EEPROM_SYSTEM_SIZE * EEPROM_SYSTEM_NUM)
#define EEPROM_PATCH_START  (EEPROM_MODEL_START + (EEPROM_MODEL_SIZE * EEPROM_MODEL_NUM))

#define EEPROM_MODEL_INDEX_NAME     0
#define EEPROM_MODEL_SIZE_NAME      8
#define EEPROM_MODEL_INDEX_CHANNEL  8
#define EEPROM_MODEL_SIZE_CHANNEL   1
#define EEPROM_MODEL_INDEX_ZINPUT   9
#define EEPROM_MODEL_SIZE_ZINPUT    1
#define EEPROM_MODEL_INDEX_GAIN_MIN 10
#define EEPROM_MODEL_SIZE_GAIN_MIN  1
#define EEPROM_MODEL_INDEX_GAIN_MAX 10
#define EEPROM_MODEL_SIZE_GAIN_MAX  1

#define EEPROM_PATCH_INDEX_NAME     0
#define EEPORM_PATCH_SIZE_NAME      8
#define EEPROM_PATCH_INDEX_MODEL    8
#define EEPROM_PATCH_SIZE_MODEL     1
#define EEPROM_PATCH_INDEX_GAIN     9
#define EEPROM_PATCH_SIZE_GAIN      1
#define EEPROM_PATCH_INDEX_LOW      10
#define EEPROM_PATCH_SIZE_LOW       1

// PCComm stuff
#define COMM_PATCH_NAME     1
#define COMM_PATCH_MODEL    2
#define COMM_PATCH_GAIN     3
#define COMM_PATCH_LOW      4
#define COMM_PATCH_MID      5
#define COMM_PATCH_HIGH     6
#define COMM_PATCH_PRES     7
#define COMM_PATCH_VOL      8

// LCD stuff
#define LCD_CC_BAR_1    0
#define LCD_CC_BAR_2    1
#define LCD_CC_BAR_3    2
#define LCD_CC_BAR_4    3
#define LCD_CC_BAR_5    4
#define LCD_CC_BAR_6    5
#define LCD_CC_BAR_7    6
#define LCD_CC_BAR_8    255




#endif