

#define DEBUGACTIVE 01

//beinhaltte alle Werte der Servos aller Beine
int ServoPosArray[4][3] = 
{ 
    425,    430,    290,
    235,    225,    315,
    425,    445,    300,  
    220,    205,    300    
};

int ServoPosArrayforward[4][3] = 
{ 
    390,    350,    290,
    280,    300,    315,
    380,    350,    300,  
    260,    300,    300    
};

int ServoPosArrayback[4][3] = 
{ 
    445,    500,    290,
    215,    110,    315,
    430,    510,    300,  
    205,    110,    300    
};


//standard values for reference
/*
int ServoPosArray[4][3] = 
{ 
    425,    425,    290,
    225,    240,    315,
    415,    425,    300,  
    225,    225,    300    
};
*/