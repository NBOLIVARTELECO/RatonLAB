#include <xc.h>
#include "ultrasonic.h"

#define _XTAL_FREQ 20000000

void Ultrasonic_Init(void)
{
    TRISBbits.TRISB0 = 0; // TRIG
    TRISBbits.TRISB1 = 1; // ECHO

    RB0 = 0;

    T1CON = 0x01;
//Timer1 ON
//Prescaler 1:1
//Reloj interno (Fosc/4)
}

unsigned int Ultrasonic_Read(void)
{
     unsigned int tiempo;
    unsigned int timeout;

    RB0 = 1;
    __delay_us(10);
    RB0 = 0;

    timeout = 60000;

    while(!RB1 && timeout--)
        

    if(timeout == 0)
        return 999;

    TMR1H = 0;
    TMR1L = 0;

    T1CON = 0x01;

    timeout = 60000;

    while(RB1 && timeout--)
        ;

    T1CONbits.TMR1ON = 0;

    tiempo = ((unsigned int)TMR1H << 8) | TMR1L;

    return tiempo / 290;
}