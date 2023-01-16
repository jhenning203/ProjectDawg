#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

uint8_t servonum = 0;

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50
void Standup();
void setServoPulse(uint8_t n, double pulse);

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();

  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);
  delay(10);

  //reset position of servo
  int Servo0 = 430;
  int Servo1 = 425;
  pwm.setPWM(0, 0, Servo0);
  pwm.setPWM(1 ,0, Servo1);
  delay(1000);
  for(int pulslen = Servo1; pulslen>190; pulslen--){
      pwm.setPWM(1,0,pulslen);
      delay(1);
  }
  for(int pulslen = Servo0; pulslen>320;pulslen--){
    pwm.setPWM(0,0,pulslen);
    delay(1);
  }
delay (200);


  for(int pulslen = 190; pulslen < 315 ;pulslen ++){
    pwm.setPWM(1,0,pulslen);
    delay(1);
  }
  delay(1000);
  /*
  for(int pulslen = 320; pulslen< 430; pulslen ++){
    pwm.setPWM(0 ,0 ,pulslen);
    pwm.setPWM(1 , 0, (pulslen - 5));
    delay(3);
  }
 */
  /*
  Aufstehen funktioniert nicht gut 
  delay(10000);
  for (int pulselen = 0; pulselen < 95; pulselen++) {
    Servo0 = Servo0 - 1 ;
    Servo1 = Servo1 + 1 ;
    pwm.setPWM(1, 0, Servo1);
    pwm.setPWM(0,0,Servo0);
    delay(30);
 }
 */
}

void loop() {
  /*
int Servo0 = 430;
  int Servo1 = 425;
  pwm.setPWM(0, 0, Servo0);
  pwm.setPWM(1 ,0, Servo1);
  delay(1000);
  for(int pulslen = Servo1; pulslen>190; pulslen--){
      pwm.setPWM(1,0,pulslen);
      delay(1);
  }
  for(int pulslen = Servo0; pulslen>320;pulslen--){
    pwm.setPWM(0,0,pulslen);
    delay(1);
  }
delay (200);


  for(int pulslen = 190; pulslen < 315 ;pulslen ++){
    pwm.setPWM(1,0,pulslen);
    delay(1);
  }
  delay(1000);
  for(int pulslen = 320; pulslen< 430; pulslen ++){
    pwm.setPWM(0 ,0 ,pulslen);
    pwm.setPWM(1 , 0, (pulslen - 5));
    delay(3);
  }
  */



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
  //pwm.setPWM(n, 0, pulse);
}