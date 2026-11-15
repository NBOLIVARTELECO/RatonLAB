# RatonLAB

Proyecto Final - Digitales II

## Descripción

RatonLAB es un robot móvil autónomo diseñado para recorrer y resolver laberintos utilizando un sensor ultrasónico montado sobre un servomotor.

El sistema realizará una exploración continua del entorno mientras se encuentra en movimiento, permitiendo detectar obstáculos y tomar decisiones de navegación en tiempo real.

---

# Objetivos

## Objetivo General

Diseñar e implementar un robot autónomo capaz de desplazarse dentro de un laberinto e identificar una trayectoria libre mediante el uso de sensores de distancia y algoritmos de navegación.

## Objetivos Específicos

- Implementar control de velocidad mediante PWM.
- Controlar la dirección de dos motores DC utilizando un puente H.
- Obtener distancias mediante un sensor HC-SR04.
- Implementar un sistema de exploración utilizando un servomotor.
- Realizar un barrido continuo de izquierda, centro y derecha.
- Tomar decisiones de navegación utilizando las mediciones obtenidas.
- Resolver recorridos tipo laberinto mediante un algoritmo reactivo.

---

# Hardware

## Microcontrolador

PIC16F877A

## Sensores

- HC-SR04

## Actuadores

- 2 Motores DC
- Servomotor SG90

## Etapa de Potencia

- L298N

## Interfaz de Usuario

- Pantalla LCD 16x2

---

# Arquitectura del Sistema

```text
                 HC-SR04
                     |
                 Servomotor
                     |
                     |
                PIC16F877A
                     |
     ---------------------------------
     |               |               |
    LCD          PWM CCP1         L298N
                                     |
                              Motor Izq
                              Motor Der
```

---

# Estrategia de Exploración

El sensor ultrasónico estará montado sobre el servomotor.

El patrón de exploración será:

```text
Centro
  ?
Izquierda
  ?
Centro
  ?
Derecha
  ?
Centro
```

Este ciclo se ejecutará continuamente para mantener actualizadas las variables de navegación.

Variables de distancia:

```c
unsigned int distIzq;
unsigned int distCentro;
unsigned int distDer;
```

---

# Estrategia de Navegación

El robot se desplazará mientras realiza mediciones periódicas del entorno.

Cuando se detecte un obstáculo frontal se evaluarán las distancias previamente almacenadas:

```text
distIzq
distCentro
distDer
```

La dirección con mayor espacio disponible será utilizada para continuar el recorrido.

---

# Arquitectura Temporal

## PWM

Generado por hardware mediante:

```text
CCP1 + Timer2
```

El microcontrolador no dedicará tiempo de procesamiento a la generación del PWM.

---

## Ultrasonido

La medición de distancia utilizará:

```text
Timer1
```

para determinar el tiempo del eco.

---

## Servomotor

El servomotor será controlado mediante una máquina de estados temporizada.

Estados previstos:

```text
CENTRO
IZQUIERDA
CENTRO
DERECHA
CENTRO
```

No se utilizarán retardos bloqueantes para el control del sistema.

---

# Asignación Preliminar de Pines

## L298N

```text
RC2 -> PWM (ENA + ENB)

RC0 -> IN1
RC1 -> IN2

RC3 -> IN3
RC4 -> IN4
```

## HC-SR04

```text
RB0 -> TRIG
RB1 -> ECHO
```

## Servomotor

```text
RB2 -> SERVO
```

## LCD 16x2

```text
RD0 -> RS
RD1 -> E

RD2 -> D4
RD3 -> D5
RD4 -> D6
RD5 -> D7
```

---

# Estructura del Firmware

```text
main.c

motor.c
motor.h

pwm.c
pwm.h

servo.c
servo.h

ultrasonic.c
ultrasonic.h

navigation.c
navigation.h

lcd.c
lcd.h
```

---

# Hoja de Ruta

## v0.1

- Estructura inicial del proyecto
- Configuración del repositorio

## v0.2

- Blink
- Verificación hardware

## v0.3

- PWM CCP1

## v0.4

- Control L298N

## v0.5

- Lectura HC-SR04

## v0.6

- Movimiento de servomotor

## v0.7

- Barrido continuo

## v0.8

- Navegación básica

## v1.0

- Resolución de laberintos

---

# Estado Actual

```text
[?] Planeación general
[?] Arquitectura de hardware
[?] Arquitectura temporal
[?] Repositorio GitHub
[ ] PWM
[ ] L298N
[ ] HC-SR04
[ ] Servomotor
[ ] Navegación
[ ] Resolución de laberintos
```