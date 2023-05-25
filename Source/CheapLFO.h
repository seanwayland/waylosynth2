/*
  ==============================================================================

    CheapLFO.h
    Created: 24 May 2023 11:09:54pm
    Author:  sean wayland

  ==============================================================================
*/

#pragma once
#include <stdlib.h>
#include <math.h>


using namespace std;

class CheapLFO {
public:
         CheapLFO();
        ~CheapLFO();

        void setDepth(float depth);
        void reset();
        void setRate(float rate);
        float process();
        void init(float samplerte);

    
private:
    float lfoDepth = 0.1f;
    float lfoRate = 3.0f;
    float lfoPhase = 0.0f;
    float lfoSamplerate = 48000.0f;

    
};
