#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "defines.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

uint8_t servonum = 0;

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50

void setPositionFromConsole(int servonum);
void MenuSetup();

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();

  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);
  delay(10);

}

void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= SERVO_FREQ;   // Analog servos run at ~60 Hz updates
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert input seconds to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void loop() {

  Serial.println(servonum);
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    pwm.setPWM(servonum, 0, pulselen);
  }

  delay(500);
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    pwm.setPWM(servonum, 0, pulselen);
  }
}

void setPositionFromConsole(int servonum){

}

void confirmPos(){
  for(int i = 0; i < 4; i++){
    for(int y = 0; y < 3; y++){
      pwm.setPWM()
    }
  }
}

void MenuSetup(){
  Serial.println("Menü zur Kontrolle von DAWG");
  Serial.println("Aktuelle Werte Servos:");
  //Werte müssen noch ergänzt werden
  Serial.println("\t1\t2\t3");
  Serial.print("Neuer Wert Servo 1: ");setPositionFromConsole(0);
  Serial.println("");

  Serial.print("Neuer Wert Servo 2: ");setPositionFromConsole(1);
  Serial.println("");

}