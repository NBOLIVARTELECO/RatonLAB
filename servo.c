#include <xc.h>
#include "servo.h"

#define _XTAL_FREQ 20000000

void Servo_Init(void)
{
    TRISBbits.TRISB2 = 0;
    RB2 = 0;
}

void Servo_Izquierda(void)
{
    unsigned char i;

    for(i=0; i<25; i++)
    {
        RB2 = 1;
        __delay_us(800);

        RB2 = 0;
        __delay_ms(19);
    }
}

void Servo_Centro(void)
{
    unsigned char i;

    for(i=0; i<25; i++)
    {
        RB2 = 1;
        __delay_us(1500);

        RB2 = 0;
        __delay_ms(18);
    }
}

void Servo_Derecha(void)
{
    unsigned char i;

    for(i=0; i<25; i++)
    {
        RB2 = 1;
        __delay_us(2200);

        RB2 = 0;
        __delay_ms(18);
    }
}