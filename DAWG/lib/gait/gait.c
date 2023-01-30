#include "gait.h"

//Funktion zur Erzeugung von Bezierkurven
//für bestimmte Koordinate
//zu bestimmtem Zeitpunkt
//time € {0;1}
int bezierCurveN3(int coordinate, int time){
    //%C(t) = (1-t)^3 * p0 + 3 * t * (1-t)^2 * p1 + 3 * t^2 * (1-t) * p2 + t^3 * p3;
    //P1 (-20|0) in Millimetern
    //P2 (-20|40)
    //P3 (20|40)
    //P4 (20|0)

}