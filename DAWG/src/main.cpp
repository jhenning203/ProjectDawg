#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "defines.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

uint8_t servonum = 0;

///////////////////////////////////////////////////////////////////////////////
//WENN IHR NUR EUREN CODE TESTEN WOLLT --> HINTER EUREM NAMEN EINE 1 PLATZIEREN
#define DAWID     01
#define VINCENT   0
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
<<<<<<< Updated upstream
=======

void loop() {

  Serial.println(servonum);
  for (int pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    pwm.setPWM(0, 0, pulselen);
    pwm.setPWM(1, 0, pulselen);
    delay(10);
  }

 
}

>>>>>>> Stashed changes
