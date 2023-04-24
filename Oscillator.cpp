

#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "Oscillator.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

Oscillator::Oscillator() {
    m_wavetype = 2;
    m_freq = 1.f;
    m_sharp = 0.f;
    srand((unsigned int)time(0));
    m_sah_last_value = 0.f;
    m_sah_current_value = (rand() / (float)RAND_MAX) * 2.f - 1.f;
    
}

void Oscillator::setup(float sampleRate) {
    m_sampleRate = sampleRate;
    m_sampleRate = 96000;
    m_oneOverSr = 1.f / m_sampleRate;
    m_increment = m_runningPhase = 0.0f;
    m_twopi = 2.f * M_PI;
    m_oneOverPiOverTwo = 1.f / (M_PI / 2.f);
    m_srOverFour = m_sampleRate / 4.f;
    m_srOverEight = m_sampleRate / 8.f;
    m_pointer_pos = m_sah_pointer_pos = 0.f;
}

Oscillator::~Oscillator() {}

void Oscillator::reset() {
    m_pointer_pos = m_sah_pointer_pos = 0.f;
}

float Oscillator::_clip(float x) {
    if (x < 0.f) {
        x += 1.f;
    } else if (x >= 1.f) {
        x -= 1.f;
    }
    return x;
}

void Oscillator::setWavetype(int type) {
    if (type != m_wavetype) {
        type = type < 0 ? 0 : type > 7 ? 7 : type;
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

float Oscillator::process() {
    float v1 = 0.f, v2 = 0.f, pointer = 0.f, numh = 0.f, pos = 0.f;
    float inc2 = 0.f, fade = 0.f, value = 0.f, maxHarms = 0.f;
    float oldvalue = 0.0;
    float key_adjust = 0.0f;
    m_feedback = 0.0f;
    

    switch (m_wavetype) {
        // Sine
        case 0:
            //m_feedback = 0.93 - (0.0004*m_freq);
 
            m_feedback = 0.9 - (0.0004*m_freq);
            if (m_feedback > 1.0 || m_feedback < 0.1){
                m_feedback = 0.6;
            }
            
            value = sinf(m_twopi * m_pointer_pos + (old_value*m_feedback));
            old_value = value;

            break;


        // band limited pulse width waylo belangeo
        case 1:
            
            pulse_width = 0.9;
            phase1 = m_pointer_pos + 0.5 * pulse_width;
            phase2 = m_pointer_pos - 0.5 * pulse_width;
            
            maxHarms = m_srOverFour / m_freq;
            numh = m_sharp * 46.f + 4.f;
            
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
            
            value = value1 - value2;

            break;
        // dx7 2 op
        case 2:
        {float x = m_twopi * m_pointer_pos;
            float A1 = 1.0;
            float f1 = 1.0;
            float A2 = 3.5;
            float f2 = 1.0;
            value = A1 * sin(f1*x + A2 * sin(f2*x));
            break;}
        // Saw
        case 3:
            maxHarms = m_srOverFour / m_freq;
            numh = m_sharp * 46.f + 4.f;
            if (numh > maxHarms)
                numh = maxHarms;
            pos = m_pointer_pos + 0.5f;
            if (pos >= 1.f)
                pos -= 1.f;
            pos = pos * 2.f - 1.f;
            value = -(pos - tanhf(numh * pos) / tanhf(numh));
            break;

        // Ramp
        case 4:
            maxHarms = m_srOverFour / m_freq;
            numh = m_sharp * 46.f + 4.f;
            if (numh > maxHarms)
                numh = maxHarms;
            pos = m_pointer_pos + 0.f;
            if (pos >= 1.f)
                pos -= 1.f;
            pos = pos * 2.f - 1.f;
            value = pos - tanhf(numh * pos) / tanhf(numh);
            break;
        // Pulse
        case 5:
            //m_feedback = 0.93 - (0.0004*m_freq);
 
            m_feedback = 0.85 - (0.0004*m_freq);
            if (m_feedback > 1.0 || m_feedback < 0.1){
                m_feedback = 0.6;
            }
            
            value = sinf(m_twopi * m_pointer_pos + (old_value*m_feedback));
            old_value = value;

            break;
        // Bi-Pulse
        case 6:
            
            
            
        {
            m_feedback = 0.4 - (0.0006*m_freq);
            if (m_feedback > 1.0 || m_feedback < 0.1){
                m_feedback = 0.3;
            }
            
            float x = m_twopi * m_pointer_pos;
            float A1 = 1.0;
            float f1 = 1.0;
            float A2 = 3.5;
            float f2 = 1.0;
            value = A1 * sin(f1*x + A2 * sin(f2*x) + (old_value*m_feedback))  ;
            old_value = value;
            prev_value = value;
            value = (value + prev_value)/2;
            break;}

        // SAH
        case 7:
            numh = 1.f - m_sharp;
            inc2 = 1.f / (1.f / (m_freq * m_oneOverSr) * numh);
            if (m_pointer_pos >= 1.f) {
                m_pointer_pos -= 1.f;
                m_sah_pointer_pos = 0.f;
                m_sah_last_value = m_sah_current_value;
                m_sah_current_value = (rand() / (float)RAND_MAX) * 2.f - 1.f;
            }
            if (m_sah_pointer_pos < 1.f) {
                fade = 0.5f * sinf(M_PI * (m_sah_pointer_pos + 0.5f)) + 0.5f;
                value = m_sah_current_value + (m_sah_last_value - m_sah_current_value) * fade;
                m_sah_pointer_pos += inc2;
            }
            else {
                value = m_sah_current_value;
            }
            m_pointer_pos += m_freq * m_oneOverSr;
            break;
        default:
            value = 0.f;
            break;
    }

    if (m_wavetype < 7) {
        m_pointer_pos += m_freq * m_oneOverSr;
        m_pointer_pos = _clip(m_pointer_pos);
    }

    return value;
}
