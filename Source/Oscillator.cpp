

#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "Oscillator.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif


Attack_decay_envelope::Attack_decay_envelope(){
    amp_envelope_position = 0;
    amp_envelope_rate = 1;
    amp_samplerate = 96000;
    float last_value = 0.0;
}

Attack_decay_envelope::~Attack_decay_envelope(){
}

float Attack_decay_envelope::calculate_attack_gain(float envelope_position, float attack_coeff){
    
    float result = pow(envelope_position,attack_coeff );
    
    if (result > 1 || result < 0){return 1;}
    return result;
}
float Attack_decay_envelope::calculate_decay_gain(float envelope_position, float decay_coeff, float sustain_time){
    
    float result = 1/( pow( (envelope_position - sustain_time) , (1/decay_coeff) ) );
    if (result > 1 || result < 0){return 1;}
    return result;
}


float Attack_decay_envelope::calculate_parabola_gain(float envelope_position){

    float x_minus_1_sqr = pow(envelope_position-1,2);
    float result = -1*((1.3*x_minus_1_sqr) - 1.3)/1.3;
    if (result > 1){return 1.0;}
    if (result < 0){return 0.0;}
    return result;
}



float Attack_decay_envelope::process(float attack_coeff, float decay_coeff, float sustain_t, String type){
    float sss = sustain_t;
    
    amp_envelope_position = amp_envelope_position + amp_envelope_rate/amp_samplerate;
    
    
    if (type == "attack_env"){
        if (amp_envelope_position < 1.0){
            return 0.99*(calculate_attack_gain(amp_envelope_position, attack_coeff));
        }
        //    //and amp_envelope_position < (0.99 + sustain_t
        //    else if (amp_envelope_position >= 1.0 && amp_envelope_position < (sustain_t + 1.01 )){
        //        return 0.95;
        //    }
        //
        else {return 0.94*(calculate_decay_gain(amp_envelope_position, decay_coeff, sustain_t));}}
        //else { return 0.98;}}
    if (type == "parabola"){
        return calculate_parabola_gain(amp_envelope_position);
    }
    
    else{return 1.0;}
    
    
//    else{
//        return calculate_decay_gain(amp_envelope_position, decay_coeff, sustain_t);
//    }
    
}

void Attack_decay_envelope::SetSampleRate(int Samplert){
    amp_samplerate = Samplert;
}
void Attack_decay_envelope::Set_amp_envelope_rate(int envelope_rate){
    amp_envelope_rate = envelope_rate;
}

void Attack_decay_envelope::reset(){
    amp_envelope_position = 0;
    amp_envelope_rate = 1;
    amp_samplerate = 96000;
}







Oscillator::Oscillator() {
    m_wavetype = 2;
    m_freq = 1.f;
    midi_note_number = 0;
    m_sharp = 0.f;
    srand((unsigned int)time(0));
    m_sah_last_value = 0.f;
    m_sah_current_value = (rand() / (float)RAND_MAX) * 2.f - 1.f;
    m_pitchbend = 1;
    
    
    
}

void Oscillator::setup(float sampleRate) {
    m_sampleRate = sampleRate;
    m_sampleRate = 96000;
    amp_env.SetSampleRate(96000);
    amp_env.reset();
    
    
    
    m_oneOverSr = 1.f / m_sampleRate;
    m_increment = m_runningPhase = 0.0f;
    m_twopi = 2.f * M_PI;
    m_oneOverPiOverTwo = 1.f / (M_PI / 2.f);
    m_srOverFour = m_sampleRate / 4.f;
    m_srOverEight = m_sampleRate / 8.f;
    m_pointer_pos = m_sah_pointer_pos = 0.f;
    SmoothData = 0.f;
    fixed_pulse_counter = 0;
    oldval = hi_pass_output = 0.f;
    //low_cutoff = 40.0f;
    state = 0;
    gain = 200.0f / (m_twopi * m_sampleRate);
    modulator = 0;
    m_pitchbend = 1;
    

    // obxd filter
    selfOscPush = false;
    bandPassSw = false;
    mm=0;
    s1=s2=s3=s4=0;
    R=1;
    R24=0;
    SampleRate = m_sampleRate;
    sampleRateInv = 1/SampleRate;
    float rcrate =sqrt((44000/SampleRate));
    rcor = (500.0 / 44000)*rcrate;
    rcor24 = (970.0 / 44000)*rcrate;
    rcorInv = 1 / rcor;
    rcor24Inv = 1 / rcor24;
    
    
    // vadim filter
        // vadimFilter
        juce::dsp::ProcessSpec spec;
        spec.maximumBlockSize = 512;
        spec.sampleRate = sampleRate;
        spec.numChannels = 1;
        vadimFilter.prepare(spec);
        vadimFilter.reset();
        vadimFilter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);

    
}

Oscillator::~Oscillator() {}

void Oscillator::reset() {
    m_pointer_pos = m_sah_pointer_pos = 0.f;
    m_pitchbend = 1;
    amp_env.reset();

}


void Oscillator::set_midi_note_number(int midi_note){
    midi_note_number = midi_note;
}


// 


// patrice functions

float Oscillator::b(float x, float a){
    if (x < a){
        float x_over_a_minus_1 = (x/a) -1.0;
        float x_over_a_minus_1_squared = x_over_a_minus_1 * x_over_a_minus_1 ;
        return  -1.0* x_over_a_minus_1_squared;
    }
    else if (x > ( 1.0 -a )){
        float x_minus_1_over_a = (x-1.0)/a;
        float root_val = 1.0 + x_minus_1_over_a;
        return root_val*root_val;
    }
    else{
        return 0.0;
    }
    
}

float Oscillator::s(float input){
    return abs(fmod(input, 1.0));
}


float Oscillator::r0(float input, float w){
    if (s(input)< w){
        return 1.0;}
    else{
        return -1.0;
        }
        
    }

// r1(x) = r0(x) + b(s(x)) - b(s(x-w))
float Oscillator::r1(float input, float a, float w){
    b_s_x = b(s(input),a);
    b_s_x_minus_w = b(s(input-w),a);
    return r0(input,w) + b_s_x - b_s_x_minus_w;
}



// obxd filter


float Oscillator::tptpc(float& state,float inp,float cutoff)
{
    double v = (inp - state) * cutoff / (1 + cutoff);
    double res = v + state;
    state = res + v;
    return res;
}

void Oscillator::setResonance(float res)
{
    R = 1-res;
    R24 =( 3.5 * res);
}


float Oscillator::NR24(float sample,float g,float lpc)
{
    float ml = 1 / (1+g);
    float S = (lpc*(lpc*(lpc*s1 + s2) + s3) +s4)*ml;
    float G = lpc*lpc*lpc*lpc;
    float y = (sample - R24 * S) / (1 + R24*G);
    return y;
}

float Oscillator::Apply4Pole(float sample,float g)
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
            float y3 = tptpc(s3,y3,g);
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


float Oscillator::Apply3Pole(float sample,float g)
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


float Oscillator::Apply2Pole(float sample,float g)
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

void Oscillator::setMultimode(float m)
{
    mm = m;
    mmch = (int)(mm * 3);
    mmt = mm*3-mmch;
}



float Oscillator::_clip(float x) {
    if (x < 0.f) {
        x += 1.f;
    } else if (x >= 1.f) {
        x -= 1.f;
    }
    return x;
}


float Oscillator::hipass(float input) {
    
        float retval = input - state;
        state += gain * retval;
        return retval;
    }
  


void Oscillator::setWavetype(int type) {
    if (type != m_wavetype) {
        type = type < 0 ? 0 : type > 10 ? 10 : type;
        m_wavetype = type;
    }
}

void Oscillator::setFreq(float freq) {
    m_freq = freq < 0.00001f ? 0.00001f : freq > m_srOverFour ? m_srOverFour : freq;
    m_increment = m_freq / m_sampleRate;
}

void Oscillator::setSharp(float sharp) {
    m_sharp = sharp < 0.f ? 0.f : sharp > 1.f ? 1.f : sharp;
}

void Oscillator::setMod(float mod) {
    m_mod = mod < 0.f ? 0.f : mod > 1.f ? 1.f : mod;
}


void Oscillator::set_note_velocity(float note_velocity){
    m_note_velocity = note_velocity;
}


void Oscillator::setPitchBend(float pitchWheelPos){
    
    
    
    if( (m_note_velocity > 0.5 && (pedal_steel == 1) ) || (pedal_steel == 0) ){
        if (pitchWheelPos > 8192){
            auto val = pitchWheelPos - 8192;
            m_pitchbend = 1 + (val/10000);
        }
        else {
            auto val = 8192 - pitchWheelPos;
            m_pitchbend = 1 - val/8192;
            
        }
        
        if (m_pitchbend < 0.5){
            m_pitchbend = 0.5;
        }
        
        if (m_pitchbend > 1.5){
            m_pitchbend = 1.5;
        }}
    else{ m_pitchbend = 1.0;}

      
}
   
float Oscillator::process() {
    float v1 = 0.f, v2 = 0.f, pointer = 0.f, numh = 0.f, pos = 0.f;
    float inc2 = 0.f, fade = 0.f, value = 0.f, maxHarms = 0.f;
    float oldvalue = old_x_value = old_y_value = 0.0;
    float key_adjust = 0.0f;
    m_feedback = 0.0f;
    
    

    switch (m_wavetype) {
            // Sine with feedback attenuated with pitch
        case 0:
            
            
            //m_feedback = 0.93 - (0.0004*m_freq);
            
            //            if (m_sharp > 0.68){m_sharp = 0.68;}
            //            m_feedback = (m_sharp+0.4) - (0.0004*m_freq);
            m_feedback = (m_sharp + m_note_velocity/5) - (0.0005*m_freq);
            
            //m_feedback = 0.5;
            //vadimFilter.setResonance(m_mod*2);
            
            
            //            if (m_feedback > 1.0 || m_feedback < 0.1){
            //                m_feedback = 0.6;
            //            }
            
            
            
            
        {modulator = sinf(m_twopi * m_pointer_pos + (prev_value*m_feedback*0.8));
            prev_value = modulator;
            
            //value = sinf(0.25*10*(modulator) + m_twopi * m_pointer_pos + (old_value*m_feedback*0.8));
            value = sinf((m_mod+ (m_note_velocity/5))*10*(modulator) + m_twopi * m_pointer_pos + (old_value*m_feedback*0.8));
            vadimFilter.setCutoffFrequency(3000*m_sharp + value*1000*m_sharp);
            value = vadimFilter.processSample(1, value);
            old_value = value;
            
            
            break;}
            
            
            // band limited pulse width waylo belangeo
        case 1:
            
        {
            pulse_width = m_mod;
            phase1 = m_pointer_pos + 0.5 * pulse_width;
            phase2 = m_pointer_pos - 0.5 * pulse_width;
            
            maxHarms = 3*(m_srOverFour / m_freq);
            // modified to allow m_sharp to change wave shape
            //numh = m_sharp * 80.f + 4.f;
            numh =  80.f + 4.f;
            
            if (numh > maxHarms)
                numh = maxHarms;
            pos = phase1 + 0.5f;
            if (pos >= 1.f)
                pos -= 1.f;
            pos = pos * 2.f - 1.f;
            value1 = -(pos - tanhf(numh * pos) / tanhf(numh));
            
            pos = phase2 + 0.5f;
            if (pos >= 1.f)
                pos -= 1.f;
            pos = pos * 2.f - 1.f;
            value2 = -(pos - tanhf(numh * pos) / tanhf(numh));
            
            value = value1 - (m_sharp*value2);
            //value = hipass(value);
            
            
            break;}
            // dx7 2 op
            
        case 2:
            
            
        {
            m_feedback_x = 6.0;
            m_feedback_y = 8.0;
            float x = m_twopi * m_pointer_pos;
            float y = m_twopi * m_pointer_pos;
            float A1 = 1.0;
            float f1 = 1.0;
            float A2 = m_mod*10;
            float f2 = 1.0;
            value = sin(y + A2 * sin(x + m_feedback*old_x_value) + old_y_value);
            old_x_value = sin(x);
            old_y_value = sin(y);
            //value = hipass(value);
            break;}
            // Saw
            
        case 3:
            
        {maxHarms = 4*m_srOverFour / m_freq;
            numh = m_sharp * 100.f + 4.f;
            if (numh > maxHarms)
                numh = maxHarms;
            pos = m_pointer_pos + 0.5f;
            if (pos >= 1.f)
                pos -= 1.f;
            pos = pos * 2.f - 1.f;
            value = -(pos - tanhf(numh * pos) / tanhf(numh));
            
            //value = hipass(value);
            
            
            
            break;}
            
            // Ramp
            // attempt at saw like "fixed pulse"
            // oscillator called P2 on page 21 https://mirm.ru/upload/iblock/cd0/Nord%20Lead%20A1,%20A1R%20(EN).pdf
            
        case 4:
            
            if(m_mod < 0.001){m_mod = 0.001;}
        
        {if (fixed_pulse_counter < 0.1f){
            value = m_mod*10.f * fixed_pulse_counter;
        }
        else{
            value = 2.0f + (-10.f * fixed_pulse_counter*m_mod);
        }
            
            if (value < 0){
                value = 0;
            }
            
            if (m_pointer_pos < 0.1)
            {
                fixed_pulse_counter = 0.0f;
            }
            
            
            float filter_cutoff = m_sharp*5000;
            float filter_resonance = 0.05f;
            setMultimode(1.0f);
            setResonance(filter_resonance);
            value = Apply4Pole(value,filter_cutoff);
            
            
        break;}
            // sin with feedback
        case 5:
            
        {
            
//            //m_feedback = 0.93 - (0.0004*m_freq);
//            if(m_sharp<0.3){
//                m_sharp = 0.3;
//            }
//
//            m_feedback = m_sharp*0.95 - (0.0004*m_freq);
//            if (m_feedback > 1.0 || m_feedback < 0.1){
//                m_feedback = 0.6;
//            }
//
//            value = sinf(m_twopi * m_pointer_pos + (old_value*m_feedback));
//            old_value = value;
//            //value = hipass(value);
            
              float f = 2 + m_mod*20;
              if (f > 20) { f = 20;}
              float j = (f*m_pointer_pos)-1;
              float x = (-1*pow(j,5.6)) + 1;
              if (isnan(x)){x=0.0;}
              if (x < 0) { x = 0.0 ;}
              if (x>1 ){ x = 1.0 ;}
            
              float filter_cutoff = m_sharp*5000;
              float filter_resonance = 0.05f;
              setMultimode(1.0f);
               setResonance(filter_resonance);
               value = Apply3Pole(x,filter_cutoff);
            
            
            
            
            break;
            
            
        }
            
            // 2 op fm with feedback
        case 6:
            
            
        {
            
            
            float x = m_twopi * m_pointer_pos;
            float A1 = 1.0;
            float f1 = 1.0;
            float A2 = 3.5;
            float f2 = 1.0;
            value = A1 * sin(f1*x + 10*m_mod * sin(f2*x) + (old_value*m_sharp))  ;
            old_value = value;
            prev_value = value;
            value = (value + prev_value)/2;
            //value = hipass(value);
            break;}
            
            // waylo tan function with low pass
        case 7:
            
            
        {float pw = 3*(m_mod+ 0.3f);
            
            value = tanhf(m_twopi*sin(pw*M_PI*m_pointer_pos));
            if (m_pointer_pos>(1/pw)){
                value = 0;
            }
            
            
            
            float filter_cutoff = m_sharp*5000;
            float filter_resonance = 0.05f;
            setMultimode(1.0f);
            setResonance(filter_resonance);
            value = Apply4Pole(value,filter_cutoff);
            
        
            break;}
            
            // waylo tan function with low pass
        case 8:
            
            
        {
            

            if (m_mod > 0.8){m_mod = 0.8f;}
            if (m_mod < 0.2){m_mod = 0.2f;}
            float a = 0.15- (m_sharp / 10.0);
            float w = m_mod + (m_note_velocity/10);
            value = r1(m_pointer_pos, a,  w);

            break;
            
            
        }
            

            
    }
    

    if (m_wavetype < 9) {

        m_pointer_pos += m_pitchbend* m_freq * m_oneOverSr;
        m_pointer_pos = _clip(m_pointer_pos);
        fixed_pulse_counter += 11000 * m_oneOverSr;
        //fixed_pulse_counter = _clip(fixed_pulse_counter);
        
    }

    return value;
}
