#ifndef LCD_H
#define LCD_H

void LCD_Init(void);
void LCD_Clear(void);

void LCD_Cmd(unsigned char cmd);
void LCD_Data(unsigned char data);

void LCD_SetCursor(unsigned char row, unsigned char col);

void LCD_Write_Char(char c);
void LCD_Write_String(const char *str);

#endif