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
void takeastep();
void sitdown();
void standup();
void punch();


void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();

  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);
  delay(10);

  //reset position of servo
 sitdown();
 delay(3000);
 standup();
 delay(2000);

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

void loop() {
//takeastep();
for(int i = 0; i<5;i++){
  takeastep();
}
delay(1000);
punch();
delay(2000);
sitdown();


}
void takeastep(){
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
}

void sitdown(){
int Servo0 = 430;
  int Servo1 = 425;
  for(int pulslen = Servo0; pulslen <480; pulslen ++ ){
    pwm.setPWM(0,0,pulslen);
    delay(2);
  }
  for(int pulslen = Servo1; pulslen>330; pulslen -- ){
    pwm.setPWM(1, 0, pulslen);
    delay(2);
  }
  for(int pulslen = 480; pulslen <495; pulslen ++ ){
    pwm.setPWM(0, 0, pulslen);
    delay(2);
  }
}

void standup(){
  int Servo0 = 495;
  int Servo1 = 330;
  pwm.setPWM(0,0,Servo0);
  pwm.setPWM(1,0,Servo1);
  for( int pulslen = Servo1; pulslen <425; pulslen ++){
    pwm.setPWM(1,0,pulslen);
    delay(2);
  }
  for(int pulslen = Servo0;pulslen > 430; pulslen --){
    pwm.setPWM(0,0,pulslen);
    delay(2);
  }
}

void punch(){
  int Servo0 = 430;
  int Servo1 = 425;
  pwm.setPWM(0, 0, Servo0);
  pwm.setPWM(1 ,0, Servo1);
  delay(50);
  pwm.setPWM(2,0,265);
  delay(1000);
  pwm.setPWM(2,0,150);
  
  delay(1000);
  for(int pulslen = Servo1; pulslen>190; pulslen--){
      pwm.setPWM(1,0,pulslen);
  }
  for(int pulslen = Servo0; pulslen>320;pulslen--){
    pwm.setPWM(0,0,pulslen);
  }
   for(int pulslen = 190; pulslen < Servo1; pulslen++){
      pwm.setPWM(1,0,pulslen);
  }
  for(int pulslen = 320; pulslen<Servo0 ;pulslen++){
    pwm.setPWM(0,0,pulslen);
  }
  delay(1000);
  pwm.setPWM(2,0,265);
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