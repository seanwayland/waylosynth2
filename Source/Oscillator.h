
#pragma once
//#include "PolyBLEP.h"


class Oscillator {
    public:
        Oscillator();
        ~Oscillator();
        void setup(float sampleRate);
        void setWavetype(int type);
        void setFreq(float freq);
        float hipass(float input);
        void setSharp(float sharp);
        void setMod(float mod);
        void setPhase(float phase);
        void reset();
        float process();
    
       // patrice functions
        
       float s(float input);
       float r0(float input, float w);
       float r1(float input, float a, float w);
       float b(float x, float a);
    
    
    
        //obxd filter
    void setResonance(float res);
    float diodePairResistanceApprox(float x);
    float NR(float sample, float g);
    float NR24(float sample,float g,float lpc);
    float Apply4Pole(float sample,float g);
    void setMultimode(float m);
    float tptpc(float& state,float inp,float cutoff);
    
    
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
    
    float patrice_a;
    float patrice_w;
    float b_s_x;
    float b_s_x_minus_w;

    //24 db multimode
    float mmt;
    int mmch;
    
    
    
    
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
        float m_mod;
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
        float hi_pass_output;
        float oldval;
        float low_cutoff;
    
    
        float old_value;
        float old_x_value;
        float old_y_value;
        float m_feedback;
        float m_feedback_x;
        float m_feedback_y; 
        float m_runningPhase;
        float m_increment;
        float m_phase;
        float key_adjust;
        float sharp_scale;
        float SmoothData = 0.f;
        float prev_value;
        float fixed_pulse_counter;
        float state;
        float gain;
        float modulator;
     
        // private methods
        float _clip(float x);
};
