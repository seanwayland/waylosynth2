
#pragma once
//#include "PolyBLEP.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "AttackDecayEnvelope.h"
#include "Filters.h"
#include "ADSR.h"
#include "VariableShapeOsc.h"
#include "VariableSawOsc.h"
#include "BandLimitedOsc.h"
#include "CheapLFO.h"





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
        void setAttackshape(float attackShape);
        void setAttackRate(float attackRate);
        void setFilterVelocity(float filterVelocity);
        void setGreaseVelocity(float GreaseVelocity);
        void setGreaseKeyboard(float GreaseKeyboard);
        void setGravyVelocity(float GravyVelocity);
        void setFilterAmount(float filteramount);
        void setFilterFM(float filterFM);
        void setFilterFMVelocity(float filterFMVelocity);
        void setFilterAttack(float filterattack);
        void setFilterSustain(float filterSustain);
        void setFilterAttackShape(float filterAttackShape);
        void setFilterDecay(float filterDecay);
        void setFilterRelease(float filterRelease);
        void setFilterDecayShape(float filterDecayShape);
        void setModAmount(float Modamount);
        void setModAttack(float Modattack);
        void setModSustain(float ModSustain);
        void setModAttackShape(float ModAttackShape);
        void setModDecay(float ModDecay);
        void setModRelease(float ModRelease);
        void setModDecayShape(float ModDecayShape);
        void setCutoff(float cutoff);
        void setCutoffKeyboard(float cutoffKeyboard);
        void setRes(float resonance);
        void setBassoff(float bassoff);
        void setDetune(float detune);
        void setPhase(float phase);
        void setPitchBend(float pitchbend);
        void reset();
        float process();
        void set_midi_note_number(int midi_note);
        void set_note_velocity(float note_velocity);
    
        void gate_filter_env();
        void open_filter_env();

    
    
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
    juce::dsp::StateVariableTPTFilter<float> vadimFilter2 ;
    
    
    //"LPF24"
    
    
    
    
    // obxd filter
            bool bandPassSw;
            float mm;
            bool selfOscPush;
    
    private:
    
    //juce::dsp::ProcessorDuplicator <dsp::IIR::Filter<float>, dsp::IIR::Coefficients <float>> lowPassFilter2;
    
    Attack_decay_envelope amp_env;
    Attack_decay_envelope filter_amp_env;
    Filters filter;
    Filters bass_off;
    ADSR2 env;
    ADSR2 mod_env;
    daisysp::VariableShapeOscillator variosc;
    daisysp::VariableSawOscillator varisaw;
    daisysp::BlOsc bandlimOsc;
    CheapLFO lfo1;
    
    
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
        float m_attackRate;
        float m_attackShape;
        float m_filterVelocity;
        float m_greaseVelocity;
        float m_greaseKeyboard;
        float m_gravyVelocity;
        float m_filterAmount;
        float m_filterAttack;
        float m_filterAttackShape;
        float m_filterDecay;
        float m_filterDecayShape;
        float m_filterSustain;
        float m_filterRelease;
        float m_cutoff;
        float m_cutoffKeyboard;
        float m_filterFMVelocity;
        float m_filterFM;
        float m_resonance;
        float m_bassoff;
        float m_detune;
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
        float m_envValue = 0.0f;
        float mod_envValue = 0.0f;
    
        float m_lfo_value = 0.0f;
    
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
    float rand_detune = 0.0;
    int pitchchange = 0;
    
    float m_filter_decay = 0.0f;
    float m_filter_decay_rate = 0.0f;
    
        
    
    float transition[1001];

     
        // private methods
        float _clip(float x);
};
