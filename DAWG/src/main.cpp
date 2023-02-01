#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "defines.h"
//#include "legIK.h"
//#include "gait.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int returnArray[3] = {0, 0, 0};
uint8_t servonum = 0;

///////////////////////////////////////////////////////////////////////////////
//WENN IHR NUR EUREN CODE TESTEN WOLLT --> HINTER EUREM NAMEN EINE 1 PLATZIEREN
#define DAWID     01
#define VINCENT   0
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
#define OFF_0               10
#define OFF_1               15
#define SHOULDER_LEGTH      107
#define WRIST_LENGTH        105
#define DS                  35
#define DX                  25
//////////////////////////////////////

void MenuSetup();
void showServoValuesToConcole();
void setServoPositionFromConsole(int servonum);
void setLegPositionFromConsole(int servonum);
void setLegPosition(int leg, int servo0, int servo1, int servo2);
void standupDaw();
int* getLegAngles(int* legC);
int* transformLegAnglesToServoVals(int* legA);
void angleTest();

void walkforeward();
void takeastep (int leg);
void sitdown();
void standup();
void punch();
void standardpos(int leg);
void walkingexperiment();
void step();

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
    setLegPosition(2,ServoPosArray[1][0],ServoPosArray[1][1],ServoPosArray[1][2]);
    setLegPosition(3,ServoPosArray[2][0],ServoPosArray[2][1],ServoPosArray[2][2]);
    setLegPosition(4,ServoPosArray[3][0],ServoPosArray[3][1],ServoPosArray[3][2]);
    
    int winkel[3] = {0, 15, 15};
    int* servoWerte = transformLegAnglesToServoVals(winkel);

    Serial.print("Servowert Schulter:\t"); Serial.println(servoWerte[0]);
    Serial.print("Servowert Steuerarm:\t"); Serial.println(servoWerte[1]);
    Serial.print("Servowert Hüfte:\t"); Serial.println(servoWerte[3]);

    //MenuSetup();
    //pwm.setPWM(0, 0, 425);
    //pwm.setPWM(1,0,425);
    //pwm.setPWM(2,0,290);
  #endif

  #if JANNIS

  #endif

  #if VINCENT
  //step();
  /*
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
      //übertragen der Werte aus dem ServPosArray auf den PCA
      pwm.setPWM(servoNumCounter,0,ServoPosArray[i][y]);
      //laufvariable, die den aktuellen Port auf dem PCA9685 vorgibt
      servoNumCounter++;
      //überspringt nicht genutzte Pins auf PCA9685
      if(servoNumCounter == 3){servoNumCounter = 4;}
      if(servoNumCounter == 7){servoNumCounter = 8;}
      if(servoNumCounter == 11){servoNumCounter = 12;}
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

  pwm.setPWM(servobyleg,0,servo0);
  delay(1);
  pwm.setPWM(servobyleg+1,0,servo1);
  delay(1);
  pwm.setPWM(servobyleg+2,0,servo2);
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

//legC[0]:  x;  theta_h Rotation Hüfte
//legC[1]:  y;  theta_s rotation oberschenkel
//legC[2]:  z;  theta_w Rotation Unterschenkel
int* getLegAngles(int* legC){
    //für berechnung siehe
    //https://www.adhamelarabawy.com/pdf/IK_Model.pdf

    //berechnung für y-z ebene
    int h1 = sqrt(OFF_0^2 + OFF_1^2);
    int h2 = sqrt(legC[2]^2 + legC[1]^2);

    int a0 = atan(legC[1]/legC[2]);
    int a1 = atan(OFF_1/OFF_0);
    int a2 = atan(OFF_0/OFF_1);
    int a3 = asin((h1*sin(a2  + radians(90)))/h2);
    int a4 = radians(90) - (a3 + a4);
    int a5 = a1 - a4;
    int theta_h = a0 - a5;

    int r_0 = (h1*sin(a4)/sin(a3));

    //berechnung für x-z ebene
    int h = sqrt(r_0^2 + legC[0]^2);
    int phi = asin(legC[0]/h);
    int theta_s = acos((h^2 + SHOULDER_LEGTH^2 - WRIST_LENGTH^2)/(2*h * SHOULDER_LEGTH)) - phi;
    int theta_w = acos((WRIST_LENGTH^2 + SHOULDER_LEGTH^2 - h^2)/(2 * WRIST_LENGTH * SHOULDER_LEGTH));

    int a6 = asin(DX/DS);                   //RAD
    int a7 = radians(180) - (theta_s + a6); //RAD
    int a8 = theta_s + a8;
    int a9 = acos(DX/DS);

    int thetaStandardAngle = radians(60);
    int theta_sa = radians(180) - (a8 + a9);
    int theta_sa_corr = thetaStandardAngle - theta_sa;
    //
    int returnArray[3] = {theta_h, theta_s, theta_sa_corr};
    return returnArray;
}

//Transformation von 3 Winekln in ° in PWM Servo-Werte
//bisher nur für linkes Bein Vorn
int* transformLegAnglesToServoVals(int* legA){
  
    int servoStepsperDgr = 450/200;

    //bisher nicht funktional für rechte Seite von DAWG !!
    //SERVOGRENZEN MÜSSEN NOCH ERMITTELT WERDEN

    //anstelle von dummy muss Konstante zum umrechnen von Winkeln in pwm-schritte eingefügt werden
    int pwm_servo2 = legA[0] * servoStepsperDgr + 0;
    int pwm_servo0 = legA[1] * servoStepsperDgr + 360;
    int pwm_servo1 = 300 - legA[2] * servoStepsperDgr;

    returnArray = {pwm_servo0, pwm_servo1, pwm_servo2};
    return returnArray;
}

void angleTest(){

}

/*
void makeStep(){
  for(int t = 0; t <= 1; t + 0.1){
   int servovals[3] =  transformLegAnglesToServoVals(getLegAngles({bezierCurve(0), bezierCurve(1), 0}));
   setLegPosition(0, servovals[0], servovals[1], servovals[2]);
   delay(100);
  }
}
*/
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
// Hilfsvariablen für die Bewegung jedes beins erstellen
int Hilfsvariableleg1_O = ServoPosArrayforward[0][1];
int Hilfsvariableleg1_U = ServoPosArrayforward[0][0];
int Hilfsvariableleg2_O = ServoPosArray[1][1];
int Hilfsvariableleg2_U = ServoPosArray[1][0];
int Hilfsvariableleg3_O = ServoPosArray[2][1];
int Hilfsvariableleg3_U = ServoPosArray[2][0];
int Hilfsvariableleg4_O = ServoPosArray[3][1];
int Hilfsvariableleg4_U = ServoPosArray[3][0];
//For-Schleife läuft durch und jedes bein wird soweit bewegt wie nötig
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

// Bewege bein 4 zurück in startposition
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
// Bewege Bein 3 zurück in startposition
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
// Bewege bein 4 zurück in startposition
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
// Bewege Bein 3 zurück in startposition
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
Links:   Standard, ausgestreckt, zurückgestellt | Rechts: Standard, ausgestreckt, zurückgestellt
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
