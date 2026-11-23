#include <xc.h>
#include "lcd.h"

#define _XTAL_FREQ 20000000

#define RS RA1
#define EN RA2

#define D4 RE0
#define D5 RE1
#define D6 RE2
#define D7 RA3

static void LCD_Enable(void)
{
    EN = 1;
    __delay_us(5);

    EN = 0;
    __delay_us(100);
}

static void LCD_Send4Bits(unsigned char nibble)
{
    D4 = (nibble >> 0) & 0x01;
    D5 = (nibble >> 1) & 0x01;
    D6 = (nibble >> 2) & 0x01;
    D7 = (nibble >> 3) & 0x01;

    LCD_Enable();
}

void LCD_Cmd(unsigned char cmd)
{
    RS = 0;

    LCD_Send4Bits(cmd >> 4);
    LCD_Send4Bits(cmd & 0x0F);

    __delay_ms(2);
}

void LCD_Data(unsigned char data)
{
    RS = 1;

    LCD_Send4Bits(data >> 4);
    LCD_Send4Bits(data & 0x0F);

    __delay_ms(2);
}

void LCD_Clear(void)
{
    LCD_Cmd(0x01);
    __delay_ms(2);
}

void LCD_SetCursor(unsigned char row, unsigned char col)
{
    unsigned char pos;

    if(row == 1)
        pos = 0x80 + (col - 1);
    else
        pos = 0xC0 + (col - 1);

    LCD_Cmd(pos);
}

void LCD_Write_Char(char c)
{
    LCD_Data(c);
}

void LCD_Write_String(const char *str)
{
    while(*str)
    {
        LCD_Data(*str++);
    }
}

void LCD_Init(void)
{
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;

    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE2 = 0;

    RS = 0;
    EN = 0;

    __delay_ms(20);

    LCD_Send4Bits(0x03);
    __delay_ms(5);

    LCD_Send4Bits(0x03);
    __delay_us(200);

    LCD_Send4Bits(0x03);
    __delay_us(200);

    LCD_Send4Bits(0x02);

    LCD_Cmd(0x28); // 4 bits, 2 líneas
    LCD_Cmd(0x0C); // display ON
    LCD_Cmd(0x06); // cursor avance
    LCD_Cmd(0x01); // clear

    __delay_ms(2);
}