#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "defines.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

uint8_t servonum = 0;

///////////////////////////////////////////////////////////////////////////////
//WENN IHR NUR EUREN CODE TESTEN WOLLT --> HINTER EUREM NAMEN EINE 1 PLATZIEREN
#define DAWID     0
#define VINCENT   1
#define JANNIS    0
////////////////////////////////////////////////////////////////////////////////

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50
#define AusgestrecktS1 190
#define AusgestrecktS2 310
#define TiefS1 330
#define Tiefs2 495
#define VorneS1 315
#define Vorne 320

void MenuSetup();
void showServoValuesToConcole();
void setServoPositionFromConsole(int servonum);
void setLegPositionFromConsole(int servonum);
void setLegPosition(int leg, int servo0, int servo1, int servo2);

void walkforeward();
void takeastep (int leg);
void sitdown();
void standup();
void punch();
void standardpos();

void setup() {
  ////////////////////////////////////////////////////
  //DO NOT CHANGE
  //init of Serial connection with according baudrate
  Serial.begin(9600);
  //Adafruit PWM lib init
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  //set PWM to 50 Hz
  pwm.setPWMFreq(SERVO_FREQ);
  //DO NOT CHANGE
  ///////////////////////////////////////////

  #if DAWID
    setLegPosition(1,ServoPosArray[0][0],ServoPosArray[0][1],ServoPosArray[0][2]);
    MenuSetup();
  #endif

  #if JANNIS

  #endif

  #if VINCENT
  

  #endif
  delay(10);
}

void loop() {

  
  //@JANNIS DEIN CODE HIER REIN
  #if JANNIS 
  walkforeward();
  #endif
  //JANNIS CODE ENDE
  /////////////////////////////
  //@VINCENT DEIN CODE HIER REIN
  #if VINCENT 
  //pwm.setPWM(0,0,500);
  #endif
  //VINCENT CODE ENDE
  /////////////////////////////
  //DAWID CODE
  #if DAWID 
    setLegPositionFromConsole(0);
  #endif
  //DAWID CODE ENDE
  ////////////////////////////
}
/////////////////////////////////////////////////////////
// Function for Leg calibration
void standardpos(int leg){
  int servobyleg = 0;
  switch (leg)
  {
  case 1: break;
  case 2: servobyleg += 4; break;
  case 3: servobyleg += 8; break;
  case 4: servobyleg += 12;break;
  default:
    break;
  }
  pwm.setPWM(0,0,425);
  pwm.setPWM(1,0,425);
  pwm.setPWM(2,0,300);
}

/////////////////////////////////////////////////////////////////
//Functions written by Dawid Wilczewski START

void showServoValuesToConcole(){
  //aktuelle Servowerte des Arrays im Serial monitor anzeigen
  Serial.println("Aktuelle Werte Servos:");
  for(int y = 0; y < 4; y++){
    //Serial.println((String)"\t" + 0 + (String)"\t" + 1 + (String)"\t" + 2);
    for(int i = 0; i < 3; i++){      
      Serial.print((String)"\t" + ServoPosArray[y][i]);
    }
    Serial.println("");
  }
}

void confirmPos(){
  int servoNumCounter = 0;
  for(int i = 0; i < 4; i++){
    for(int y = 0; y < 3; y++){
      pwm.setPWM(servoNumCounter,0,ServoPosArray[i][y]);
      servoNumCounter++;
    }
  }
}

void setServoPositionFromConsole(int servonum){

  //trash wird genutzt, um Müll im Rx Serial Buffer abzufangen
  int trash = Serial.read();
  //Schleife wird durchlaufen, bis Daten im Serial Rx Buffer ankommen
  while(Serial.available() == 0){
    ServoPosArray[0][servonum] = Serial.parseInt();
  }
  trash = Serial.read();
  //Neuen Wert im Serial monitor anzeigen
  Serial.println((String)"Eingabe für Servo " + servonum + (String)" übernommen, neuer Wert: " + ServoPosArray[0][servonum]);
}

//anstatt servonum muss als parameter noch der fuß übernommen werden
void setLegPositionFromConsole(int servonum){

  showServoValuesToConcole();
  
  Serial.println("Eingabe Neuer Wert für Servo 0(Oberschenkel): ");   setServoPositionFromConsole(0);
  Serial.println("Eingabe Neuer Wert für Servo 1(Steuerarm): ");      setServoPositionFromConsole(1);
  //Serial.println("Eingabe Neuer Wert für Servo 2(Hüftdrehung): ");    setServoPositionFromConsole(2);

  Serial.println("Aktuelle Werte Servos:");
  Serial.println("\t1\t2\t3");
  Serial.println((String)"\t" + ServoPosArray[0][0] + (String)"\t" + ServoPosArray[0][1] + (String)"\t" + ServoPosArray[0][2]);

  Serial.println("Neue Werte jetzt übernehmen? 1 für JA / RESET Für Wiederholte Eingabe der Werte");
  while(Serial.available() == 0){
    if (Serial.parseInt() == 1)
    {
      confirmPos();
      Serial.println("Neue Werte von Servos übernommen");
    }  
  }
}

void MenuSetup(){
  Serial.println("Menü zur Kontrolle von DAWG");
  setLegPositionFromConsole(0);
}

//Funktion zum ändern aller Werte am Servo eines Beins
void setLegPosition(int leg, int servo0, int servo1, int servo2){

  //leg = 1   links vorn
  //leg = 2   rechts vorn
  //leg = 3   links hinten
  //leg = 4   rechts hinten

  int servobyleg = 0;

  //Wahl des entsprechenden Fußes
  switch (leg)
  {
  case 1: break;
  case 2: servobyleg += 4; break;
  case 3: servobyleg += 8; break;
  case 4: servobyleg += 12;break;
  default:
    break;
  }

  //3. servo noch nicht drin, zunächst nicht wichtig
  pwm.setPWM(servobyleg,0,servo0);
  pwm.setPWM(servobyleg+1,0,servo1);
}

//Funtions written by Dawid END
////////////////////////////////////////////////////////////////

void walkforeward() {
  
    pwm.setPWM(0, 0, 390);
    pwm.setPWM(1, 0, 420);
    delay(1000);

    pwm.setPWM(0, 0, 310);
    pwm.setPWM(1, 0, 379);

    delay(1000);
}

//one step sequence needs optimisation
void takeastep(int leg){
  //leg = 1   links vorn
  //leg = 2   rechts vorn
  //leg = 3   links hinten
  //leg = 4   rechts hinten

  // Servobyleg + 0 = unterer Servo 
  // Servobyleg + 1 = oberer Servo 
  // Servobyleg + 2 = Bein rotation 

  int servobyleg = 0;

  //Wahl des entsprechenden Fußes
  switch (leg)
  {
  case 1: break;
  case 2: servobyleg += 4; break;
  case 3: servobyleg += 8; break;
  case 4: servobyleg += 12;break;
  default:
    break;
  }
  int Servo0 = 430;
  int Servo1 = 425;
  pwm.setPWM(servobyleg, 0, Servo0);
  pwm.setPWM(servobyleg + 1, 0, Servo1);
  delay(1000);
  for(int pulslen = Servo1; pulslen > 190; pulslen -- ){
      pwm.setPWM(servobyleg + 1, 0, pulslen);
      delay(1);
  }
  for(int pulslen = Servo0; pulslen > 320; pulslen -- ){
    pwm.setPWM(servobyleg, 0, pulslen);
    delay(1);
  }
delay (100);


  for(int pulslen = 190; pulslen < 315 ;pulslen ++ ){
    pwm.setPWM(servobyleg + 1, 0, pulslen);
    delay(1);
  }
  delay(1000);
  for(int pulslen = 320; pulslen < 430; pulslen ++ ){
    pwm.setPWM(servobyleg, 0, pulslen);
    pwm.setPWM(servobyleg + 1, 0, (pulslen - 5));
    delay(3);
  }
}

//Sitting down from default standing position 
//For all 4 legs
void sitdown(){
int Servo0 = 430;
  int Servo1 = 425;
  for(int pulslen = Servo0; pulslen < 480; pulslen ++ ){
    pwm.setPWM(0, 0, pulslen);
    pwm.setPWM(4, 0, pulslen);
    pwm.setPWM(8, 0, pulslen);
    pwm.setPWM(12, 0, pulslen);
    delay(2);
  }
  for(int pulslen = Servo1; pulslen > 330; pulslen -- ){
    pwm.setPWM(1, 0, pulslen);
    pwm.setPWM(5, 0, pulslen);
    pwm.setPWM(9, 0, pulslen);
    pwm.setPWM(13, 0, pulslen);
    delay(2);
  }
  for(int pulslen = 480; pulslen < 495; pulslen ++ ){
    pwm.setPWM(0, 0, pulslen);
    pwm.setPWM(4, 0, pulslen);
    pwm.setPWM(8, 0, pulslen);
    pwm.setPWM(12, 0, pulslen);
    delay(2);
  }
}

//Standup sequence only if DAWG is all the way down 
void standup(){
  int Servo0 = 495;
  int Servo1 = 330;
  pwm.setPWM(0, 0, Servo0);
  pwm.setPWM(1, 0, Servo1);
  pwm.setPWM(2, 0, Servo0);
  pwm.setPWM(4, 0, Servo0);
  pwm.setPWM(6, 0, Servo0);
  pwm.setPWM(9, 0, Servo0);
  pwm.setPWM(10, 0, Servo0);
  pwm.setPWM(12, 0, Servo0);
  pwm.setPWM(13, 0, Servo0);
  for( int pulslen = Servo1; pulslen < 425; pulslen ++ ){
    pwm.setPWM(1, 0, pulslen);
    delay(4);
  }
  for(int pulslen = Servo0; pulslen > 430; pulslen -- ){
    pwm.setPWM(0, 0, pulslen);
    delay(4);
  }
}

// Punch left front 
void punch(){
  //check if in default position and goto default 
  int Servo0 = 430;
  int Servo1 = 425;
  pwm.setPWM(0, 0, Servo0);
  pwm.setPWM(1, 0, Servo1);
  delay(50);
  pwm.setPWM(2, 0, 265);
  delay(1000);
  //rotate hip
  pwm.setPWM(2, 0, 150);
  delay(1000);
  //similar to taking a step but without delay 
  for(int pulslen = Servo1; pulslen > 190; pulslen  -- ){
      pwm.setPWM(1, 0, pulslen);
  }
  for(int pulslen = Servo0; pulslen > 320; pulslen -- ){
    pwm.setPWM(0, 0, pulslen);
  }
   for(int pulslen = 190; pulslen < Servo1; pulslen ++ ){
      pwm.setPWM(1, 0, pulslen);
  }
  for(int pulslen = 320; pulslen < Servo0; pulslen ++ ){
    pwm.setPWM(0, 0, pulslen);
  }
  delay(1000);
  //rotating hip back into normal position 
  pwm.setPWM(2, 0, 300);
}


///////////////////////////////////////////
//UNUSED SAVED FOR LATER

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
