
#define A_STEP_PIN         54
#define A_DIR_PIN          55
#define A_ENABLE_PIN       38

#define B_STEP_PIN         60
#define B_DIR_PIN          61
#define B_ENABLE_PIN       56

#define C_STEP_PIN         46
#define C_DIR_PIN          48
#define C_ENABLE_PIN       62

#define D_STEP_PIN         26
#define D_DIR_PIN          28
#define D_ENABLE_PIN       24

#define E_STEP_PIN         36
#define E_DIR_PIN          34
#define E_ENABLE_PIN       30

#define F_STEP_PIN         33
#define F_DIR_PIN          32
#define F_ENABLE_PIN       31

#define SERVO_PIN          35

#define STEPPER_ACCEL_A     4000
#define STEPPER_SPEED_A     10000
#define STEPPER_ACCEL_B     4000
#define STEPPER_SPEED_B     10000
#define STEPPER_ACCEL_C     5000
#define STEPPER_SPEED_C     15000
#define STEPPER_ACCEL_D     1500
#define STEPPER_SPEED_D     1000
#define STEPPER_ACCEL_E     5000
#define STEPPER_SPEED_E     7000
#define STEPPER_ACCEL_F     5000
#define STEPPER_SPEED_F     7000

#define MAX_A  5000
#define MIN_A  -5000
#define MAX_B  4500
#define MIN_B  -4500
#define MAX_C  10000
#define MIN_C  -10000
#define MAX_D  1000
#define MIN_D  -1000
#define MAX_E  3000
#define MIN_E  -3000
#define MAX_F  1500
#define MIN_F  -1500
#define MAX_G  168
#define MIN_G  80

long movimiento1 = 2500;
long movimiento2 = 4500;
long movimiento3 = 8000;
long movimiento4 = 500;
long movimiento5 = 1500;
long movimiento6 = 1500;
long movimiento7 = MAX_G;



#include <AccelStepper.h>
#include <Servo.h>

AccelStepper motorA(1, A_STEP_PIN, A_DIR_PIN);
AccelStepper motorB(1, B_STEP_PIN, B_DIR_PIN);
AccelStepper motorC(1, C_STEP_PIN, C_DIR_PIN);
AccelStepper motorD(1, D_STEP_PIN, D_DIR_PIN);
AccelStepper motorE(1, E_STEP_PIN, E_DIR_PIN);
AccelStepper motorF(1, F_STEP_PIN, F_DIR_PIN);

Servo pinza; 

const int consApin = A9;
const int consBpin = A10;
const int consCpin = A11;
const int consDpin = A12;
const int consEpin = A13;
const int consFpin = A14;
const int consGpin = A15;

long consignaA = 0;
long consignaB = 0;
long consignaC = 0;
long consignaD = 0;
long consignaE = 0;
long consignaF = 0;
long consignaG = 0;

void leerConsignas(){
  consignaA = map(analogRead(consApin), 0, 1023, MIN_A, MAX_A);
  consignaB = map(analogRead(consBpin), 0, 1023, MIN_B, MAX_B);
  consignaC = map(analogRead(consCpin), 0, 1023, MIN_C, MAX_C);
  consignaD = map(analogRead(consDpin), 0, 1023, MIN_D, MAX_D);
  consignaE = map(analogRead(consEpin), 0, 1023, MIN_E, MAX_E);
  consignaF = map(analogRead(consFpin), 0, 1023, MIN_F, MAX_F);
  consignaG = map(analogRead(consGpin), 0, 1023, MIN_G, MAX_G);
}

void setup() {
  motorA.setEnablePin(A_ENABLE_PIN);
  motorA.setPinsInverted(false, false, false);
  motorA.setAcceleration(STEPPER_ACCEL_A);
  motorA.setMaxSpeed(STEPPER_SPEED_A);
  motorA.enableOutputs();

  motorB.setEnablePin(B_ENABLE_PIN);
  motorB.setPinsInverted(false, false, true);
  motorB.setAcceleration(STEPPER_ACCEL_B);
  motorB.setMaxSpeed(STEPPER_SPEED_B);
  motorB.enableOutputs();

  motorC.setEnablePin(C_ENABLE_PIN);
  motorC.setPinsInverted(false, false, false);
  motorC.setAcceleration(STEPPER_ACCEL_C);
  motorC.setMaxSpeed(STEPPER_SPEED_C);
  motorC.enableOutputs();

  motorD.setEnablePin(D_ENABLE_PIN);
  motorD.setPinsInverted(false, false, false);
  motorD.setAcceleration(STEPPER_ACCEL_D);
  motorD.setMaxSpeed(STEPPER_SPEED_D);
  motorD.enableOutputs();

  motorE.setEnablePin(E_ENABLE_PIN);
  motorE.setPinsInverted(false, false, false);
  motorE.setAcceleration(STEPPER_ACCEL_E);
  motorE.setMaxSpeed(STEPPER_SPEED_E);
  motorE.enableOutputs();

  motorF.setEnablePin(F_ENABLE_PIN);
  motorF.setPinsInverted(false, false, false);
  motorF.setAcceleration(STEPPER_ACCEL_F);
  motorF.setMaxSpeed(STEPPER_SPEED_F);
  motorF.enableOutputs();

  pinza.attach(SERVO_PIN);
  pinza.write(MIN_G); 

}

long antA = 0;
long antB = 0;
long antC = 0;
long antD = 0;
long antE = 0;
long antF = 0;
long antG = 0;

void loop() {
  if(motorA.currentPosition() == 0 && motorB.currentPosition() == 0 && motorC.currentPosition() == 0 &&
    motorD.currentPosition() == 0 && motorE.currentPosition() == 0 && motorF.currentPosition() == 0) {
    delay(2000);
    pinza.write(MIN_G); 
    motorA.moveTo(movimiento1);
  }

  if(motorA.currentPosition() == movimiento1) {
    motorB.moveTo(movimiento2);
  }

  if(motorB.currentPosition() == movimiento2) {
    motorC.moveTo(movimiento3);
  }

  if(motorC.currentPosition() == movimiento3) {
    motorD.moveTo(movimiento4);
  }

  if(motorD.currentPosition() == movimiento4) {
    motorE.moveTo(movimiento5);
  }

  if(motorE.currentPosition() == movimiento5) {
    motorF.moveTo(movimiento6);
  }

  if(motorF.currentPosition() == movimiento6) {
    pinza.write(80);
    delay(1000);
    pinza.write(140);
    delay(1000);
    pinza.write(80);
    delay(1000);
    pinza.write(140);
    delay(1000);
    pinza.write(80);
    motorA.moveTo(0);
    motorB.moveTo(0);
    motorC.moveTo(0);
    motorD.moveTo(0);
    motorE.moveTo(0);
    motorF.moveTo(0);
    delay(2000);
  }


  
  motorA.run();
  motorB.run();
  motorC.run();
  motorD.run();
  motorE.run();
  motorF.run();
        
}
