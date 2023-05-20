/*
  ==============================================================================

    Filters.h
    Created: 19 May 2023 7:58:06pm
    Author:  sean wayland

  ==============================================================================
*/

#pragma once
#include <string>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <math.h>


using namespace std;

class Filters {
public:
         Filters();
        ~Filters();
    //obxd filter
        void setResonance(float res);
        float diodePairResistanceApprox(float x);
        float NR(float sample, float g);
        float NR24(float sample,float g,float lpc);
        float Apply4Pole(float sample,float g);
        float Apply2Pole(float sample,float g);
        float Apply3Pole(float sample,float g);
        void setMultimode(float m);
        float tptpc(float& state,float inp,float cutoff);
        float hipass(float input);
    
    // obxd filter
            bool bandPassSw;
            float mm;
            bool selfOscPush;
    
private:
    // obxd filter
      
  float s1,s2,s3,s4;
  float R;
  float R24;
  float rcor,rcorInv;
  float rcor24,rcor24Inv;
  float SampleRate;
  float sampleRateInv;
  float state;
  float gain;
    
    //24 db multimode
    float mmt;
    int mmch;

    
};

