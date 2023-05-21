/*
  ==============================================================================

    Filters.cpp
    Created: 19 May 2023 7:58:13pm
    Author:  sean wayland

  ==============================================================================
*/

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

#include "Filters.h"


Filters::Filters(){
    float m_twopi = 2.f * M_PI;
    state = 0;
    gain = 200.0f / (m_twopi * 96000);
    sampleRateInv = 1/96000;
    selfOscPush = false;
    bandPassSw = false;
    mm=0;
    s1=s2=s3=s4=0;
    R=1;
    R24=0;
    SampleRate = 96000;
    sampleRateInv = 1/SampleRate;
    float rcrate =sqrt((44000/SampleRate));
    rcor = (500.0 / 44000)*rcrate;
    rcor24 = (970.0 / 44000)*rcrate;
    rcorInv = 1 / rcor;
    rcor24Inv = 1 / rcor24;
};
Filters::~Filters(){
    
};





// obxd filter


float Filters::tptpc(float& state,float inp,float cutoff)
{
    double v = (inp - state) * cutoff / (1 + cutoff);
    double res = v + state;
    state = res + v;
    return res;
}

void Filters::setResonance(float res)
{
    R = 1-res;
    R24 =( 3.5 * res);
}


float Filters::NR24(float sample,float g,float lpc)
{
    float ml = 1 / (1+g);
    float S = (lpc*(lpc*(lpc*s1 + s2) + s3) +s4)*ml;
    float G = lpc*lpc*lpc*lpc;
    float y = (sample - R24 * S) / (1 + R24*G);
    return y;
}

float Filters::Apply4Pole(float sample,float g)
    {
            float g1 = (float)tan(g *sampleRateInv * M_PI);
            g = g1;


            
            float lpc = g / (1 + g);
            float y0 = NR24(sample,g,lpc);
            //first low pass in cascade
            double v = (y0 - s1) * lpc;
            double res = v + s1;
            s1 = res + v;
            //damping
            s1 =atan(s1*rcor24)*rcor24Inv;

            float y1= res;
            float y2 = tptpc(s2,y1,g);
            float y3 = tptpc(s3,y2,g);
            float y4 = tptpc(s4,y3,g);
            float mc;
            switch(mmch)
            {
            case 0:
                mc = ((1 - mmt) * y4 + (mmt) * y3);
                break;
            case 1:
                mc = ((1 - mmt) * y3 + (mmt) * y2);
                break;
            case 2:
               mc = ((1 - mmt) * y2 + (mmt) * y1);
                break;
            case 3:
                mc = y1;
                break;
            default:
                mc=0;
                break;
            }
            //half volume comp
            return mc * (1 + R24 * 0.45);
    }


float Filters::Apply3Pole(float sample,float g)
    {
            float g1 = (float)tan(g *sampleRateInv * M_PI);
            g = g1;


            
            float lpc = g / (1 + g);
            float y0 = NR24(sample,g,lpc);
            //first low pass in cascade
            double v = (y0 - s1) * lpc;
            double res = v + s1;
            s1 = res + v;
            //damping
            s1 =atan(s1*rcor24)*rcor24Inv;
            float y1= res;
            float y3 = tptpc(s3,y1,g);
            float y4 = tptpc(s4,y3,g);


            float mc;
            switch(mmch)
            {
            case 0:
                mc = ((1 - mmt) * y4 + (mmt) * y3);
                break;
            case 1:
                //mc = ((1 - mmt) * y3 + (mmt) * y2);
                break;
            case 2:
               // mc = ((1 - mmt) * y2 + (mmt) * y1);
                break;
            case 3:
                mc = y1;
                break;
            default:
                mc=0;
                break;
            }
            //half volume comp
            return mc * (1 + R24 * 0.45);
    }


float Filters::Apply2Pole(float sample,float g)
    {
            float g1 = (float)tan(g *sampleRateInv * M_PI);
            g = g1;


            
            float lpc = g / (1 + g);
            float y0 = NR24(sample,g,lpc);
            //first low pass in cascade
            double v = (y0 - s1) * lpc;
            double res = v + s1;
            s1 = res + v;
            //damping
            s1 =atan(s1*rcor24)*rcor24Inv;

            float y1= res;
            float y3 = tptpc(s2,y1,g);
            float y4 = y3;
            float mc;
            switch(mmch)
            {
            case 0:
                mc = ((1 - mmt) * y4 + (mmt) * y3);
                break;
            case 1:
                //mc = ((1 - mmt) * y3 + (mmt) * y2);
                break;
            case 2:
               // mc = ((1 - mmt) * y2 + (mmt) * y1);
                break;
            case 3:
                mc = y1;
                break;
            default:
                mc=0;
                break;
            }
            //half volume comp
            return mc * (1 + R24 * 0.45);
    }

void Filters::setMultimode(float m)
{
    mm = m;
    mmch = (int)(mm * 3);
    mmt = mm*3-mmch;
}


float Filters::hipass(float input) {
    
        float retval = input - state;
        state += gain * retval;
        return retval;
    }
