
#pragma once
//#include "PolyBLEP.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "AttackDecayEnvelope.h"
#include "Filters.h"




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
        void setPitchBend(float pitchbend);
        void reset();
        float process();
        void set_midi_note_number(int midi_note);
        void set_note_velocity(float note_velocity);

    
    
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
    float Apply2Pole(float sample,float g);
    float Apply3Pole(float sample,float g);
    void setMultimode(float m);
    float tptpc(float& state,float inp,float cutoff);

    
    
    juce::dsp::StateVariableTPTFilter<float> vadimFilter ;
    
    
    // obxd filter
            bool bandPassSw;
            float mm;
            bool selfOscPush;
    
    private:
    
    Attack_decay_envelope amp_env;
    Filters filter;
    
    
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

        int m_wavetype;
        float m_freq;
        float m_pitchbend;
        float m_sharp;
        float m_mod;
        float m_pointer_pos;
        float fm_phase_1;
        float fm_phase_2;
        float fm_phase_3;
        float fm_phase_4;
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
        float old_value_1;
        float old_value_2;
        float old_value_3;
        float old_value_4;
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
        float m_note_velocity;
        int m_mod_wheel_value = 0;
        int midi_note_number = 0;
        int pedal_steel = 1;

     
        // private methods
        float _clip(float x);
};
