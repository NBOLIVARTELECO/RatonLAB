#include <xc.h>
#include "motor.h"
#include "ultrasonic.h"
#include "servo.h"
#include "navigation.h"
#include "lcd.h"


// CONFIG

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define _XTAL_FREQ 20000000

void LED_Boot(void);
void testUltrasonido(void);
void testMotores(void);
void Navigation_Update(void);
void Navigation_Init(void);

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
    
    estadoActual = ESTADO_STOP;
    unsigned int contador = 0;
    while(1)
    {
       
        Navigation_Scan();
       // testMotores();

//        LCD_Clear();
//        LCD_SetCursor(1,1);
//        LCD_Write_String("Hola");

        __delay_ms(500);
  
    }
}

void Sistema_Init(void)
{
    ADCON1 = 0x07; //salidas lcd digitales
    TRISAbits.TRISA0 = 0;
    RA0 = 0;

    LED_Boot();
    Motor_Init();
    Ultrasonic_Init();
    Servo_Init();
    Navigation_Init();
    LCD_Init();
}
void LED_Boot(void)
{
    unsigned char i;

    for(i = 0; i < 10; i++)
    {
        RA0 = 1;
        __delay_ms(200);

        RA0 = 0;
        __delay_ms(200);
    }
}
//void testMotores(void)
//{
//    Motor_SetSpeed(500);
//
//    // Adelante
//    Motor_Adelante();
//    __delay_ms(3000);
//
//    Motor_Stop();
//    __delay_ms(1000);
//
//    // Atrás
//    Motor_Atras();
//    __delay_ms(3000);
//
//    Motor_Stop();
//    __delay_ms(1000);
//
//    // Giro izquierda
//    Motor_Izquierda();
//    __delay_ms(3000);
//
//    Motor_Stop();
//    __delay_ms(1000);
//
//    // Giro derecha
//    Motor_Derecha();
//    __delay_ms(3000);
//
//    Motor_Stop();
//    __delay_ms(1000);
//
//    // Corrección izquierda
//    Motor_CorregirIzquierda();
//    __delay_ms(3000);
//
//    Motor_Stop();
//    __delay_ms(1000);
//
//    // Corrección derecha
//    Motor_CorregirDerecha();
//    __delay_ms(3000);
//
//    Motor_Stop();
//    __delay_ms(1000);
//}



