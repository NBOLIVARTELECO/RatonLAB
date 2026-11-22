#ifndef NAVIGATION_H
#define NAVIGATION_H

typedef struct
{
    unsigned int izquierda;
    unsigned int centro;
    unsigned int derecha;

} Distancias;

extern Distancias entorno;

void Navigation_Init(void);

void Navigation_Update(void);

#endif