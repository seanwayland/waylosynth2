
#pragma once
//#include "PolyBLEP.h"


class Oscillator {
    public:
        Oscillator();
        ~Oscillator();
        void setup(float sampleRate);
        void setWavetype(int type);
        void setFreq(float freq);
        float patrice_blep(float x, float a);
        float patrice_rr(float x, float w);
        float patrice_rrr(float x, float w, float a);
        void setSharp(float sharp);
        void setPhase(float phase);
        void reset();
        float process();
    double poly_blep(double t);


        
    private:
        // globals
        float m_sampleRate;
        float m_oneOverSr;
        float m_twopi;
        float m_oneOverPiOverTwo;
        float m_oneOverPi;
        float m_srOverFour;
        float m_srOverEight;
        float m_srOverTwo;

        // parameters
        // 0 = Sine, 1 = Triangle, 2 = Square, 3 = Saw,
        // 4 = Ramp, 5 = pulse, 6 = bi-pulse, 7 = SAH
        int m_wavetype;
        float m_freq;
        float m_sharp;
        float m_pointer_pos;
        float fm_m_pointer_pos;
        float m_sah_pointer_pos;
        float m_sah_last_value;
        float m_sah_current_value;
        float fm_depth;
        float fm_frequency;
        float fm_index;
    
        float phase1;
        float phase2;
        float pulse_width;
        float value1;
        float value2;
    
        float old_value;
        float m_feedback;
        float m_runningPhase;
        float m_increment;
        float m_phase;
        float key_adjust;
        float sharp_scale;
        float SmoothData = 0.f;
        float prev_value;
        // private methods
        float _clip(float x);
};
