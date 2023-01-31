///////////////////////////
//save gait patterns here 
//Walking

#include "defines.h"

#ifndef GAIT_H
#define GAIT_H

int p1[2] = {-20, 0};
int p2[2] = {-20, 40};
int p3[2] = {20, 40};
int p4[2] = {20, 0};

int bezierCurveN3(int coordinate, int t);
//void makeStep(int leg);

#endif