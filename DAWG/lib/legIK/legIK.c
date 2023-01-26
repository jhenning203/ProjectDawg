#include "legIK.h"
#include <math.h>

//1x3 matrix which contains desired position of leg
//currently not used
int legPos[3] = {0, 0,  0};

//funktion zum berechnen der benötigten Winkel für IK

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
    int a3 = asin((h1*sin(a2+90))/h2);
    int a4 = 90 - (a3 + a4);
    int a5 = a1 - a4;
    int theta_h = a0 - a5;

    int r_0 = (h1*sin(a4)/sin(a3));

    //berechnung für x-z ebene
    int h = sqrt(r_0^2 + legC[0]^2);
    int phi = asin(legC[0]/h);
    int theta_s = acos((h^2 + SHOULDER_LEGTH^2 - WRIST_LENGTH^2)/(2*h * SHOULDER_LEGTH)) - phi;
    int theta_w = acos((WRIST_LENGTH^2 + SHOULDER_LEGTH^2 - h^2)/(2 * WRIST_LENGTH * SHOULDER_LEGTH));

    //int returnArray[3] = {theta_h, theta_s, theta_w};
    //return returnArray;
    //rückgabe der benötigten 3 winkel in °
    return {theta_h, theta_s, theta_w};
}

//Transformation von 3 Winekln in ° in PWM Servo-Werte
int* transformLegAnglesToServoVals(int* legA){
    int dummy = 0;
    //anstelle von dummy muss Konstante zum umrechnen von Winkeln in pwm-schritte eingefügt werden
    int pwm_servo2 = legA[0] * dummy;
    int pwm_servo0 = legA[1] * dummy;
    int pwm_servo1 = legA[2] * dummy;

    return {pwm_servo0, pwm_servo1, pwm_servo2};
}