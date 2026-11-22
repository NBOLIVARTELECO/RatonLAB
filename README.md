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
Disposición de pines
RA0 -> LED STATUS

RA1 -> LCD RS
RA2 -> LCD E
RA3 -> LCD D7

RE0 -> LCD D4
RE1 -> LCD D5
RE2 -> LCD D6


RB0 -> HC-SR04 TRIG
RB1 -> HC-SR04 ECHO
RB2 -> SERVO


RC0 -> L298 IN1
RC1 -> L298 IN2

RC2 -> PWM

RC3 -> L298 IN3
RC4 -> L298 IN4



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

# Consideraciones de Alimentación y Desacoplo

## Desacoplo del Microcontrolador

El PIC16F877A dispone de dos pares de alimentación:

VDD  (Pin 11)

VSS  (Pin 12)

VDD  (Pin 32)

VSS  (Pin 31)

Se recomienda conectar ambos pares de alimentación y colocar un condensador cerámico de desacoplo por cada par.

100 nF entre Pin 11 y Pin 12

100 nF entre Pin 32 y Pin 31

Estos condensadores deben colocarse físicamente lo más cerca posible del microcontrolador.

### Función

- Filtrado de ruido de alta frecuencia.
- Estabilidad de alimentación.
- Prevención de reinicios inesperados.
- Mejora de la inmunidad frente a ruido generado por motores y servomotores.

---

## Desacoplo de la Etapa de Potencia

El módulo L298N controla motores de corriente continua que generan variaciones importantes de corriente durante arranque, frenado y cambios de dirección.

Se recomienda instalar:

220 µF / 16 V

entre:

VMOTOR y GND

muy cerca de la entrada de alimentación del L298N.

### Función

- Absorber caídas momentáneas de tensión.
- Reducir fluctuaciones al arrancar los motores.
- Mejorar la estabilidad general del sistema.

---

## Supresión de Ruido en Motores

Los motores DC generan interferencia electromagnética debido a la conmutación mecánica de las escobillas.

Se recomienda colocar un condensador cerámico:

100 nF

directamente en paralelo con los terminales de cada motor.

Terminal A \-\-\-\-\|\|\-\-\-\- Terminal B

              100 nF

### Función

- Reducción de interferencias EMI.
- Menor ruido eléctrico sobre la alimentación.
- Menor afectación sobre el sensor ultrasónico, servomotor y LCD.

---

## Recomendación de Masa Común

Todos los subsistemas deben compartir referencia de tierra (GND).

PIC16F877A

LCD

HC\-SR04

Servomotor

L298N

Fuente de motores

deben estar unidos mediante una masa común.

La ausencia de una referencia común puede producir errores de medición, comportamiento errático de los motores o fallos de comunicación entre módulos.

---

## Configuración Utilizada en el Proyecto

PIC16F877A

??? 100 nF (VDD\-VSS lado 1)

??? 100 nF (VDD\-VSS lado 2)

L298N

??? 220 µF / 16 V

??? 100 nF cerámico

Motor izquierdo

??? 100 nF entre terminales

Motor derecho

??? 100 nF entre terminales

