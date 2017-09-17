//--------------DEFINE-------------------------------------

//#define factorX         355
//#define factorY         355
//#define factorZ         533
//#define factorE         166
//#define factorQ         80

#define factorX         32
#define factorY         32
#define factorZ         32
#define factorE         32
#define factorQ         32

// Definición de pines de la RAMPS 1.4
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN           3
#define X_MAX_PIN           2

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#define E_STEP_PIN         26
#define E_DIR_PIN          28
#define E_ENABLE_PIN       24

#define Q_STEP_PIN         36
#define Q_DIR_PIN          34
#define Q_ENABLE_PIN       30

#define SDPOWER            -1
#define SDSS               53
#define LED_PIN            13

#define FAN_PIN            9

#define HEATER_0_PIN       10
#define HEATER_1_PIN       8
#define TEMP_0_PIN          13   // ANALOG NUMBERING
#define TEMP_1_PIN          14   // ANALOG NUMBERING

#define SERVO_1_PIN         11
#define SERVO_2_PIN         6
#define SERVO_3_PIN         5
#define SERVO_4_PIN         4

#define STEPPER_ACCEL     2000
#define STEPPER_SPEED     10000
#define STEPPER_MOVE      100

#define DESPLAZAMIENTO_X  200
#define DESPLAZAMIENTO_Y  100
#define DESPLAZAMIENTO_Z  100
#define DESPLAZAMIENTO_E  100
#define DESPLAZAMIENTO_Q  100
#define PINZA_CERRADA  30
#define PINZA_ABIERTA  150

//--------------VARIABLES-------------------------------------
int etapa = 0;



