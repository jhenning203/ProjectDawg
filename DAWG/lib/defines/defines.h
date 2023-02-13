#include <stdint.h>
//#include "utils.h"
#include <math.h>

#define DEBUGACTIVE 0
/*
//beinhaltte alle Werte der Servos aller Beine
int ServoPosArray[4][3] = 
{ 
    360,    300,    290,    //Zahl kleiner -> Winkel kleiner;   Zahl kleiner -> Winkel größer
    300,    350,    305,    //Zahl kleiner -> Winkel größer;    Zahl kleiner -> Winkel kleiner
    350,    300,    300,    //Zahl kleiner -> Winkel kleiner;   Zahl kleiner -> Winkel größer
    300,    340,    305     //Zahl kleiner -> Winkel größer;    Zahl kleiner -> Winkel kleiner    
};
*/


///////////////////////////////////////////////////
//Werte Vincent ab hier 

int ServoPosArrayforward[4][3] = 
{ 
    390,    350,    290,
    280,    300,    315,
    380,    350,    300,  
    260,    300,    300    
};

int ServoPosArrayback[4][3] = 
{ 
    445,    500,    295,
    220,    110,    310,
    430,    500,    295,  
    215,    110,    305    
};

int ServoPosArrayStandardVincent[4][3]=
{
    435,    425,    295,
    235,    225,    310,
    415,    425,    295,   
    230,    225,    305,
};

//standard values for reference

int ServoPosArray[4][3] = 
{ 
    425,    425,    290,
    225,    240,    315,
    415,    425,    300,  
    225,    225,    300    
};
