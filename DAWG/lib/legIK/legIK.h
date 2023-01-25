///////////////////////////////////////////////////////
//first test to write own IK solver 

#define OFF_0               10
#define OFF_1               15
#define SHOULDER_LEGTH      188
#define WRIST_LENGTH        105

//1x3 matrix which contains desired position of leg
int legPos[3] = {0, 0,  0};

//funktion zum berechnen der benötigten Winkel für IK
int* getLegAngles(int* legC);
//Transformation der Winkel aus getLegAngles in nutzbare PWM-Werte von 150-600
int* transformLegAnglesToServoVals(int* legA);
