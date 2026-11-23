#include "navigation.h"
#include "ultrasonic.h"
#include "servo.h"
#include "motor.h"
#include "lcd.h"

#include <xc.h>
#include <stdio.h>

#define _XTAL_FREQ 20000000

#define DIST_MIN       15
#define DIST_LATERAL   20
#define MARGEN_GIRO    5
#define DIST_EMERGENCIA 10

#define SPEED_MIN      500
#define SPEED_GIRO     500
#define SPEED_NORMAL   500
#define SPEED_BACK     500

typedef enum
{
    NAV_ADELANTE,
    NAV_GIRO_IZQ,
    NAV_GIRO_DER,
    NAV_REVERSA

} NavState;

NavState estadoNav;

NavState estadoNav = NAV_ADELANTE;

unsigned char tiempoEstado = 0;
Distancias entorno;
unsigned char ciclos;
void Message(char *mensaje, unsigned int distancia);

void Navigation_Init(void)
{
    
    Servo_Centro();
    entorno.centro = Ultrasonic_Read();

    Servo_Izquierda();
    entorno.izquierda = Ultrasonic_Read();

    Servo_Derecha();
    entorno.derecha = Ultrasonic_Read();
}

void Navigation_Scan(void)
{
    Servo_Centro();
    __delay_ms(50);

    entorno.centro = Ultrasonic_Read();

    Navigation_Decision();

    Servo_Izquierda();
    __delay_ms(50);

    entorno.izquierda = Ultrasonic_Read();

    Navigation_Decision();

    Servo_Derecha();
    __delay_ms(50);

    entorno.derecha = Ultrasonic_Read();

    Navigation_Decision();
}

void Navigation_Decision()
{
     /* Maniobra en curso */

    if(estadoNav == NAV_GIRO_IZQ)
    {
        Motor_SetSpeed(SPEED_GIRO);
        Motor_Izquierda();

        Message("GIRO IZQ", entorno.izquierda);

        tiempoEstado--;

        if(tiempoEstado == 0)
            estadoNav = NAV_ADELANTE;

        return;
    }

    if(estadoNav == NAV_GIRO_DER)
    {
        Motor_SetSpeed(SPEED_GIRO);
        Motor_Derecha();

        Message("GIRO DER", entorno.derecha);

        tiempoEstado--;

        if(tiempoEstado == 0)
            estadoNav = NAV_ADELANTE;

        return;
    }

    if(estadoNav == NAV_REVERSA)
    {
        Motor_SetSpeed(SPEED_BACK);
        Motor_Atras();

        Message("REVERSA", entorno.centro);

        tiempoEstado--;

        if(tiempoEstado == 0)
            estadoNav = NAV_ADELANTE;

        return;
    }

    /* ZONA CRÍTICA */
    if((entorno.centro < DIST_EMERGENCIA) ||
       (entorno.izquierda < DIST_EMERGENCIA) ||
       (entorno.derecha < DIST_EMERGENCIA))
    {
        estadoNav = NAV_REVERSA;
        tiempoEstado = 1;
        return;
    }

    /* OBSTÁCULO FRONTAL */
    if(entorno.centro < DIST_MIN)
    {
        if(entorno.derecha > entorno.izquierda)
        {
            estadoNav = NAV_GIRO_DER;
            tiempoEstado = 2;
        }
        else
        {
            estadoNav = NAV_GIRO_IZQ;
            tiempoEstado = 2;
        }

        return;
    }

    /* CORRECCIÓN LATERAL IZQUIERDA */
    if(entorno.izquierda < DIST_LATERAL)
    {
        Motor_SetSpeed(SPEED_GIRO);

        /* ya corregiste las llamadas invertidas */
        Motor_CorregirDerecha();

        Message("COR DER", entorno.izquierda);

        return;
    }

    /* CORRECCIÓN LATERAL DERECHA */
    if(entorno.derecha < DIST_LATERAL)
    {
        Motor_SetSpeed(SPEED_GIRO);

        /* ya corregiste las llamadas invertidas */
        Motor_CorregirIzquierda();

        Message("COR IZQ", entorno.derecha);

        return;
    }

    /* AVANCE NORMAL */
    Motor_SetSpeed(SPEED_NORMAL);
    Motor_Adelante();

    Message("ADELANTE", entorno.centro);
}

void Message(char *mensaje, unsigned int distancia)
{
    char buffer[16];

    LCD_Clear();

    LCD_SetCursor(1,1);
    LCD_Write_String(mensaje);

    sprintf(buffer, "D:%u", distancia);

    LCD_SetCursor(2,1);
    LCD_Write_String(buffer);
}

