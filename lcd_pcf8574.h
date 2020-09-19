// LIQUIDCRYSTAL_I2C_PCF8574 V1.0

#ifndef LIQUIDCRYSTAL_I2C_PCF8574_H
#define LIQUIDCRYSTAL_I2C_PCF8574_H

#ifdef	__cplusplus
extern "C" {
#endif

  void LCD_Init(void);
  void LCD_Write_Char(char message);
  void LCD_Write_Str(const char *message);
  void LCD_Write_Str_Padded(const char *message, char len);
  void LCD_Write_Str_Padded_Right(const char *message, char len);
  void LCD_Write_Str_Zero_Padded_Right(const char *message, char len);
  
  void LCD_Clear(void);
  void LCD_Home(void);

  void LCDdisplayOff(void);
  void LCDdisplayOn(void);
  void LCD_BlinkOff(void);
  void LCD_BlinkOn(void);
  void LCD_CursorOff(void);
  void LCD_CursorOn(void);
  void LCDscrollDisplayLeft(void);
  void LCDscrollDisplayRight(void);
  void LCDleftToRight(void);
  void LCDrightToLeft(void);
  void LCDnoBacklight(void);
  void LCDbacklight(void);
  void LCDautoscroll(void);
  void LCDnoAutoscroll(void);
  void LCDcreateChar(unsigned char location, unsigned char charmap[]);
  void LCD_SetCursor(unsigned char col, unsigned char row);

  inline void LCDcommandWrite(unsigned char value);
  inline unsigned char LCDcommandRead(void);
  inline void LCDdataWrite(unsigned char value);
  inline unsigned char LCDdataRead(void);
  unsigned char LCDbusy(void);
  unsigned char LCDaddressCounter(void);
  unsigned char LCDreadDDRam(unsigned char address);
  unsigned char LCDreadCGRam(unsigned char address);
  void lcd_load_custom_characters(void);

#ifdef	__cplusplus
}
#endif

#endif // LIQUIDCRYSTAL_I2C_PCF8574_H
