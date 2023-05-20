/*
  ==============================================================================

    AttackDecayEnvelope.cpp
    Created: 19 May 2023 7:43:21pm
    Author:  sean wayland

  ==============================================================================
*/

#include "AttackDecayEnvelope.h"
#include <string>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <math.h>


using namespace std;

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



float Attack_decay_envelope::process(float attack_coeff, float decay_coeff, float sustain_t, string type){
    
    amp_envelope_position = amp_envelope_position + amp_envelope_rate/amp_samplerate;
    
    
    if (type == "attack_env"){
        if (amp_envelope_position < 1.0){
            return 0.99*(calculate_attack_gain(amp_envelope_position, attack_coeff));
        }
        else {return 0.94*(calculate_decay_gain(amp_envelope_position, decay_coeff, sustain_t));}}
        //else { return 0.98;}}
    if (type == "parabola"){
        return calculate_parabola_gain(amp_envelope_position);
    }
    
    else{return 1.0;}
    
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




