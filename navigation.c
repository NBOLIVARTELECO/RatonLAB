#include "navigation.h"
#include "ultrasonic.h"
#include "servo.h"
#include "motor.h"
#include <xc.h>

#define _XTAL_FREQ 20000000

#define DIST_MIN       15
#define MARGEN_GIRO    5

Distancias entorno;

void Navigation_Init(void)
{
    entorno.izquierda = 15;
    entorno.centro = 15;
    entorno.derecha = 15;
}
void Navigation_Update(void)
{
    Servo_Centro();
    entorno.centro = Ultrasonic_Read();

    Servo_Izquierda();
    entorno.izquierda = Ultrasonic_Read();

    Servo_Derecha();
    entorno.derecha = Ultrasonic_Read();

    // Todo bloqueado
    if((entorno.izquierda < DIST_MIN) &&
       (entorno.centro    < DIST_MIN) &&
       (entorno.derecha   < DIST_MIN))
    {
        Motor_SetSpeed(400);
        Motor_Atras();
        return;
    }

    // Obstáculo frontal
    if(entorno.centro < DIST_MIN)
    {
        if(entorno.derecha > entorno.izquierda)
        {
            Motor_SetSpeed(350);
            Motor_Derecha();
        }
        else
        {
            Motor_SetSpeed(350);
            Motor_Izquierda();
        }

        return;
    }

    // Búsqueda de espacio
    if(entorno.izquierda > (entorno.derecha + MARGEN_GIRO))
    {
        Motor_SetSpeed(350);
        Motor_Izquierda();
    }
    else if(entorno.derecha > (entorno.izquierda + MARGEN_GIRO))
    {
        Motor_SetSpeed(350);
        Motor_Derecha();
    }
    else
    {
        Motor_SetSpeed(400);
        Motor_Adelante();
    }
}

