/*
  ==============================================================================

    CheapLFO.cpp
    Created: 24 May 2023 11:10:03pm
    Author:  sean wayland

  ==============================================================================
*/

#include "CheapLFO.h"


CheapLFO::CheapLFO(){
    
};
CheapLFO::~CheapLFO(){
    
};


void CheapLFO::init(float samplerte){
    
    lfoSamplerate = samplerte;
    lfoPhase = 0.0f;
    lfoDepth = 0.1f;
    lfoRate = 1.0f;
}

// value from zero to one
void CheapLFO::setDepth(float depth)
{
    lfoDepth = depth;
}

// rate in hz. 3 hz is a slow lfo
void CheapLFO::setRate(float rate)
{
    lfoRate = rate;
}

float CheapLFO::process()
{
    

    float a = lfoPhase*(lfoPhase - 0.5)*(lfoPhase - 1);
    float result = (a/0.0451125)*lfoDepth;
    //float result = sin(2*3.14159265358979323846264338327950288*lfoPhase);
    lfoPhase += lfoRate / lfoSamplerate;
    if(lfoPhase > 1.0){lfoPhase = 0.0;}
    return result;
    
}

void CheapLFO::reset()
{
    lfoPhase = 0.0f;
    lfoDepth = 0.1f;
    lfoRate = 1.0f;
}
