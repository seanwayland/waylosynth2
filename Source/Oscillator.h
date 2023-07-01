
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
        void setSampleRate(float sampleRate);
        void setup(float sampleRate);
        void setWavetype(int type);
        void setFiltertype(int filterType);
        void setFreq(float freq);
        float hipass(float input);
        void setSharp(float sharp);
        void setMod(float mod);
        void setAttackshape(float attackShape);
        void setAttackRate(float attackRate);
        void setFilterVelocity(float filterVelocity);
        void setGreaseVelocity(float GreaseVelocity);
        void setGreaseKeyboard(float GreaseKeyboard);
        void setGravyKeyboard(float GravyKeyboard);
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
        void reset(float sampleRate);
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
    //ADSR2 mod_env;
    daisysp::VariableShapeOscillator variosc;
    daisysp::VariableSawOscillator varisaw;
    daisysp::BlOsc bandlimOsc;
    //CheapLFO lfo1;
    
    
      // obxd filter
        
    float s1,s2,s3,s4 = 0.f;
    float R = 0.f;
    float R24 = 0.f;
    float rcor,rcorInv = 0.f;
    float rcor24,rcor24Inv = 0.f ;
    float SampleRate = 48000.0f;
    float sampleRateInv = 1/48000;
    
    float patrice_a = 0.f;
    float patrice_w = 0.f;
    float b_s_x = 0.f;
    float b_s_x_minus_w = 0.f;

    //24 db multimode
    float mmt = 0.f;
    int mmch = 0.f;
    
    
         // globals
        float m_sampleRate = 48000.0f;
        float m_oneOverSr = 1/48000;
        float m_twopi =  2*3.14159265358979323846264338327950288;
        float m_oneOverPiOverTwo = 0.f;
        float m_oneOverPi = 0.f;
        float m_srOverFour = 0.f;
        float m_srOverEight = 0.f;
        float m_srOverTwo = 0.f;

        int m_wavetype = 0;
        int m_filterType = 2;
        float m_freq = 0.f;
        float m_pitchbend = 0.f;
        float m_sharp = 0.f;
        float m_mod = 0.f;
        float m_attackRate = 0.f;
        float m_attackShape = 0.f;
        float m_filterVelocity = 0.f;
        float m_greaseVelocity = 0.f;
        float m_greaseKeyboard = 0.f;
        float m_gravyVelocity = 0.f;
        float m_gravyKeyboard = 0.f;
        float m_filterAmount = 0.f;
        float m_filterAttack = 0.f;
        float m_filterAttackShape = 0.f;
        float m_filterDecay = 0.f;
        float m_filterDecayShape = 0.f;
        float m_filterSustain = 0.f;
        float m_filterRelease = 0.f;
        float m_cutoff = 0.f;
        float m_cutoffKeyboard = 0.f;
        float m_filterFMVelocity = 0.f;
        float m_filterFM = 0.f;
        float m_resonance = 0.f;
        float m_bassoff = 0.f;
        float m_detune = 0.f;
        float m_pointer_pos = 0.f;
        float fm_phase_1 = 0.f;
        float fm_phase_2 = 0.f;
        float fm_phase_3 = 0.f;
        float fm_phase_4 = 0.f;
        float fm_m_pointer_pos = 0.f;
        float m_sah_pointer_pos = 0.f;
        float m_sah_last_value = 0.f;
        float m_sah_current_value = 0.f;
        float fm_depth = 0.f ;
        float fm_frequency = 0.f;
        float fm_index = 0.f;
        float m_envValue = 0.0f;
        float mod_envValue = 0.0f;
    
        float m_lfo_value = 0.0f;
    
        float phase1 = 0.f;
        float phase2 = 0.f;
        float pulse_width = 0.f;
        float value1 = 0.f;
        float value2 = 0.f;
        float hi_pass_output = 0.f;
        float oldval = 0.f;
        float low_cutoff = 0.f;
    
    
        float old_value = 0.f;
        float old_value_1  = 0.0f;
        float old_value_2 = 0.0f;
        float old_value_3 = 0.0f;
        float old_value_4 = 0.0f;
        float old_x_value = 0.f;
        float old_y_value = 0.f;
        float m_feedback = 0.f;
        float m_feedback_x = 0.f;
        float m_feedback_y = 0.f;
        float m_runningPhase = 0.f;
        float m_increment = 0.f;
        float m_phase = 0.f;
        float key_adjust = 0.f;
        float sharp_scale = 0.f;
        float SmoothData = 0.f;
        float prev_value = 0.f;
        float fixed_pulse_counter = 0.f;
        float state = 0.f;
        float gain = 0.f;
        float modulator = 0.f;
        float m_note_velocity = 0.f;
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
