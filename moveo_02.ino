/*
  Ejemplo de control del robot moveo mediante Arduino Mega y RAMPS
*/
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

#define PS_ON_PIN          12
#define KILL_PIN           -1

#define HEATER_0_PIN       10
#define HEATER_1_PIN       8
#define TEMP_0_PIN          13   // ANALOG NUMBERING
#define TEMP_1_PIN          14   // ANALOG NUMBERING

#define SERVO_1_PIN         11
#define SERVO_2_PIN         6
#define SERVO_3_PIN         5
#define SERVO_4_PIN         4

#define STEPPER_ACCEL     5000
#define STEPPER_SPEED     2000
#define STEPPER_MOVE      6400

#define DESPLAZAMIENTO_X  6400
#define DESPLAZAMIENTO_Y  6400
#define DESPLAZAMIENTO_Z  6400
#define DESPLAZAMIENTO_E  6400
#define DESPLAZAMIENTO_Q  6400
#define PINZA_CERRADA  30
#define PINZA_ABIERTA  150

#include <AccelStepper.h>
#include <Servo.h>


// Define a stepper and the pins it will use
AccelStepper motorX(1, X_STEP_PIN, X_DIR_PIN);
AccelStepper motorY(1, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper motorZ(1, Z_STEP_PIN, Z_DIR_PIN);
AccelStepper motorE(1, E_STEP_PIN, E_DIR_PIN);
AccelStepper motorQ(1, Q_STEP_PIN, Q_DIR_PIN);

Servo pinza;  // create servo object to control a servo

void setup()
{
  motorX.setEnablePin(X_ENABLE_PIN);
  motorX.setPinsInverted(false, false, true);
  motorX.setAcceleration(STEPPER_ACCEL);
  // motorX.move(STEPPER_MOVE);
  motorX.setMaxSpeed(STEPPER_SPEED);
  motorX.enableOutputs();

  motorY.setEnablePin(Y_ENABLE_PIN);
  motorY.setPinsInverted(false, false, true);
  motorY.setAcceleration(STEPPER_ACCEL);
  motorY.setMaxSpeed(STEPPER_SPEED);
  motorY.enableOutputs();

  motorZ.setEnablePin(Z_ENABLE_PIN);
  motorZ.setPinsInverted(false, false, true);
  motorZ.setAcceleration(STEPPER_ACCEL);
  motorZ.setMaxSpeed(STEPPER_SPEED);
  motorZ.enableOutputs();

  motorE.setEnablePin(E_ENABLE_PIN);
  motorE.setPinsInverted(false, false, true);
  motorE.setAcceleration(STEPPER_ACCEL);
  motorE.setMaxSpeed(STEPPER_SPEED);
  motorE.enableOutputs();

  motorQ.setEnablePin(Q_ENABLE_PIN);
  motorQ.setPinsInverted(false, false, true);
  motorQ.setAcceleration(STEPPER_ACCEL);
  motorQ.setMaxSpeed(STEPPER_SPEED);
  motorQ.enableOutputs();

  pinza.attach(SERVO_1_PIN);  // attaches the servo on pin SERVO_1_PIN to the servo object

  motorX.setCurrentPosition(0);
  motorY.setCurrentPosition(0);
  motorZ.setCurrentPosition(0);
  motorE.setCurrentPosition(0);
  motorQ.setCurrentPosition(0);
  pinza.write(PINZA_CERRADA);
}




void loop()
{
  if (motorX.currentPosition() == 0) {
    motorX.moveTo(DESPLAZAMIENTO_X);
  }
  if (motorX.currentPosition() == DESPLAZAMIENTO_X) {
    motorY.moveTo(DESPLAZAMIENTO_Y);
  }
  if (motorY.currentPosition() == DESPLAZAMIENTO_Y) {
    motorZ.moveTo(DESPLAZAMIENTO_Z);
  }
  if (motorZ.currentPosition() == DESPLAZAMIENTO_Z) {
    motorE.moveTo(DESPLAZAMIENTO_E);
  }
  if (motorE.currentPosition() == DESPLAZAMIENTO_E) {
    motorQ.moveTo(DESPLAZAMIENTO_Q);
  }
  if (motorQ.currentPosition() == DESPLAZAMIENTO_Q) {
    pinza.write(PINZA_ABIERTA);
  }
  if (pinza.read() == PINZA_ABIERTA) {
    pinza.write(PINZA_CERRADA);
  }

  motorX.run();
  motorY.run();
  motorZ.run();
  motorE.run();
  motorQ.run();
}
