#include <xc.h>
#include "motor.h"

//PIC16F877A         L298N
//
//RC0 -------------> IN1
//RC1 -------------> IN2
//
//RC3 -------------> IN3
//RC4 -------------> IN4
//
//RC2 (PWM) -------> ENA
//                    |
//                    +-> ENB

void Motor_Init(void)
{
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC4 = 0;

    PORTC = 0x00;

    // PWM
    PR2 = 255;

    CCP1CON = 0x0C;

    T2CON = 0x04;

    CCPR1L = 0;
    
    TMR2 = 0;
    
    PIR1bits.TMR2IF = 0;
}
void Motor_SetSpeed(unsigned int duty)
{
    if(duty > 1023)
        duty = 1023;

    CCPR1L = duty >> 2;

    CCP1CON &= 0xCF;
    CCP1CON |= (duty & 0x03) << 4;
}
void Motor_Adelante(void)
{
    RC0 = 1;//motor der
    RC1 = 0;

    RC3 = 0;//motor izqu
    RC4 = 1;
}
void Motor_Atras(void)
{
    RC0 = 0;
    RC1 = 1;

    RC3 = 1;
    RC4 = 0;
}
void Motor_Izquierda(void)
{
    RC0 = 1;
    RC1 = 0;

    RC3 = 1;
    RC4 = 0;
}
void Motor_Derecha(void)
{
    RC0 = 0;
    RC1 = 1;

    RC3 = 0;
    RC4 = 1;
}
void Motor_CorregirDerecha(void)
{
    // Motor derecho adelante
    RC0 = 1;
    RC1 = 0;

    // Motor izquierdo detenido
    RC3 = 0;
    RC4 = 0;
}
void Motor_CorregirIzquierda(void)
{
    // Motor derecho detenido
    RC0 = 0;
    RC1 = 0;

    // Motor derizquierdoecho adelante
    RC3 = 0;
    RC4 = 1;
}
void Motor_Stop(void)
{
    RC0 = 0;
    RC1 = 0;

    RC3 = 0;
    RC4 = 0;
}