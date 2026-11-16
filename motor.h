#ifndef MOTOR_H
#define MOTOR_H

void Motor_Init(void);

void Motor_SetSpeed(unsigned int duty);

void Motor_Adelante(void);
void Motor_Atras(void);

void Motor_Izquierda(void);
void Motor_Derecha(void);

void Motor_Stop(void);

#endif