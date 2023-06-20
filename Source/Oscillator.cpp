#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "Oscillator.h"
#include "CheapLFO.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

Oscillator::Oscillator()
{
    m_wavetype = 2;
    m_filterType = 1;
    m_freq = 1.f;
    midi_note_number = 0;
    m_sharp = 0.f;
    m_attackRate = 0.1f;
    m_attackShape = 0.75f;
    m_resonance = 0.01f;
    m_bassoff = 0.f;
    m_detune = 1.0f;
    // m_cutoff = 0.f;
    srand((unsigned int)time(0));
    m_sah_last_value = 0.f;
    m_sah_current_value = (rand() / (float)RAND_MAX) * 2.f - 1.f;
    m_pitchbend = 1;
    env.reset();
    // mod_env.reset();
    m_filter_decay = 0.0f;
}

void Oscillator::setup(float sampleRate)
{
    m_sampleRate = sampleRate;
    // m_sampleRate = 96000;
    amp_env.SetSampleRate(m_sampleRate);
    amp_env.reset();
    filter_amp_env.SetSampleRate(m_sampleRate);
    filter_amp_env.reset();
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
    modulator = 0;
    m_pitchbend = 1;
    m_detune = 1.0;
    variosc.Init(m_sampleRate);
    varisaw.Init(m_sampleRate);
    bandlimOsc.Init(m_sampleRate);
    setDetune(1.0f);
    // lfo1.init(m_sampleRate);
    // lfo1.setDepth(1.0f);
    // lfo1.setRate(0.4f);
    m_lfo_value = 0.0f;
    m_attackRate = 0.1f;
    m_attackShape = 0.75f;
    m_filter_decay = 0.0f;
    m_filterAmount = 0.1f;
    m_filterSustain = 0.2f;
    m_filterRelease = 0.2f;
    m_filterAttackShape = 0.1f;
    m_filterDecayShape = 0.1f;
    m_filterVelocity = 0.0f;
    m_greaseVelocity = 0.0f;
    m_greaseKeyboard = 0.0f;
    m_cutoffKeyboard = 0.0f;
    m_gravyKeyboard = 0.0f;

    // vadimFilter
    //    juce::dsp::ProcessSpec spec;
    //    spec.maximumBlockSize = 512;
    //    spec.sampleRate = sampleRate;
    //    spec.numChannels = 1;
    //    vadimFilter.prepare(spec);
    //    vadimFilter.reset();
    //    vadimFilter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
    // lowPassFilter2.state = juce::dsp::IIR::Coefficients<float>::makeLowPass (sampleRate, 440.0);
    // lowPassFilter2.prepare (spec);

    //    int max;
    //    max = 100; //set the upper bound to generate the random number
    //    srand(time(0));
    //    pitchchange = rand()%max;
    //    float pp = float(pitchchange)/10000.f;
    //    rand_detune = 0.005 + pp;
}

Oscillator::~Oscillator() {}

void Oscillator::setSampleRate(float sampleRate)
{
    m_sampleRate = sampleRate;
}

void Oscillator::reset(float sampleRate)
{
    m_sampleRate = sampleRate;
    m_pointer_pos = fm_phase_1 = fm_phase_2 = fm_phase_3 = fm_phase_4 = m_sah_pointer_pos = 0.f;
    m_pitchbend = 1;
    m_detune = 1.0f;
    amp_env.reset();
    filter_amp_env.reset();
    // lfo1.setDepth(1.0f);
    // lfo1.setRate(1.0f);
    m_lfo_value = 0.0f;
    m_attackRate = 0.1f;
    m_attackShape = 0.75f;
    m_filterFM = 0.1f;
    m_filterFMVelocity = 0.1f;
    m_oneOverSr = 1.f / m_sampleRate;

    //    int max;
    //    max = 100; //set the upper bound to generate the random number
    //    srand(time(0));
    //    pitchchange = rand()%max;
    //    float pp = float(pitchchange)/10000.f;
    //    rand_detune = 0.005 + pp;
}

void Oscillator::set_midi_note_number(int midi_note)
{
    midi_note_number = midi_note;
}

void Oscillator::gate_filter_env()
{
    env.gate(false);
    // mod_env.gate(false);
}

void Oscillator::open_filter_env()
{
    env.gate(true);
    // mod_env.gate(true);
    filter_amp_env.reset();
}

// patrice functions

float Oscillator::b(float x, float a)
{
    if (x < a)
    {
        float x_over_a_minus_1 = (x / a) - 1.0;
        float x_over_a_minus_1_squared = x_over_a_minus_1 * x_over_a_minus_1;
        return -1.0 * x_over_a_minus_1_squared;
    }
    else if (x > (1.0 - a))
    {
        float x_minus_1_over_a = (x - 1.0) / a;
        float root_val = 1.0 + x_minus_1_over_a;
        return root_val * root_val;
    }
    else
    {
        return 0.0;
    }
}

float Oscillator::s(float input)
{
    return abs(fmod(input, 1.0));
}

float Oscillator::r0(float input, float w)
{
    if (s(input) < w)
    {
        return 1.0;
    }
    else
    {
        return -1.0;
    }
}

// r1(x) = r0(x) + b(s(x)) - b(s(x-w))
float Oscillator::r1(float input, float a, float w)
{
    b_s_x = b(s(input), a);
    b_s_x_minus_w = b(s(input - w), a);
    return r0(input, w) + b_s_x - b_s_x_minus_w;
}

float Oscillator::_clip(float x)
{
    if (x < 0.f)
    {
        x += 1.f;
    }
    else if (x >= 1.f)
    {
        x -= 1.f;
    }
    return x;
}

void Oscillator::setWavetype(int type)
{
    if (type != m_wavetype)
    {
        type = type < 0 ? 0 : type > 19 ? 19
                                        : type;
        m_wavetype = type;
    }
}

void Oscillator::setFiltertype(int type)
{
    if (type != m_filterType)
    {
        type = type < 0 ? 0 : type > 19 ? 19
                                        : type;
        m_filterType = type;
    }
}

void Oscillator::setFreq(float freq)
{
    m_freq = freq < 0.00001f ? 0.00001f : freq > m_srOverFour ? m_srOverFour
                                                              : freq;
    m_increment = m_freq / m_sampleRate;
}

void Oscillator::setSharp(float sharp)
{
    m_sharp = sharp < 0.f ? 0.f : sharp > 1.f ? 1.f
                                              : sharp;
}

void Oscillator::setMod(float mod)
{
    m_mod = mod < 0.f ? 0.f : mod > 1.f ? 1.f
                                        : mod;
}

void Oscillator::setFilterVelocity(float filterVelocity)
{
    m_filterVelocity = filterVelocity < 0.f ? 0.f : filterVelocity > 1.f ? 1.f
                                                                         : filterVelocity;
}

void Oscillator::setGreaseVelocity(float GreaseVelocity)
{
    m_greaseVelocity = GreaseVelocity < -1.f ? -1.f : GreaseVelocity > 1.f ? 1.f
                                                                           : GreaseVelocity;
}

void Oscillator::setGreaseKeyboard(float GreaseKeyboard)
{
    m_greaseKeyboard = GreaseKeyboard < -1.f ? -1.f : GreaseKeyboard > 1.f ? 1.f
                                                                           : GreaseKeyboard;
}

void Oscillator::setGravyKeyboard(float GravyKeyboard)
{
    m_gravyKeyboard = GravyKeyboard < -1.f ? -1.f : GravyKeyboard > 1.f ? 1.f
                                                                        : GravyKeyboard;
}

void Oscillator::setGravyVelocity(float GravyVelocity)
{
    m_gravyVelocity = GravyVelocity < -1.f ? -1.f : GravyVelocity > 1.f ? 1.f
                                                                        : GravyVelocity;
}

void Oscillator::setFilterFMVelocity(float FilterFMVelocity)
{
    m_filterFMVelocity = FilterFMVelocity < 0.f ? 0.f : FilterFMVelocity > 1.f ? 1.f
                                                                               : FilterFMVelocity;
}

void Oscillator::setFilterFM(float FilterFM)
{
    m_filterFM = FilterFM < 0.f ? 0.f : FilterFM > 1.f ? 1.f
                                                       : FilterFM;
}

void Oscillator::setFilterAmount(float filteramount)
{
    m_filterAmount = filteramount < 0.f ? 0.f : filteramount > 1.f ? 1.f
                                                                   : filteramount;
}

void Oscillator::setFilterAttack(float filterattack)
{
    m_filterAttack = filterattack < 0.f ? 0.f : filterattack > 1.f ? 1.f
                                                                   : filterattack;
}

void Oscillator::setFilterSustain(float filterSustain)
{
    m_filterSustain = filterSustain < 0.f ? 0.f : filterSustain > 1.f ? 1.f
                                                                      : filterSustain;
}

void Oscillator::setFilterRelease(float filterRelease)
{
    m_filterRelease = filterRelease < 0.f ? 0.f : filterRelease > 1.f ? 1.f
                                                                      : filterRelease;
}

void Oscillator::setFilterAttackShape(float filterAttackShape)
{
    m_filterAttackShape = filterAttackShape < 0.f ? 0.f : filterAttackShape > 1.f ? 1.f
                                                                                  : filterAttackShape;
}

void Oscillator::setFilterDecay(float filterdecay)
{
    m_filterDecay = filterdecay < 0.f ? 0.f : filterdecay > 1.f ? 1.f
                                                                : filterdecay;
}

void Oscillator::setFilterDecayShape(float filterDecayshape)
{
    m_filterDecayShape = filterDecayshape < 0.f ? 0.f : filterDecayshape > 1.f ? 1.f
                                                                               : filterDecayshape;
}

void Oscillator::setAttackRate(float attackRate)
{
    m_attackRate = attackRate < 0.f ? 0.f : attackRate > 1.f ? 1.f
                                                             : attackRate;
}

void Oscillator::setAttackshape(float attackShape)
{
    m_attackShape = attackShape < 0.f ? 0.f : attackShape > 1.f ? 1.f
                                                                : attackShape;
}

void Oscillator::setCutoff(float cutoff)
{
    m_cutoff = cutoff < 0.f ? 0.f : cutoff > 1.f ? 1.f
                                                 : cutoff;
}

void Oscillator::setCutoffKeyboard(float CutoffKeyboard)
{
    m_cutoffKeyboard = CutoffKeyboard < 0.f ? 0.f : CutoffKeyboard > 1.f ? 1.f
                                                                         : CutoffKeyboard;
}

void Oscillator::setRes(float resonance)
{
    m_resonance = resonance < 0.f ? 0.f : resonance > 1.f ? 1.f
                                                          : resonance;
}

void Oscillator::setBassoff(float bassoff)
{
    m_bassoff = bassoff < 0.f ? 0.f : bassoff > 1.f ? 1.f
                                                    : bassoff;
}

void Oscillator::setDetune(float detune)
{
    m_detune = detune < 0.5f ? 0.5f : detune > 2.f ? 2.f
                                                   : detune;
}

void Oscillator::set_note_velocity(float note_velocity)
{
    m_note_velocity = note_velocity;
}

void Oscillator::setPitchBend(float pitchWheelPos)
{

    if ((m_note_velocity > 0.5 && (pedal_steel == 1)) || (pedal_steel == 0))
    {
        if (pitchWheelPos > 8192)
        {
            auto val = pitchWheelPos - 8192;
            m_pitchbend = 1 + (val / 10000);
        }
        else
        {
            auto val = 8192 - pitchWheelPos;
            m_pitchbend = 1 - val / 8192;
        }

        if (m_pitchbend < 0.5)
        {
            m_pitchbend = 0.5;
        }

        if (m_pitchbend > 1.5)
        {
            m_pitchbend = 1.5;
        }
    }
    else
    {
        m_pitchbend = 1.0;
    }
}

float Oscillator::process()
{
    float numh = 0.f, pos = 0.f;
    float value = 0.f, maxHarms = 0.f;
    float old_x_value = old_y_value = 0.0;
    // float key_adjust = 0.0f;
    m_feedback = 0.0f;

    // m_mod = (m_mod + m_greaseVelocity*(m_note_velocity/127.0f))/2;

    float m_mod_g = (m_mod + m_greaseVelocity * m_note_velocity * m_mod + m_greaseKeyboard * midi_note_number / 127) / 3;
    if (m_mod_g < 0.001)
    {
        m_mod_g = 0.001;
    }
    // float m_mod_g = m_modAmount*mod_envValue*m_mod;
    float m_sharp_g = (m_sharp + m_gravyVelocity * m_note_velocity * m_mod + m_gravyKeyboard * midi_note_number / 127) / 3;
    if (m_sharp_g < 0.001)
    {
        m_sharp_g = 0.001;
    }

    switch (m_wavetype)
    {
        // Sine with feedback attenuated with pitch

    case 0:

        // m_feedback = 0.93 - (0.0004*m_freq);

        //            if (m_sharp > 0.68){m_sharp = 0.68;}
        //            m_feedback = (m_sharp+0.4) - (0.0004*m_freq);
        m_feedback = (m_sharp_g - (0.0005 * m_freq));

        // m_feedback = 0.5;
        // vadimFilter.setResonance(m_mod*2);

        //            if (m_feedback > 1.0 || m_feedback < 0.1){
        //                m_feedback = 0.6;
        //            }

        {
            modulator = sinf(m_twopi * m_pointer_pos + (prev_value * m_feedback * 0.8));
            prev_value = modulator;

            // value = sinf(0.25*10*(modulator) + m_twopi * m_pointer_pos + (old_value*m_feedback*0.8));
            value = sinf((m_mod_g + (m_note_velocity / 5)) * 10 * (modulator) + m_twopi * m_pointer_pos + (old_value * m_feedback * 0.8));
            // vadimFilter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
            //  filter fm ?
            // vadimFilter.setCutoffFrequency(3000*m_sharp + value*1000*m_sharp);
            // value = vadimFilter.processSample(1, value);
            old_value = value;

            break;
        }

        // band limited pulse width waylo belangeo
    case 1:

    {
        pulse_width = m_mod_g;
        phase1 = m_pointer_pos + 0.5 * pulse_width;
        phase2 = m_pointer_pos - 0.5 * pulse_width;

        maxHarms = 3 * (m_srOverFour / m_freq);
        // modified to allow m_sharp to change wave shape
        // numh = m_sharp * 80.f + 4.f;
        numh = 80.f + 4.f;

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

        value = value1 - (m_sharp_g * value2);
        // value = hipass(value);

        break;
    }
        // dx7 2 op

    case 2:

    {
        m_feedback_x = 6.0;
        m_feedback_y = 8.0;
        float x = m_twopi * m_pointer_pos;
        float y = m_twopi * m_pointer_pos;
        // float A1 = 1.0;
        // float f1 = 1.0;
        float A2 = m_mod_g * 10;
        // float f2 = 1.0;
        value = sin(y + A2 * sin(x + m_feedback * old_x_value) + old_y_value);
        old_x_value = sin(x);
        old_y_value = sin(y);
        // value = hipass(value);
        break;
    }

        // Saw

    case 3:

    {
        maxHarms = 4 * m_srOverFour / m_freq;
        numh = m_sharp_g * 100.f + 4.f;
        if (numh > maxHarms)
            numh = maxHarms;
        pos = m_pointer_pos + 0.5f;
        if (pos >= 1.f)
            pos -= 1.f;
        pos = pos * 2.f - 1.f;
        value = -(pos - tanhf(numh * pos) / tanhf(numh));

        // value = hipass(value);

        break;
    }

        // Ramp
        // attempt at saw like "fixed pulse"
        // oscillator called P2 on page 21 https://mirm.ru/upload/iblock/cd0/Nord%20Lead%20A1,%20A1R%20(EN).pdf

    case 4:

    {
        if (m_mod_g < 0.001)
        {
            m_mod_g = 0.001;
        }

        if (fixed_pulse_counter < 0.1f)
        {
            value = m_mod_g * 10.f * fixed_pulse_counter;
        }
        else
        {
            value = 2.0f + (-10.f * fixed_pulse_counter * m_mod_g);
        }

        if (value < 0)
        {
            value = 0;
        }

        if (m_pointer_pos < 0.1)
        {
            fixed_pulse_counter = 0.0f;
        }

        break;
    }
        // pulse like
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

        float f = 2 + m_mod_g * 20;
        if (f > 20)
        {
            f = 20;
        }
        float j = (f * m_pointer_pos) - 1;
        float x = (-1 * pow(j, 5.6)) + 1;
        if (isnan(x))
        {
            x = 0.0;
        }
        if (x < 0)
        {
            x = 0.0;
        }
        if (x > 1)
        {
            x = 1.0;
        }
        value = x;

        break;
    }

        // 2 op fm with feedback
    case 6:

    {
        float x = m_twopi * m_pointer_pos;
        float A1 = 1.0;
        float f1 = 1.0;
        // float A2 = 3.5;
        float f2 = 1.0;
        value = A1 * sin(f1 * x + 10 * m_mod * sin(f2 * x) + (old_value * m_sharp_g));
        old_value = value;
        prev_value = value;
        value = (value + prev_value) / 2;

        break;
    }

        // waylo tan function with low pass
    case 7:

    {

        float pw = 3 * (m_mod_g + 0.3f);
        value = tanhf(m_twopi * sin(pw * M_PI * m_pointer_pos));
        if (m_pointer_pos > (1 / pw))
        {
            value = 0;
        }

        break;
    }

        // waylo tan function with low pass
    case 8:

    {

        if (m_mod_g > 0.8)
        {
            m_mod_g = 0.8f;
        }
        if (m_mod_g < 0.2)
        {
            m_mod_g = 0.2f;
        }
        float a = 0.15 - (m_sharp_g / 10.0);
        float w = m_mod_g + (m_note_velocity / 10);
        value = r1(m_pointer_pos, a, w);

        //
        //            env.setAttackRate(m_sampleRate/20);
        //            env.setDecayRate(m_sampleRate*0.8);
        //            env.setReleaseRate(m_sampleRate*0.7);
        //            env.setSustainLevel(0.1);
        //            env.setTargetRatioA(0.1);
        //            env.setTargetRatioDR(2.0);
        //            float env_value = env.getOutput();

        break;
    }

    case 9:
    {

        env.setAttackRate(m_sampleRate * 3);
        env.setDecayRate(m_sampleRate * 4);
        env.setReleaseRate(m_sampleRate * 4);
        env.setSustainLevel(0.2);
        env.setTargetRatioA(0.5);
        env.setTargetRatioDR(1.0);
        float env_value = env.getOutput(); // reface DX
        // operator 3 is 2 all others are 1
        // 4 -> 3 -> 1
        // 2 -> 1
        // operators 1 and 3 are mixed in the output
        //                        float op1_level = 117/127;
        //                        float op2_level = 101/127;
        //                        float op3_level = 84/127;
        //                        float op4_level = 96/127;
        //
        //                        float op1_fdbk = 48*2/127;
        //                        float op2_fdbk = 33*2/127;
        //                        float op3_fdbk = 46*2/127;
        //                        float op4_fdbk = 25*2/127;

        // if(m_sharp > 0.65){m_sharp = 0.65;}
        m_feedback = (m_sharp_g + 0.4) - (0.0004 * m_freq);
        if (m_feedback > 1.0)
        {
            m_feedback = 0.9;
        }
        if (m_feedback < 0.1)
        {
            m_feedback = 0.1;
        }

        if (midi_note_number > 0 && !(isnan(midi_note_number)))
        {
            m_mod_g = m_mod_g + 1 / midi_note_number;
        };

        // operator 4
        float fm_value_4 = sinf(m_twopi * fm_phase_2 + m_feedback * old_value_4);
        old_value_4 = 0.7 * fm_value_4;

        // operator 3
        float fm_value_3 = sinf(m_twopi * fm_phase_3 + m_feedback * old_value_3 + (m_note_velocity)*m_mod_g * 10 * fm_value_4);
        old_value_3 = 0.6 * fm_value_3;

        // operator 2
        float fm_value_2 = sinf(m_twopi * fm_phase_2 + m_feedback * old_value_2);
        old_value_2 = 0.8 * fm_value_2;
        // value = (fm_value_1 + old_value)/2;
        // value = fm_value_2;

        // operator 1
        float fm_value_1 = sinf(m_twopi * fm_phase_2 + m_feedback * old_value_1 + env_value * (m_note_velocity * 0.8) * m_mod_g * 10 * fm_value_2 + (m_note_velocity * 0.8) * m_mod * 10 * fm_value_3);
        old_value_1 = fm_value_1;
        // value = (fm_value_1 + old_value)/2;
        value = fm_value_1 + fm_value_3;
        fm_phase_2 += m_pitchbend * m_freq * m_oneOverSr;
        fm_phase_2 = _clip(m_pointer_pos);
        fm_phase_3 += m_pitchbend * m_freq * 2 * m_oneOverSr;
        fm_phase_3 = _clip(m_pointer_pos);

        break;
    }

    case 10:
    {

        variosc.SetFreq(m_pitchbend * m_freq);
        variosc.SetWaveshape(m_sharp_g);
        variosc.SetPW(m_mod_g);
        value = variosc.Process();

        break;
    }

    case 11:
    {
        varisaw.SetWaveshape(m_sharp_g);
        varisaw.SetPW(m_mod_g);
        varisaw.SetFreq(m_freq * m_pitchbend * m_detune);
        value = varisaw.Process();

        break;
    }

        // sin w / feedback
    case 12:
    {

        m_feedback = 0.93 - (0.0004 * m_freq);
        if (m_sharp_g < 0.3)
        {
            m_sharp_g = 0.3;
        }

        m_feedback = m_cutoff * 0.95 - (0.0004 * m_freq);
        if (m_feedback > 1.0 || m_feedback < 0.1)
        {
            m_feedback = 0.6;
        }

        value = sinf(m_twopi * m_pointer_pos + (old_value * m_feedback));
        old_value = value;

        break;
    }
    case 13:
    {
        bandlimOsc.SetWaveform(daisysp::BlOsc::WAVE_SAW);
        bandlimOsc.SetFreq(m_freq);
        bandlimOsc.SetAmp(1.0);

        value = bandlimOsc.Process();

        break;
    }
    case 14:
    {

        bandlimOsc.SetWaveform(daisysp::BlOsc::WAVE_SQUARE);
        bandlimOsc.SetFreq(m_freq);
        bandlimOsc.SetAmp(0.8 + (0.19 * midi_note_number / 127));
        bandlimOsc.SetPw(m_mod_g);
        value = bandlimOsc.Process();

        break;
    }

    case 15:
    {

        env.setAttackRate(m_sampleRate / 20);
        env.setDecayRate(m_sampleRate * 10);
        env.setReleaseRate(m_sampleRate / 5);
        env.setSustainLevel(0.0);
        env.setTargetRatioA(0.5);
        env.setTargetRatioDR(1.0);
        float env_value = env.getOutput(); // reface DX
        // operator 3 is 2 all others are 1
        // 4 -> 3 -> 1
        // 2 -> 1
        // operators 1 and 3 are mixed in the output
        //            float op1_level = 127/127;
        //            float op2_level = 83/127;
        //            float op3_level = 19/127;
        //            float op4_level = 19/127;
        //
        //            float op1_fdbk = 48*2/127;
        //            float op2_fdbk = 33*2/127;
        //            float op3_fdbk = 46*2/127;
        //            float op4_fdbk = 25*2/127;

        // operator 3 is 2 all others are 1
        // 4 -> 3 -> 1
        // 2 -> 1
        // operators 1 and 3 are mixed in the output

        // if(m_sharp > 0.65){m_sharp = 0.65;}
        m_feedback = (m_sharp_g + 0.4) - (0.0004 * m_freq);
        if (m_feedback > 1.0)
        {
            m_feedback = 0.9;
        }
        if (m_feedback < 0.1)
        {
            m_feedback = 0.1;
        }

        if (midi_note_number > 0 && !(isnan(midi_note_number)))
        {
            m_mod_g = m_mod_g + 1 / midi_note_number;
        };

        // operator 4
        float fm_value_4 = sinf(m_twopi * fm_phase_4);

        // operator 3
        float fm_value_3 = sinf(m_twopi * fm_phase_3 + (m_note_velocity)*0.05 * m_mod_g * fm_value_4);

        // operator 2
        float fm_value_2 = sinf(m_twopi * fm_phase_2 + m_feedback * old_value_2 * 0.5 * m_note_velocity * 0.4);
        old_value_2 = 0.8 * fm_value_2;
        // value = (fm_value_1 + old_value)/2;
        // value = fm_value_2;

        // operator 1
        float fm_value_1 = sinf(m_twopi * fm_phase_2 + env_value * (m_note_velocity * 0.6) * m_mod_g * 10 * fm_value_2 + env_value * ((m_note_velocity * 0.2) * m_mod_g * 0.5 * fm_value_3) + m_feedback * old_value_1);

        old_value_1 = fm_value_1;
        // value = (fm_value_1 + old_value)/2;
        value = fm_value_1 + fm_value_3;

        fm_phase_2 += m_pitchbend * m_freq * m_oneOverSr;
        fm_phase_2 = _clip(fm_phase_2);
        fm_phase_3 += m_pitchbend * m_freq * 4 * m_oneOverSr;
        fm_phase_3 = _clip(fm_phase_3);
        fm_phase_4 += m_pitchbend * m_freq * 15 * m_oneOverSr;
        fm_phase_4 = _clip(fm_phase_4);

        break;
    }
    case 16:
    {

        env.setAttackRate(m_sampleRate * 3);
        env.setDecayRate(m_sampleRate * 4);
        env.setReleaseRate(m_sampleRate * 4);
        env.setSustainLevel(0.2);
        env.setTargetRatioA(0.5);
        env.setTargetRatioDR(1.0);
        float env_value = env.getOutput(); // reface DX
        // operator 3 is 2 all others are 1
        // 4 -> 3 -> 1
        // 2 -> 1
        // operators 1 and 3 are mixed in the output
        //                        float op1_level = 117/127;
        //                        float op2_level = 101/127;
        //                        float op3_level = 84/127;
        //                        float op4_level = 96/127;
        //
        //                        float op1_fdbk = 48*2/127;
        //                        float op2_fdbk = 33*2/127;
        //                        float op3_fdbk = 46*2/127;
        //                        float op4_fdbk = 25*2/127;

        // if(m_sharp > 0.65){m_sharp = 0.65;}
        m_feedback = (m_sharp_g + 0.4) - (0.0004 * m_freq);
        if (m_feedback > 1.0)
        {
            m_feedback = 0.9;
        }
        if (m_feedback < 0.1)
        {
            m_feedback = 0.1;
        }

        if (midi_note_number > 0 && !(isnan(midi_note_number)))
        {
            m_mod_g = m_mod_g + 1 / midi_note_number;
        };

        // operator 4
        float fm_value_4 = (sinf(m_twopi * fm_phase_2 + m_feedback * old_value_4));
        old_value_4 = 0.7 * fm_value_4;

        // operator 3
        float fm_value_3 = (sinf(m_twopi * fm_phase_3 + m_feedback * old_value_3 + (m_note_velocity)*m_mod_g * 10 * fm_value_4));
        old_value_3 = 0.6 * fm_value_3;

        // operator 2
        float fm_value_2 = (sinf(m_twopi * fm_phase_2 + m_feedback * old_value_2));
        old_value_2 = 0.8 * fm_value_2;
        // value = (fm_value_1 + old_value)/2;
        // value = fm_value_2;

        // operator 1
        float fm_value_1 = sinf(m_twopi * fm_phase_2 + m_feedback * old_value_1 + env_value * (m_note_velocity * 0.8) * m_mod_g * 10 * fm_value_2 + (m_note_velocity * 0.8) * m_mod_g * 10 * fm_value_3);
        old_value_1 = fm_value_1;
        // value = (fm_value_1 + old_value)/2;
        value = fm_value_1 + fm_value_3;
        fm_phase_2 += m_pitchbend * m_freq * m_oneOverSr;
        fm_phase_2 = _clip(fm_phase_2);
        fm_phase_3 += m_pitchbend * m_freq * 2 * m_oneOverSr;
        fm_phase_3 = _clip(fm_phase_3);

        break;
    }
        // organ
    case 17:
    {

        float sin1 = sinf(m_twopi * m_pointer_pos + 5 * m_mod_g * old_value_1);
        old_value_1 = sin1;
        float sin2 = sinf(m_twopi * fm_phase_2 + 5 * m_mod_g * old_value_2);
        old_value_2 = sin2;
        float sin3 = sinf(m_twopi * fm_phase_3 + 5 * m_mod_g * old_value_3);
        old_value_2 = sin3;

        fm_phase_2 += m_pitchbend * m_freq * m_oneOverSr * 2;
        fm_phase_3 += m_pitchbend * m_freq * m_oneOverSr * 3;
        fm_phase_2 = _clip(fm_phase_2);
        fm_phase_3 = _clip(fm_phase_3);

        value = (sin1 + m_sharp_g * sin2 + m_cutoff * sin3) / 3.0f;

        break;
    }
    case 18:
    {
        value = 0;
        break;
    }
    case 19:
    {
        value = 0;
        break;
    }
    }

    if (m_wavetype < 20)
    {

        m_pointer_pos += m_detune * m_pitchbend * m_freq * m_oneOverSr * m_detune; //*(1-rand_detune)
        m_pointer_pos = _clip(m_pointer_pos);
        fixed_pulse_counter += 11000 * m_oneOverSr;
        env.process();

        amp_env.Set_amp_envelope_rate(m_attackRate * 100);
        value = value * amp_env.process(m_attackShape, 0.75, "attack_env");

        if (m_cutoff < 0.99)
        {
            float filter_cutoff = m_cutoff * 20000;

            // Adjust the curves of the Attack, or Decay and Release segments,
            // from the initial default values (small number such as 0.0001 to 0.01 for mostly-exponential, large numbers like 100 for //       virtually linear):

            env.setAttackRate(20 * m_filterAttack * m_sampleRate); // .1 second
            env.setDecayRate(50 * m_filterDecay * 4 * m_sampleRate);
            env.setReleaseRate(m_filterRelease * m_sampleRate);
            env.setSustainLevel(m_filterSustain);
            env.setTargetRatioA(m_filterAttackShape / 10.0f);
            env.setTargetRatioDR(m_filterDecayShape * 100);
            m_envValue = env.process();
            //            m_envValue = m_envValue + 2*(m_note_velocity/127.0f);
            filter_cutoff = filter_cutoff + 10 * m_filterAmount * (filter_cutoff * m_envValue) + 10 * m_note_velocity * m_filterVelocity * m_envValue * filter_cutoff;
            // filter_cutoff = 3*m_envValue*filter_cutoff;
            filter_cutoff = filter_cutoff + filter_cutoff * m_cutoffKeyboard * (midi_note_number);
            if (filter_cutoff > 15000)
            {
                filter_cutoff = 15000.0f;
            }

            // higher notes louder
            value = (value + 3 * (midi_note_number / 127) * value) / 4;

            // obxd filter

            if (m_filterType == 0)
            {
                float filter_resonance = m_resonance;
                filter.setMultimode(1.0);
                filter.setResonance(filter_resonance);
                filter_cutoff = filter_cutoff + m_filterFM * value * filter_cutoff + m_filterFMVelocity * m_note_velocity * value * filter_cutoff;
                value = filter.Apply4Pole(value, filter_cutoff);
            }

            if (m_filterType == 1)
            {
                vadimFilter2.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
                vadimFilter2.setCutoffFrequency(filter_cutoff);
                if (m_resonance < 0.01)
                {
                    m_resonance = 0.01;
                }
                vadimFilter2.setResonance(m_resonance);
                filter_cutoff = filter_cutoff + m_filterFM * value * filter_cutoff + m_filterFMVelocity * m_note_velocity * value * filter_cutoff;
                vadimFilter2.setCutoffFrequency(filter_cutoff);
                // value = vadimFilter.processSample(1, value);
                value = vadimFilter2.processSample(1, value);
            }

            //            ladderFilter.setCutoffFrequencyHz(filter_cutoff);
            //            if(m_resonance < 0.01){m_resonance = 0.01;}
            //            ladderFilter.setResonance(m_resonance);
            //            value = ladderFilter.process(value, 1);
        }

        if ((m_freq > 0) && (m_bassoff > 0.1))
        {

            float bass_adjust = m_bassoff * 10.0f;
            vadimFilter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
            vadimFilter.setCutoffFrequency(0.9f);
            vadimFilter.setCutoffFrequency(m_freq - m_freq / bass_adjust);
            value = vadimFilter.processSample(1, value);
        }
        //
        //
        //
    }

    return value;
}
