/*
  ==============================================================================

    AttackDecayEnvelope.h
    Created: 19 May 2023 7:43:08pm
    Author:  sean wayland

  ==============================================================================
*/

#include <time.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <math.h>


#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

#pragma once

using namespace std;

class Attack_decay_envelope {
    
    
        public:
            Attack_decay_envelope();
            ~Attack_decay_envelope();
            float calculate_attack_gain(float envelope_position, float attack_coeff);
            float calculate_decay_gain(float envelope_position, float decay_coeff);
            float calculate_parabola_gain(float envelope_position);
            void SetSampleRate(int Samplerate);
            void Set_amp_envelope_rate(int envelope_rate);
            void reset();
            float amp_envelope_position;
            int amp_envelope_rate;
            float amp_samplerate;
            float process(float attack_coeff, float decay_coeff, string type);

    
};
