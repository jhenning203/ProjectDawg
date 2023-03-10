#include "gait.h"

//Funktion zur Erzeugung von Bezierkurven
//für bestimmte Koordinate
//zu bestimmtem Zeitpunkt

/*
//time € {0;1}
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
*/