#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "defines.h"
//#include "legIK.h"
#include "gait.h"
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int returnArray[3] = {0, 0, 0};
uint8_t servonum = 0;

///////////////////////////////////////////////////////////////////////////////
//WENN IHR NUR EUREN CODE TESTEN WOLLT --> HINTER EUREM NAMEN EINE 1 PLATZIEREN
#define DAWID     0
#define VINCENT   01
#define JANNIS    0
////////////////////////////////////////////////////////////////////////////////

#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50
#define AusgestrecktS1 190
#define AusgestrecktS2 310
#define TiefS1 330
#define Tiefs2 495
#define VorneS1 315
#define Vorne 320

#define S0_L_UNTEN        495
#define S1_L_UNTEN        330

//#define S0_R_UNTEN        
#define S2_MITTELSTELLUNG 290


//////////////////////////////////
//DELETE WHEN DIVIDED INTO MORE FILES
#define OFF_0               12
#define OFF_1               27
#define SHOULDER_LEGTH      107
#define WRIST_LENGTH        105
#define DS                  35
#define DX                  25
int retArray[3] = {0};
int wArray[3] = {0};
//////////////////////////////////////

void MenuSetup();
void showServoValuesToConcole();
void setServoPositionFromConsole(int servonum);
void setLegPositionFromConsole(int servonum);
void setLegPosition(int leg, int servo0, int servo1, int servo2);
int bezierCurveN3(int coordinate, int t);
void standupDaw();
void getLegAngles(int x, int y, int z);
void transformLegAnglesToServoVals(int wH, int wOS, int wSA);
void transformLegAnglesToSVSingle(int leg, int wH, int wOS, int wSA);
void angleTest();
void walkingGaitLF();

void walkforeward();
void takeastep (int leg);
void sitdown();
void standup();
void punch();
void standardpos(int leg);
void walkingexperiment();
void step();
void stepexperiment();

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

    //angleTest();
    //walkingGaitLF();

    setLegPosition(1, 270, 300, 300);

    /*
    setLegPosition(1,ServoPosArray[0][0],ServoPosArray[0][1],ServoPosArray[0][2]);
    setLegPosition(2,ServoPosArray[1][0],ServoPosArray[1][1],ServoPosArray[1][2]);
    setLegPosition(3,ServoPosArray[2][0],ServoPosArray[2][1],ServoPosArray[2][2]);
    setLegPosition(4,ServoPosArray[3][0],ServoPosArray[3][1],ServoPosArray[3][2]);
    delay(2000);
    
    for(int i = 0; i <= 50; i++){

      getLegAngles(i, 0, 150);

      Serial.print("Winkel Schulter:\t"); Serial.println((wArray[1]));
      Serial.print("Winkel Steuerarm:\t"); Serial.println((wArray[2]));
      Serial.print("Winkel H??fte:\t"); Serial.println((wArray[0]));

      int winkel[3]= {wArray[0], wArray[1], wArray[2]};
      //int servoWerte[3] = {0};
      transformLegAnglesToServoVals(winkel[0], winkel[1], winkel[2]);
      //transformLegAnglesToServoVals(0, 30, 15);

      Serial.print("Servowert Schulter:\t"); Serial.println(retArray[0]);
      Serial.print("Servowert Steuerarm:\t"); Serial.println(retArray[1]);
      Serial.print("Servowert H??fte:\t"); Serial.println(retArray[2]);

    }
    
    getLegAngles(25, 30, 150);

      Serial.print("Winkel Schulter:\t"); Serial.println((wArray[1]));
      Serial.print("Winkel Steuerarm:\t"); Serial.println((wArray[2]));
      Serial.print("Winkel H??fte:\t"); Serial.println((wArray[0]));

      int winkel[3]= {wArray[0], wArray[1], wArray[2]};
      //int servoWerte[3] = {0};
      transformLegAnglesToServoVals(winkel[0], winkel[1], winkel[2]);
      //transformLegAnglesToServoVals(0, 30, 15);

      Serial.print("Servowert Schulter:\t"); Serial.println(retArray[0]);
      Serial.print("Servowert Steuerarm:\t"); Serial.println(retArray[1]);
      Serial.print("Servowert H??fte:\t"); Serial.println(retArray[2]);
    */

    

    MenuSetup();
    //pwm.setPWM(0, 0, 425);
    //pwm.setPWM(1,0,425);
    //pwm.setPWM(2,0,290);
  #endif

  #if JANNIS

  #endif

  #if VINCENT

  /*
  
    setLegPosition(1,ServoPosArrayStandardVincent[0][0],ServoPosArrayStandardVincent[0][1],ServoPosArrayStandardVincent[0][2]);
    setLegPosition(2,ServoPosArrayStandardVincent[1][0],ServoPosArrayStandardVincent[1][1],ServoPosArrayStandardVincent[1][2]);
    setLegPosition(3,ServoPosArrayStandardVincent[2][0],ServoPosArrayStandardVincent[2][1],ServoPosArrayStandardVincent[2][2]);
    setLegPosition(4,ServoPosArrayStandardVincent[3][0],ServoPosArrayStandardVincent[3][1],ServoPosArrayStandardVincent[3][2]);
    
  
    setLegPosition(1,ServoPosArrayback[0][0],ServoPosArrayback[0][1],ServoPosArrayback[0][2]);
    setLegPosition(2,ServoPosArrayback[1][0],ServoPosArrayback[1][1],ServoPosArrayback[1][2]);
    setLegPosition(3,ServoPosArrayback[2][0],ServoPosArrayback[2][1],ServoPosArrayback[2][2]);
    setLegPosition(4,ServoPosArrayback[3][0],ServoPosArrayback[3][1],ServoPosArrayback[3][2]);
    */
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
//stepexperiment();
//delay(1000);

  /*
 step();
 delay(1);
    setLegPosition(1,ServoPosArray[0][0],ServoPosArray[0][1],ServoPosArray[0][2]);
    setLegPosition(2,ServoPosArray[1][0],ServoPosArray[1][1],ServoPosArray[1][2]);
    setLegPosition(3,ServoPosArray[2][0],ServoPosArray[2][1],ServoPosArray[2][2]);
    setLegPosition(4,ServoPosArray[3][0],ServoPosArray[3][1],ServoPosArray[3][2]);
delay(1);
 */
//step();
//delay(1000);
  
  #endif
  //VINCENT CODE ENDE
  /////////////////////////////
  //DAWID CODE
  #if DAWID 
    setLegPositionFromConsole(0);
    //angleTest();
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
  if(leg == 1){
    pwm.setPWM(servobyleg, 0, 425);
    pwm.setPWM(servobyleg + 1,0,425);
    pwm.setPWM(servobyleg + 2,0,290);
  }
  if(leg == 3){
    pwm.setPWM(servobyleg, 0, 415);
    pwm.setPWM(servobyleg + 1,0,425);
    pwm.setPWM(servobyleg + 2,0,300);
  }
  if(leg == 2){
    pwm.setPWM(servobyleg, 0, 255);
    pwm.setPWM(servobyleg + 1,0,225);
    pwm.setPWM(servobyleg + 2,0,315);
  }
  if(leg == 4){
    pwm.setPWM(servobyleg, 0, 225);
    pwm.setPWM(servobyleg + 1,0,225);
    pwm.setPWM(servobyleg + 2,0,300);
  }
  
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
      //??bertragen der Werte aus dem ServPosArray auf den PCA
      pwm.setPWM(servoNumCounter,0,ServoPosArray[i][y]);
      //laufvariable, die den aktuellen Port auf dem PCA9685 vorgibt
      servoNumCounter++;
      //??berspringt nicht genutzte Pins auf PCA9685
      if(servoNumCounter == 3){servoNumCounter = 4;}
      if(servoNumCounter == 7){servoNumCounter = 8;}
      if(servoNumCounter == 11){servoNumCounter = 12;}
    }
  }
}

void setServoPositionFromConsole(int servonum){

  //trash wird genutzt, um M??ll im Rx Serial Buffer abzufangen
  int trash = Serial.read();
  //Schleife wird durchlaufen, bis Daten im Serial Rx Buffer ankommen
  while(Serial.available() == 0){
    ServoPosArray[0][servonum] = Serial.parseInt();
  }
  trash = Serial.read();
  //Neuen Wert im Serial monitor anzeigen
  Serial.println((String)"Eingabe f??r Servo " + servonum + (String)" ??bernommen, neuer Wert: " + ServoPosArray[0][servonum]);
}

//anstatt servonum muss als parameter noch der fu?? ??bernommen werden
void setLegPositionFromConsole(int servonum){

  showServoValuesToConcole();
  
  Serial.println("Eingabe Neuer Wert f??r Servo 0(Oberschenkel): ");   setServoPositionFromConsole(0);
  Serial.println("Eingabe Neuer Wert f??r Servo 1(Steuerarm): ");      setServoPositionFromConsole(1);
  //Serial.println("Eingabe Neuer Wert f??r Servo 2(H??ftdrehung): ");    setServoPositionFromConsole(2);

  Serial.println("Aktuelle Werte Servos:");
  Serial.println("\t1\t2\t3");
  Serial.println((String)"\t" + ServoPosArray[0][0] + (String)"\t" + ServoPosArray[0][1] + (String)"\t" + ServoPosArray[0][2]);

  Serial.println("Neue Werte jetzt ??bernehmen? 1 f??r JA / RESET F??r Wiederholte Eingabe der Werte");
  while(Serial.available() == 0){
    if (Serial.parseInt() == 1)
    {
      confirmPos();
      Serial.println("Neue Werte von Servos ??bernommen");
    }  
  }
}

void MenuSetup(){
  Serial.println("Men?? zur Kontrolle von DAWG");
  setLegPositionFromConsole(0);
}

//Funktion zum ??ndern aller Werte am Servo eines Beins
void setLegPosition(int leg, int servo0, int servo1, int servo2){

  //leg = 1   links vorn
  //leg = 2   rechts vorn
  //leg = 3   links hinten
  //leg = 4   rechts hinten

  int servobyleg = 0;

  //Wahl des entsprechenden Fu??es
  switch (leg)
  {
  case 1: break;
  case 2: servobyleg += 4; break;
  case 3: servobyleg += 8; break;
  case 4: servobyleg += 12;break;
  default:
    break;
  }

  pwm.setPWM(servobyleg,0,servo0);
  delay(1);
  pwm.setPWM(servobyleg+1,0,servo1);
  delay(1);
  pwm.setPWM(servobyleg+2,0,servo2);
}

//time ??? {0;1}
//coordinate: 0 = x; 1 = y
int bezierCurveN3(int coordinate, int t){
    //%C(t) = (1-t)^3 * p0 + 3 * t * (1-t)^2 * p1 + 3 * t^2 * (1-t) * p2 + t^3 * p3;
    //P1 (-20|0) in Millimetern
    //P2 (-20|40)
    //P3 (20|40)
    //P4 (20|0)
    int returnValue = 0;
    if(coordinate == 0){
        returnValue = ((1-t)^3 * p1[0]) + (3 * t * (1-t)^2 * p2[0]) + (3 * t^2 * (1-t) * p3[0]) + (t^3 * p4[0]);
        return returnValue;
    }
    else{
        returnValue = ((1-t)^3 * p1[1]) + (3 * t * ((1-t)^2) * p2[1]) + (3 * t^2 * (1-t) * p3[1]) + ((t^3) * p4[1]);
        return returnValue;
    }
}

void standupDaw(){
  int Servoleft0 = 495;
  int Servoleft1 = 330;
  int Servoright0 = 155;
  int Servoright1 = 320;


  // setting all servos into down position 
  // maybe include setting 3 servo for hip rotation into default position
  pwm.setPWM(0, 0, Servoleft0);
  pwm.setPWM(1, 0, Servoleft1);

  pwm.setPWM(4, 0, Servoright0);
  pwm.setPWM(5, 0, Servoright1);

  pwm.setPWM(8, 0, Servoleft0);
  pwm.setPWM(9, 0, Servoleft1);

  pwm.setPWM(12, 0, Servoright0);
  pwm.setPWM(13, 0, Servoright1);

  // setting all legs into standing position 
  int pulslenright = Servoright1;
  for( int pulslen = Servoleft1; pulslen < 425; pulslen ++ ){
    //VL 
    pwm.setPWM(1, 0, pulslen);
    //VR
    pwm.setPWM(5, 0, pulslenright);
    //HL
    pwm.setPWM(9, 0, pulslen);
    //HR
    pwm.setPWM(13, 0, pulslenright);
    pulslenright = pulslenright - 1;
    //delay(4);
  }
  pulslenright = Servoright0;
  for(int pulslen = Servoleft0; pulslen > 425; pulslen -- ){
    pwm.setPWM(0, 0, pulslen);
    pwm.setPWM(8, 0, pulslen);
    pwm.setPWM(4, 0, pulslenright);
    pwm.setPWM(12, 0, pulslenright);
    pulslenright = pulslenright + 1;
    //delay(4);
  }
}

void transformLegAnglesToServoVals(int wH, int wOS, int wSA){
    int servoStepsperDgr = 450/200;
    //SERVOGRENZEN M??SSEN NOCH ERMITTELT WERDEN

    //Diese Werte gelten nur f??r LINKS VORN
    int pwm_servo2 = wH * servoStepsperDgr + 290;
    int pwm_servo0 = wOS * servoStepsperDgr + 360;
    int pwm_servo1 = 300 - wSA * servoStepsperDgr;

    //int returnArray[3] = {pwm_servo0, pwm_servo1, pwm_servo2};
    //return returnArray;
    //static int retArray[3] = {0};
    retArray[0] = pwm_servo0;
    retArray[1] = pwm_servo1;
    retArray[2] = pwm_servo2;

    //Bein 1
    ServoPosArray[0][0] = wOS * servoStepsperDgr + 360;
    ServoPosArray[0][1] = 300 - wSA * servoStepsperDgr;
    //ServoPosArray[0][2] = wH * servoStepsperDgr + 290;

    //Bein 2
    ServoPosArray[1][0] = 300 - servoStepsperDgr * wOS;
    ServoPosArray[1][1] = servoStepsperDgr * wSA + 350;

    //Bein 3
    ServoPosArray[2][0] = wOS * servoStepsperDgr + 350;
    ServoPosArray[2][1] = 300 - wSA * servoStepsperDgr;
    //ServoPosArray[2][2] = 300 - wH * servoStepsperDgr;

    //Bein 4 
    ServoPosArray[3][0] = 300 - servoStepsperDgr * wOS;
    ServoPosArray[3][1] = servoStepsperDgr * wSA + 340;

    /*
    ServoPosArray[0][0] = retArray[0];
    ServoPosArray[0][1] = retArray[1];
    ServoPosArray[0][2] = retArray[2];
    */
}

void transformLegAnglesToSVSingle(int leg, int wH, int wOS, int wSA){
  int servoStepsperDgr = 450/200;
  if(leg == 1){
    //Bein 1
    ServoPosArray[0][0] = wOS * servoStepsperDgr + 360;
    ServoPosArray[0][1] = 300 - wSA * servoStepsperDgr;
    //ServoPosArray[0][2] = wH * servoStepsperDgr + 290;
  }

  else if(leg == 2){
    //Bein 2
    ServoPosArray[1][0] = 300 - servoStepsperDgr * wOS;
    ServoPosArray[1][1] = servoStepsperDgr * wSA + 350;
  }

  else if (leg == 3){
    //Bein 3
    ServoPosArray[2][0] = wOS * servoStepsperDgr + 350;
    ServoPosArray[2][1] = 300 - wSA * servoStepsperDgr;
    //ServoPosArray[2][2] = 300 - wH * servoStepsperDgr;
  }

  else if(leg == 4){
    //Bein 4 
    ServoPosArray[3][0] = 300 - servoStepsperDgr * wOS;
    ServoPosArray[3][1] = servoStepsperDgr * wSA + 340;
  }
}

//legC[0]:  x;  theta_h Rotation H??fte
//legC[1]:  y;  theta_s rotation oberschenkel
//legC[2]:  z;  theta_w Rotation Unterschenkel
void getLegAngles(int x, int y, int z){
    //f??r berechnung siehe
    //https://www.adhamelarabawy.com/pdf/IK_Model.pdf

    float s = SHOULDER_LEGTH;
    float w = WRIST_LENGTH;
    float dx = DX;
    float ds = DS;
    float off0 = OFF_0;
    float off1 = OFF_1;

    //berechnung f??r y-z ebene
    //float h1 = sqrt((OFF_0^2) + (OFF_1^2));
    float h1 = sqrt(sq(off0) + sq(off1));
      #if DEBUGACTIVE
        Serial.print("h1:\t"); Serial.println(h1);
      #endif

    float h2 = sqrt(sq(z) + sq(y));
      #if DEBUGACTIVE
        Serial.print("h2:\t"); Serial.println(h2);
      #endif
    //float a0 = atan(abs(y)/z);
    float a0 = atan(y/z);
    #if DEBUGACTIVE
      Serial.print("a0:\t"); Serial.println(degrees(a0));
    #endif

    float a1 = atan(off1/off0);
      #if DEBUGACTIVE
        Serial.print("a1:\t"); Serial.println(degrees(a1));
      #endif

    float a2 = atan(off0/off1);
      #if DEBUGACTIVE
        Serial.print("a2:\t"); Serial.println(a2);
      #endif

    float a3 = asin((h1*sin(a2  + radians(90)))/h2);
      #if DEBUGACTIVE
        Serial.print("a3:\t"); Serial.println(a3);
      #endif

    float a4 = radians(90) - (a3 + a2);
      #if DEBUGACTIVE
        Serial.print("a4:\t"); Serial.println(degrees(a4));
      #endif

    float a5 = a1 - a4;
      #if DEBUGACTIVE
        Serial.print("a5:\t"); Serial.println(degrees(a5));
      #endif

    float theta_h = a0 - a5;
      #if DEBUGACTIVE
        Serial.print("theta_h:\t"); Serial.println(degrees(theta_h));
      #endif

    float r_0 = (h1*sin(a4)/sin(a3));
      #if DEBUGACTIVE
        Serial.print("r_0:\t"); Serial.println(r_0);
      #endif

    //berechnung f??r x-z ebene
    float h = sqrt(sq(r_0) + sq(x));
    float phi = asin(x/h);

    float theta_s = acos((sq(h) + sq(s) - sq(w))/(2*h * s)) - phi;
      #if DEBUGACTIVE
        Serial.print("theta_s:\t"); Serial.println(degrees(theta_s));
      #endif

    float theta_w = acos((sq(w) + sq(s) - sq(h))/(2 * w * s));
      #if DEBUGACTIVE
        Serial.print("theta_w:\t"); Serial.println(degrees(theta_w));
      #endif

    double a6Val = dx/ds;
      #if DEBUGACTIVE
        Serial.print("DX/DS:\t"); Serial.println((a6Val));
      #endif
    float a6 = asin(a6Val);                   //RAD
      #if DEBUGACTIVE
        Serial.print("a6:\t"); Serial.println(degrees(a6));
      #endif

    float a7 = radians(180) - (theta_s + a6); //RAD
      #if DEBUGACTIVE
        Serial.print("a7:\t"); Serial.println(degrees(a7));
      #endif

    float a8 = theta_s + a6;
      #if DEBUGACTIVE
        Serial.print("a8:\t"); Serial.println(degrees(a8));
      #endif

    float a9 = acos(dx/ds);
      #if DEBUGACTIVE
        Serial.print("a9:\t"); Serial.println(degrees(a9));
      #endif

    float thetaStandardAngle = radians(60);
    float theta_sa = radians(180) - (a8 + a9);
      #if DEBUGACTIVE
        Serial.print("theta_sa:\t"); Serial.println(degrees(theta_sa));
      #endif

    float theta_sa_corr = thetaStandardAngle - theta_sa;
      #if DEBUGACTIVE
        Serial.print("theta_sa_corr:\t"); Serial.println(degrees(theta_sa_corr));
      #endif
    //int returnArray[3] = {theta_h, theta_s, theta_sa_corr};
    //return returnArray;
    wArray[0] = degrees(theta_h);
    wArray[1] = degrees(theta_s);
    wArray[2] = degrees(theta_sa_corr);
    //wArray[2] = degrees(theta_sa);
}

void angleTest(){
  //einfache Tests zu bewegungen eines einzelnen Beins
  /*
  getLegAngles(50, 0, 175);
  transformLegAnglesToSVSingle(1, wArray[0], wArray[1], wArray[2]);
  confirmPos();

  
  transformLegAnglesToSVSingle(1, 0, 30, 30);
  confirmPos();
  delay(1000);
  transformLegAnglesToSVSingle(2, 0, 30, 30);
  confirmPos();
  delay(1000);
  transformLegAnglesToSVSingle(3, 0, 30, 30);
  confirmPos();
  delay(1000);
  transformLegAnglesToSVSingle(4, 0, 30, 30);
  confirmPos();
  delay(1000);
  //confirmPos();
  //delay(1000);
*/

  for(int i = 0; i <= 50; i++){
    getLegAngles(0, 0, 125 + i);
    transformLegAnglesToSVSingle(1, wArray[0], wArray[1], wArray[2]);
    confirmPos();
    delay(10);
  }
  
  delay(1000);
  for(int i = 0; i <= 50; i++){
    getLegAngles(i, 0, 175);
    transformLegAnglesToSVSingle(1, wArray[0], wArray[1], wArray[2]);
    confirmPos();
    delay(10);
  }

  for(int i = 0; i <= 50; i++){
    getLegAngles(50, 0, 175 - i);
    transformLegAnglesToSVSingle(1, wArray[0], wArray[1], wArray[2]);
    confirmPos();
    delay(10);
  }  
  delay(1000);
  
  for(int i = 0; i <= 50; i++){
    getLegAngles(50 - i, 0, 125);
    transformLegAnglesToSVSingle(1, wArray[0], wArray[1], wArray[2]);
    confirmPos();
    delay(10);
  }
  
}

void walkingGaitLF(){
  getLegAngles(50, 0, 150);
  transformLegAnglesToSVSingle(1, wArray[0], wArray[1], wArray[2]);
  confirmPos();
  delay(2000);
  /*
  for(int i = 0; i <= 100; i++){
    float t = (float)i/10;
    getLegAngles(bezierCurveN3(0,t), 0, bezierCurveN3(1, t));
    transformLegAnglesToSVSingle(1, wArray[0], wArray[1], wArray[2]);
    confirmPos();
    delay(100);
  }

  getLegAngles(0, 0, 150);
  transformLegAnglesToSVSingle(1, wArray[0], wArray[1], wArray[2]);
  confirmPos();
  delay(2000);
  */
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

void stepexperiment(){
pwm.setPWM(2,0,ServoPosArrayStandardVincent[0][2]);
pwm.setPWM(6,0,ServoPosArrayStandardVincent[1][2]);
pwm.setPWM(10,0,ServoPosArrayStandardVincent[2][2]);
pwm.setPWM(14,0,ServoPosArrayStandardVincent[3][2]);
int Hilfsvariableleg1_O = ServoPosArrayStandardVincent[0][1];
int Hilfsvariableleg1_U = ServoPosArrayStandardVincent[0][0];
int Hilfsvariableleg2_O = ServoPosArrayStandardVincent[1][1];
int Hilfsvariableleg2_U = ServoPosArrayStandardVincent[1][0];
int Hilfsvariableleg3_O = ServoPosArrayStandardVincent[2][1];
int Hilfsvariableleg3_U = ServoPosArrayStandardVincent[2][0];
int Hilfsvariableleg4_O = ServoPosArrayStandardVincent[3][1];
int Hilfsvariableleg4_U = ServoPosArrayStandardVincent[3][0];
//For-Schleife l??uft durch und jedes bein wird soweit bewegt wie n??tig
for(int laufvariable = 0 ; laufvariable < 150; laufvariable ++){
  // Bein 1 
  if(Hilfsvariableleg1_O <= ServoPosArrayback[0][1]){
    pwm.setPWM(1,0,Hilfsvariableleg1_O);
  }
  if(Hilfsvariableleg1_U <= ServoPosArrayback[0][0]){
    pwm.setPWM(0,0,Hilfsvariableleg1_U);
  }
  // Bein 2 
  if(Hilfsvariableleg2_O >= ServoPosArrayback[1][1]){
    pwm.setPWM(5,0,Hilfsvariableleg2_O);
  }
  if(Hilfsvariableleg2_U >= ServoPosArrayback[1][0]){
    pwm.setPWM(4,0,Hilfsvariableleg2_U);
  }
  // Bein 3 
  if(Hilfsvariableleg3_O <= ServoPosArrayback[2][1]){
    pwm.setPWM(9,0,Hilfsvariableleg3_O);
  }
  if(Hilfsvariableleg3_U <= ServoPosArrayback[2][0]){
    pwm.setPWM(8,0,Hilfsvariableleg3_U);
  }
  // Bein 4 
  if(Hilfsvariableleg4_O >= ServoPosArrayback[3][1]){
    pwm.setPWM(13,0,Hilfsvariableleg4_O);
  }
  if(Hilfsvariableleg4_U >= ServoPosArrayback[3][0]){
    pwm.setPWM(12,0,Hilfsvariableleg4_U);
  }
  Hilfsvariableleg1_O ++;
  Hilfsvariableleg1_U ++;
  Hilfsvariableleg2_O --;
  Hilfsvariableleg2_U -=2;
  Hilfsvariableleg3_O ++;
  Hilfsvariableleg3_U ++;
  Hilfsvariableleg4_O --;
  Hilfsvariableleg4_U -=2;
  delay(1);
}
///////////////////////////////////////////////////////////////////////
//Bein 1 nach vorne 
for(int legpos = ServoPosArrayback[0][1]; legpos >= 260; legpos--){
  pwm.setPWM(1,0,legpos);
  delay(1);
}
for(int legpos = ServoPosArrayback[0][0]; legpos >= ServoPosArrayStandardVincent[2][0]; legpos--){
  pwm.setPWM(0,0,legpos);
  delay(1);
}
for(int legpos = 260; legpos <= ServoPosArrayStandardVincent[0][1]; legpos++){
  pwm.setPWM(1,0,legpos);
  delay(1);
}
// Bein 2 nach vorne  /////////////////////////////////////////////

for(int legpos = ServoPosArrayback[1][1]; legpos <= 350; legpos++){
  pwm.setPWM(5,0,legpos);
  delay(1);
}
for(int legpos = ServoPosArrayback[1][0]; legpos <= ServoPosArrayStandardVincent[1][0]; legpos++){
  pwm.setPWM(4,0,legpos);
  delay(1);
}
for(int legpos = 350; legpos >= ServoPosArrayStandardVincent[1][1]; legpos--){
  pwm.setPWM(5,0,legpos);
 delay(1);
}
// Bewege bein 4 nach vorne ////////////////////////////////////////////////
for(int legpos = ServoPosArrayback[3][1]; legpos <= 350; legpos++){
  pwm.setPWM(13,0,legpos);
  delay(1);
}
for(int legpos = ServoPosArrayback[3][0]; legpos <= ServoPosArrayStandardVincent[3][0]; legpos++){
  pwm.setPWM(12,0,legpos);
  delay(1);
}
for(int legpos = 350; legpos >= ServoPosArrayStandardVincent[3][1]; legpos--){
  pwm.setPWM(13,0,legpos);
  delay(1);
}
//Bewege bein 3 nach vorne /////////////////////////////////////////////////////
for(int legpos = ServoPosArrayback[2][1]; legpos >= 260; legpos--){
  pwm.setPWM(9,0,legpos);
  delay(1);
}
for(int legpos = ServoPosArrayback[2][0]; legpos >= ServoPosArrayStandardVincent[2][0]; legpos--){
  pwm.setPWM(8,0,legpos);
  delay(1);
}
for(int legpos = 260; legpos <= ServoPosArrayStandardVincent[2][1]; legpos++){
  pwm.setPWM(9,0,legpos);
  delay(1);
}
}


void step(){


  // Bein 1 
  //lift foot of the ground 
  for(int legpos = ServoPosArray[0][1]; legpos >= 190; legpos --){
    pwm.setPWM(1,0,legpos);
    delay(1);
  }
  //move whole leg forward 
for(int legpos = ServoPosArray[0][0]; legpos >= ServoPosArrayforward[0][0]; legpos --){
  pwm.setPWM(0,0,legpos);
  delay(1);
}
//place foot on the ground 
for(int legpos = 190; legpos <= ServoPosArrayforward[0][1]; legpos ++){
  pwm.setPWM(1,0,legpos);
  delay(2);
}
////////////////////////////////////
//delay(20);
// forward movement of leg completed 
// Hilfsvariablen f??r die Bewegung jedes beins erstellen
int Hilfsvariableleg1_O = ServoPosArrayforward[0][1];
int Hilfsvariableleg1_U = ServoPosArrayforward[0][0];
int Hilfsvariableleg2_O = ServoPosArray[1][1];
int Hilfsvariableleg2_U = ServoPosArray[1][0];
int Hilfsvariableleg3_O = ServoPosArray[2][1];
int Hilfsvariableleg3_U = ServoPosArray[2][0];
int Hilfsvariableleg4_O = ServoPosArray[3][1];
int Hilfsvariableleg4_U = ServoPosArray[3][0];
//For-Schleife l??uft durch und jedes bein wird soweit bewegt wie n??tig
for(int laufvariable = 0 ; laufvariable < 150; laufvariable ++){
  // Bein 1 
  if(Hilfsvariableleg1_O <= ServoPosArray[0][1]){
    pwm.setPWM(1,0,Hilfsvariableleg1_O);
  }
  if(Hilfsvariableleg1_U <= ServoPosArray[0][0]){
    pwm.setPWM(0,0,Hilfsvariableleg1_U);
  }
  // Bein 2 
  if(Hilfsvariableleg2_O >= ServoPosArrayback[1][1]){
    pwm.setPWM(5,0,Hilfsvariableleg2_O);
  }
  if(Hilfsvariableleg2_U >= ServoPosArrayback[1][0]){
    pwm.setPWM(4,0,Hilfsvariableleg2_U);
  }
  // Bein 3 
  if(Hilfsvariableleg3_O <= ServoPosArrayback[2][1]){
    pwm.setPWM(9,0,Hilfsvariableleg3_O);
  }
  if(Hilfsvariableleg3_U <= ServoPosArrayback[2][0]){
    pwm.setPWM(8,0,Hilfsvariableleg3_U);
  }
  // Bein 4 
  if(Hilfsvariableleg4_O >= ServoPosArrayback[3][1]){
    pwm.setPWM(13,0,Hilfsvariableleg4_O);
  }
  if(Hilfsvariableleg4_U >= ServoPosArrayback[3][0]){
    pwm.setPWM(12,0,Hilfsvariableleg4_U);
  }
  Hilfsvariableleg1_O ++;
  Hilfsvariableleg1_U ++;
  Hilfsvariableleg2_O --;
  Hilfsvariableleg2_U -=2;
  Hilfsvariableleg3_O ++;
  Hilfsvariableleg3_U ++;
  Hilfsvariableleg4_O --;
  Hilfsvariableleg4_U -=2;
  delay(1);
}

// Bewege bein 4 zur??ck in startposition
for(int legpos = ServoPosArrayback[3][1]; legpos <= 350; legpos++){
  pwm.setPWM(13,0,legpos);
  delay(1);
}
for(int legpos = ServoPosArrayback[3][0]; legpos <= ServoPosArray[3][0]; legpos++){
  pwm.setPWM(12,0,legpos);
  delay(1);
}
for(int legpos = 350; legpos >= ServoPosArray[3][1]; legpos--){
  pwm.setPWM(13,0,legpos);
  delay(1);
}
//delay(20);
// nachziehen bein 4 fertig 
///////////////////////////////////
// Bewege Bein 3 zur??ck in startposition
for(int legpos = ServoPosArrayback[2][1]; legpos >= 260; legpos--){
  pwm.setPWM(9,0,legpos);
  delay(1);
}
for(int legpos = ServoPosArrayback[2][0]; legpos >= ServoPosArray[2][0]; legpos--){
  pwm.setPWM(8,0,legpos);
  delay(1);
}
for(int legpos = 260; legpos <= ServoPosArray[2][1]; legpos++){
  pwm.setPWM(9,0,legpos);
  delay(1);
}
//delay(20);

////////////////////////////////////////////////
// Bewege bein 2 zur??ck in startposition
for(int legpos = ServoPosArrayback[1][1]; legpos <= 350; legpos++){
  pwm.setPWM(5,0,legpos);
  delay(1);
}
for(int legpos = ServoPosArrayback[1][0]; legpos <= ServoPosArray[1][0]; legpos++){
  pwm.setPWM(4,0,legpos);
  delay(1);
}
for(int legpos = 350; legpos >= ServoPosArray[1][1]; legpos--){
  pwm.setPWM(5,0,legpos);
 delay(1);
}
//delay(20);
// nachziehen bein 4 fertig 
/*
///////////////////////////////////
// Bewege Bein 3 zur??ck in startposition
for(int legpos = ServoPosArrayback[2][1]; legpos >= 260; legpos--){
  pwm.setPWM(9,0,legpos);
  delay(2);
}
for(int legpos = ServoPosArrayback[2][0]; legpos >= ServoPosArray[2][0]; legpos--){
  pwm.setPWM(8,0,legpos);
  delay(2);
}
for(int legpos = 260; legpos <= ServoPosArray[2][1]; legpos++){
  pwm.setPWM(9,0,legpos);
  delay(2);
}
delay(20);
//Bein 3 fertig 
*/


/*
int Hilfsvarablediagonaleunten 
int Hilfsvarablediagonaleoben
if(fabs(ServoPosArrayforward[0][0] - ServoPosArray[0][0]) > fabs(ServoPosArrayforward[0][1] - ServoPosArray[0][1])){
  int legpos2 = ServoPosArrayforward[0][1];
  for(int legpos = ServoPosArrayforward[0][0]; legpos <= ServoPosArray[0][0]; legpos++){
    pwm.setPWM(0,0,legpos);
    if(legpos2 <= ServoPosArray[0][1]){
      pwm.setPWM(1,0,legpos2);
    }
    legpos2++;

    delay(5);
  }
}else{
  int legpos2 = ServoPosArrayforward[0][0];
  for(int legpos = ServoPosArrayforward[0][1]; legpos <= ServoPosArray[0][1]; legpos++){
    pwm.setPWM(1,0,legpos);
    if(legpos2 <= ServoPosArray[0][0]){
      pwm.setPWM(0,0,legpos2);
    }
    legpos2++;
    delay(5);
  }
}
*/


}

// kann entfernt werden wenn step funktioniert 
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

  //Wahl des entsprechenden Fu??es
  switch (leg)
  {
  case 1: break;
  case 2: servobyleg += 4; break;
  case 3: servobyleg += 8; break;
  case 4: servobyleg += 12;break;
  default:
    break;
  }
  if(servobyleg == 0 || servobyleg == 8){
  int Servo0 = 425;
  int Servo1 = 425;
  pwm.setPWM(servobyleg, 0, Servo0);
  pwm.setPWM(servobyleg + 1, 0, Servo1);
  delay(150);
  for(int pulslen = Servo1; pulslen > 190; pulslen -- ){
      pwm.setPWM(servobyleg + 1, 0, pulslen);
      delay(1);
  }
  for(int pulslen = Servo0; pulslen > 315; pulslen -- ){
    pwm.setPWM(servobyleg, 0, pulslen);
    delay(1);
  }
delay (50);


  for(int pulslen = 190; pulslen < 315 ;pulslen ++ ){
    pwm.setPWM(servobyleg + 1, 0, pulslen);
    delay(1);
  }
  delay(100);
  for(int pulslen = 315; pulslen < 425; pulslen ++ ){
    pwm.setPWM(servobyleg, 0, pulslen);
    pwm.setPWM(servobyleg + 1, 0, pulslen);
    delay(2);
  }
  }else{
    int Servo0 = 225;
    int Servo1 = 225;
    pwm.setPWM(servobyleg, 0, Servo0);
    pwm.setPWM(servobyleg + 1, 0, Servo1);
    delay(150);
     for(int pulslen = Servo1; pulslen < 460; pulslen ++ ){
      pwm.setPWM(servobyleg + 1, 0, pulslen);
      delay(1);
    }
    for(int pulslen = Servo0; pulslen < 335; pulslen ++ ){
     pwm.setPWM(servobyleg, 0, pulslen);
      delay(1);
    }
    delay (50);
    for(int pulslen = 460; pulslen > 335 ;pulslen -- ){
      pwm.setPWM(servobyleg + 1, 0, pulslen);
      delay(1);
    }
     delay(100);
    for(int pulslen = 335; pulslen > 225; pulslen -- ){
      pwm.setPWM(servobyleg, 0, pulslen);
      pwm.setPWM(servobyleg + 1, 0, pulslen);
      delay(2);
  }

  }
  
}

//Sitting down from default standing position 
//For all 4 legs
void sitdown(){
  int Servoleft0 = 425;
  int Servoleft1 = 425;
  int Servoright0 = 225;
  int Servoright1 = 225;
  int pulslenright = Servoright0;
  for(int pulslen = Servoleft0; pulslen < 480; pulslen ++ ){
    pwm.setPWM(0, 0, pulslen);
    pwm.setPWM(8, 0, pulslen);
    pwm.setPWM(4, 0, pulslenright);
    pwm.setPWM(12, 0, pulslenright);
    pulslenright = pulslenright - 1;
  }
  pulslenright = Servoright1;
  for(int pulslen = Servoleft1; pulslen > 330; pulslen -- ){
    pwm.setPWM(1, 0, pulslen);
    pwm.setPWM(9, 0, pulslen);
    pwm.setPWM(5, 0, pulslenright);
    pwm.setPWM(13, 0, pulslenright);
    pulslenright = pulslenright + 1;
  }
  pulslenright = 170;
  for(int pulslen = 480; pulslen < 495; pulslen ++ ){
    pwm.setPWM(0, 0, pulslen);
    pwm.setPWM(8, 0, pulslen);
    pwm.setPWM(4, 0, pulslenright);
    pwm.setPWM(12, 0, pulslenright);
    pulslenright = pulslenright - 1;
  }
}

//Standup sequence only if DAWG is all the way down 
void standup(){
  int Servoleft0 = 495;
  int Servoleft1 = 330;
  int Servoright0 = 155;
  int Servoright1 = 320;

  // setting all servos into down position 
  // maybe include setting 3 servo for hip rotation into default position
  pwm.setPWM(0, 0, Servoleft0);
  pwm.setPWM(1, 0, Servoleft1);

  pwm.setPWM(4, 0, Servoright0);
  pwm.setPWM(5, 0, Servoright1);

  pwm.setPWM(8, 0, Servoleft0);
  pwm.setPWM(9, 0, Servoleft1);

  pwm.setPWM(12, 0, Servoright0);
  pwm.setPWM(13, 0, Servoright1);
  // setting all legs into standing position 
  int pulslenright = Servoright1;
  for( int pulslen = Servoleft1; pulslen < 425; pulslen ++ ){
    pwm.setPWM(1, 0, pulslen);
    pwm.setPWM(9, 0, pulslen);
    pwm.setPWM(5, 0, pulslenright);
    pwm.setPWM(13, 0, pulslenright);
    pulslenright = pulslenright - 1;
    //delay(4);
  }
  pulslenright = Servoright0;
  for(int pulslen = Servoleft0; pulslen > 425; pulslen -- ){
    pwm.setPWM(0, 0, pulslen);
    pwm.setPWM(8, 0, pulslen);
    pwm.setPWM(4, 0, pulslenright);
    pwm.setPWM(12, 0, pulslenright);
    pulslenright = pulslenright + 1;
    //delay(4);
  }
}

// kann entfernt werden wenn step funktioniert#
//Just an experimental funktion how to implement walking with all 4 legs at once
void walkingexperiment(){
  //second attempt 
  /*
Links:   Standard, ausgestreckt, zur??ckgestellt | Rechts: Standard, ausgestreckt, zur??ckgestellt
Servo 0:  425        320 (--)         ???(440?) | Servo 0:  225       170           ???(240?)
Servo 1:  425        190 (--)         ???(425?) | Servo 1:  225       320           ???(225?)
  */
 
  //First failed attempt, moving feet diagonal to each other 
  /*
  int Servoleft0 = 425;
  int Servoright0 = 225;
  // all servos to default maybe not needed 
  standardpos(1);
  standardpos(2);
  standardpos(3);
  standardpos(4);
  //lifting foot off the ground 
  int pulslenright = Servoright0;
  for(int pulslenleft = Servoleft0; pulslenleft > 190 ; pulslenleft -- ){
    pwm.setPWM(1 , 0, pulslenleft);
    pwm.setPWM(13, 0, pulslenright);
    pulslenright++;
    delay(1);
  }
  //extending leg forward 
  pulslenright = Servoright0;
  for(int pulslenleft = Servoleft0; pulslenleft > 320; pulslenleft -- ){
    pwm.setPWM(0 ,0 ,pulslenleft);
    pwm.setPWM(12 ,0 ,pulslenright);
    pulslenright++;
    delay(1);
  }
  delay(20);
  // setting foot on the ground 
  pulslenright = 460;
  for(int pulslenleft = 190; pulslenleft < 320; pulslenleft ++ ){
    pwm.setPWM(1, 0, pulslenleft);
    pwm.setPWM(13, 0, pulslenright);
    pulslenright--;
    delay(1);
  }
  //moving both servos to get back into starting position
  pulslenright = 335;
  for(int pulslenleft = 320; pulslenleft < Servoleft0; pulslenleft ++){
  pwm.setPWM(0, 0, pulslenleft);
  pwm.setPWM(1, 0, pulslenleft);
  pwm.setPWM(12, 0, pulslenright);
  pwm.setPWM(13, 0, pulslenright);
  pulslenright--;
  }
  // Diagonale links vorne und rechts hinten abgeshlossen
  /////////////////////////////////////
  // Diagonale rechts vorne und links hinten 
  pulslenright = Servoright0;
  for(int pulslenleft = Servoleft0; pulslenleft > 190 ; pulslenleft -- ){
    pwm.setPWM(5 , 0, pulslenright);
    pwm.setPWM(9, 0, pulslenleft);
    pulslenright++;
    delay(1);
  }
  pulslenright = Servoright0;
  for(int pulslenleft = Servoleft0; pulslenleft > 320; pulslenleft -- ){
    pwm.setPWM(4 ,0 ,pulslenright);
    pwm.setPWM(8 ,0 ,pulslenleft);
    pulslenright++;
    delay(1);
  }
  delay(20);
  pulslenright = 460;
  for(int pulslenleft = 190; pulslenleft < 320; pulslenleft ++ ){
    pwm.setPWM(5, 0, pulslenright);
    pwm.setPWM(9, 0, pulslenleft);
    pulslenright--;
    delay(1);
  }
  pulslenright = 335;
  for(int pulslenleft = 320; pulslenleft < 425; pulslenleft ++){
  pwm.setPWM(4, 0, pulslenright);
  pwm.setPWM(8, 0, pulslenleft);
  pwm.setPWM(5, 0, pulslenright);
  pwm.setPWM(9, 0, pulslenleft);
  pulslenright--;
  }
  // Diagonale rechts vorne und links hinten abgeschlossen
  */
}

/*
// Punch left front 
void punch(){
  //check if in default position and goto default 
  int Servo0 = 425;
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
*/

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
