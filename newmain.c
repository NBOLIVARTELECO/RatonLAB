#include <xc.h>
#include "motor.h"

// CONFIG

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define _XTAL_FREQ 20000000

// Estados del robot
typedef enum
{
    ESTADO_STOP = 0,
    ESTADO_ADELANTE,
    ESTADO_ATRAS,
    ESTADO_IZQUIERDA,
    ESTADO_DERECHA

} EstadoRobot;

EstadoRobot estadoActual;

void Sistema_Init(void);

void main(void)
{
    Sistema_Init();
    unsigned int vel =500;

    estadoActual = ESTADO_STOP;

    while(1)
    {
        switch(estadoActual)
        {
            case ESTADO_STOP:

                Motor_Stop();
                Motor_SetSpeed(0);

                __delay_ms(1000);

                estadoActual = ESTADO_ADELANTE;

                break;

            case ESTADO_ADELANTE:

                Motor_SetSpeed(vel);
                Motor_Adelante();

                __delay_ms(3000);

                estadoActual = ESTADO_IZQUIERDA;

                break;

            case ESTADO_IZQUIERDA:

                Motor_SetSpeed(vel);
                Motor_Izquierda();

                __delay_ms(1500);

                estadoActual = ESTADO_DERECHA;

                break;

            case ESTADO_DERECHA:

                Motor_SetSpeed(vel);
                Motor_Derecha();

                __delay_ms(1500);

                estadoActual = ESTADO_ATRAS;

                break;

            case ESTADO_ATRAS:

                Motor_SetSpeed(vel);
                Motor_Atras();

                __delay_ms(3000);

                estadoActual = ESTADO_STOP;

                break;
        }
    }
}

void Sistema_Init(void)
{
    Motor_Init();
}
