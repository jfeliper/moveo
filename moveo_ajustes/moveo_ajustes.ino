/*
  Ejemplo de control del robot moveo mediante Arduino Mega y RAMPS

  Motor X Nema17 transmisión poleas con reducción
  Driver DRV8825 en RAMPS   Uni-T 0.7A
  Desde el centro move(32000) mueve 90º hacia la derecha (Factor 355)

  Motor Y Nema23
  Driver DQ542MA Todos los switchwes en OFF Uni-T 1.7A
  Desde a vertical move(32000) mueve 90º hacia adelante (Factor 355)

  Motor Z Nema17 red 5:1 y transmisión poleas con reducción
  Driver DRV8825 en RAMPS Uni-T 0.5A
  Desde el centro move(48000) mueve 90º hacia delante (Factor 533)

  Motor E Nema17 corto
  Driver DRV8825 en RAMPS Uni-T 0.5A
  Desde el centro move(15000) mueve 90º en sentido horario (Factor 166)

  Motor Q Nema14 transmisión poleas con reducción
  Driver DRV8825 en RAMPS Uni-T 0.7A
  Desde el centro move(7200) mueve 90º hacia delante (Factor 80)

*/

#include <AccelStepper.h>
#include <Servo.h>

#include "variables.h"            /*    variables                         */

/*----------------- INSTANCIAS ----------------*/

// Define a stepper and the pins it will use
AccelStepper motorX(1, X_STEP_PIN, X_DIR_PIN);
AccelStepper motorY(1, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper motorZ(1, Z_STEP_PIN, Z_DIR_PIN);
AccelStepper motorE(1, E_STEP_PIN, E_DIR_PIN);
AccelStepper motorQ(1, Q_STEP_PIN, Q_DIR_PIN);

Servo pinza;  // create servo object to control a servo


/*----------------- ARRANQUE ------------------*/


#include "funciones.h"            /*    Funciones                         */

void setup()
{
  motorX.setEnablePin(X_ENABLE_PIN);
  motorX.setPinsInverted(false, false, true);
  motorX.setAcceleration(STEPPER_ACCEL);
  motorX.move(DESPLAZAMIENTO_X);
  motorX.setMaxSpeed(STEPPER_SPEED);
  motorX.enableOutputs();

  motorY.setEnablePin(Y_ENABLE_PIN);
//  motorY.setPinsInverted(false, false, false); //Para driver externo
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
  motorX.run();
  motorY.run();
  motorZ.run();
  motorE.run();
  motorQ.run();
  if ((etapa == 0) && (motorX.currentPosition() == 0)) {
    mueveaX(90, 45, 10);
    etapa = 1;
  }
  if ((etapa == 1) && (motorX.currentPosition() == 90 * factorX)) {
    mueveaZ(90, 45,10);
    etapa = 2;
  }
  if ((etapa == 2) && (motorZ.currentPosition() == 90 * factorZ)) {
    mueveaQ(90, 45, 10);
    pinza.write(PINZA_ABIERTA);
    etapa = 3;
  }
  if ((etapa == 3) && (motorQ.currentPosition() == 90 * factorQ)) {
    mueveaY(90, 45, 10);
    etapa = 4;
  }
  if ((etapa == 4) && (motorY.currentPosition() == 90 * factorY)) {
    pinza.write(PINZA_CERRADA);
    etapa = 5;
  }
  if ((etapa == 5) && (pinza.read() < 90)) {
    mueveaY(45, 45, 10);
    etapa = 6;
  }
  if ((etapa == 6) && (motorY.currentPosition() == 45 * factorY)) {
    mueveaZ(45, 45, 10);
    mueveaQ(45, 45, 10);
    etapa = 7;
  }
  if ((etapa == 7) && (motorQ.currentPosition() == 45 * factorQ) && (motorZ.currentPosition() == 45 * factorZ)) {
    mueveaX(45, 45, 10);
    etapa = 8;
  }
  if ((etapa == 8) && (motorX.currentPosition() == 45 * factorX)) {
    mueveaZ(90, 45, 10);
    mueveaQ(90, 45, 10);
    etapa = 9;
  }
  if ((etapa == 9) && (motorQ.currentPosition() == 90 * factorQ) && (motorZ.currentPosition() == 90 * factorZ)) {
    mueveaY(45, 45, 10);
    etapa = 10;
  }
  if ((etapa == 10) && (motorY.currentPosition() == 45 * factorY)) {
    pinza.write(PINZA_ABIERTA);
    etapa = 11;
  }
  if ((etapa == 11) && (pinza.read() > 100)) {
    mueveaY(0, 45, 10);
    mueveaZ(0, 45, 10);
    mueveaQ(0, 45, 10);
    etapa = 12;
  }
  if ((etapa == 12) && (motorY.currentPosition() == 0 * factorY) && (motorZ.currentPosition() == 0 * factorZ) && (motorQ.currentPosition() == 0 * factorQ)) {
    mueveaX(0, 45, 10);
    etapa = 13;
  }
  if ((etapa == 13) && (motorX.currentPosition() == 0 * factorX)) {
    etapa = 14;
  }
}


