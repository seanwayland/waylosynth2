
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "waylo_look_and_feel.h"

class waylosynth2AudioProcessorEditor  : public AudioProcessorEditor
{
public:
    waylosynth2AudioProcessorEditor (waylosynth2&, AudioProcessorValueTreeState& vts);
    ~waylosynth2AudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;

private:
    waylosynth2& processor;

    waylo_look_and_feel plugexLookAndFeel;

    AudioProcessorValueTreeState& valueTreeState;

    Label title;

    Label  attackLabel;
    Slider attackKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackAttachment;

    Label  decayLabel;
    Slider decayKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> decayAttachment;

    Label  sustainLabel;
    Slider sustainKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;

    Label  releaseLabel;
    Slider releaseKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;

    Label typeLabel;
    ComboBox typeCombo;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> typeAttachment;

    Label  sharpLabel;
    Slider sharpKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sharpAttachment;
    
    Label  modLabel;
    Slider modKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> modAttachment;

    Label  gainLabel;
    Slider gainKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    MidiKeyboardComponent keyboardComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (waylosynth2AudioProcessorEditor)
};


//
//// Sine with feedback attenuated with pitch
//case 0:
//
//
////m_feedback = 0.93 - (0.0004*m_freq);
////            if (m_sharp > 0.68){m_sharp = 0.68;}
////            m_feedback = (m_sharp+0.4) - (0.0004*m_freq);
//{
//
//m_feedback = (m_sharp + m_note_velocity/4) - (0.0005*m_freq);
//amp_env.Set_amp_envelope_rate(1);
//
//
//modulator = sinf(m_twopi * m_pointer_pos + (prev_value*m_feedback*0.8));
//prev_value = modulator;
//
//value = sinf((m_mod+ (m_note_velocity/3))*10*(modulator) + m_twopi * m_pointer_pos + (old_value*m_feedback*0.8));
//// filter fm thing
////vadimFilter.setCutoffFrequency(3000*m_sharp + value*1000*m_sharp);
////value = vadimFilter.processSample(1, value);
//amp_env.Set_amp_envelope_rate(4);
//float gain_val = amp_env.process(1.55, 1.5, 0.7, "parabola");
//value = value*gain_val;
//old_value = value;
//
//break;
//
//}
//
//
//// band limited pulse width waylo belangeo
//case 1:
//
//{
//pulse_width = m_mod;
//phase1 = m_pointer_pos + 0.5 * pulse_width;
//phase2 = m_pointer_pos - 0.5 * pulse_width;
//
//maxHarms = 3*(m_srOverFour / m_freq);
//// modified to allow m_sharp to change wave shape
////numh = m_sharp * 80.f + 4.f;
//numh =  80.f + 4.f;
//
//if (numh > maxHarms)
//    numh = maxHarms;
//pos = phase1 + 0.5f;
//if (pos >= 1.f)
//    pos -= 1.f;
//pos = pos * 2.f - 1.f;
//value1 = -(pos - tanhf(numh * pos) / tanhf(numh));
//
//pos = phase2 + 0.5f;
//if (pos >= 1.f)
//    pos -= 1.f;
//pos = pos * 2.f - 1.f;
//value2 = -(pos - tanhf(numh * pos) / tanhf(numh));
//
//value = value1 - (m_sharp*value2);
////value = hipass(value);
//
//
//break;}
//// dx7 2 op
//
//// f you have a signal x(t) = sin(w*t) and a modulation signal f(t) then:
//// x(t) = sin(w*t + f(t))
//
////  carrierPhase += carrierFreq
//// carrier=sin(carrierPhase + modIndex*modulatorOut).
//
//// value = sin((phase + modulation)*TWO_PI);
//
//case 2:
//
//
//{
//m_feedback_x = 6.0;
//m_feedback_y = 8.0;
//float x = m_twopi * m_pointer_pos;
//float y = m_twopi * m_pointer_pos;
//float A1 = 1.0;
//float f1 = 1.0;
//float A2 = m_mod*10;
//float f2 = 1.0;
//value = sin(y + A2 * sin(x + m_feedback*old_x_value) + old_y_value);
//old_x_value = sin(x);
//old_y_value = sin(y);
////value = hipass(value);
//break;
//
//}
//
//
//// Saw belangeo
//
//case 3:
//
//{
//maxHarms = 4*m_srOverFour / m_freq;
//numh = m_sharp * 100.f + 4.f;
//if (numh > maxHarms)
//    numh = maxHarms;
//pos = m_pointer_pos + 0.5f;
//if (pos >= 1.f)
//    pos -= 1.f;
//pos = pos * 2.f - 1.f;
//value = -(pos - tanhf(numh * pos) / tanhf(numh));
//
//break;
//
//}
//
//
//case 4:
//
//
//{
//value = sin(m_phase*m_twopi);
//break;
//}
//
////            if(m_mod < 0.001){m_mod = 0.001;}
////
////        if (fixed_pulse_counter < 0.1f){
////            value = m_mod*10.f * fixed_pulse_counter;
////        }
////        else{
////            value = 2.0f + (-10.f * fixed_pulse_counter*m_mod);
////        }
////
////            if (value < 0){
////                value = 0;
////            }
////
////            if (m_pointer_pos < 0.1)
////            {
////                fixed_pulse_counter = 0.0f;
////            }
////
////
////            float filter_cutoff = m_sharp*5000;
////            float filter_resonance = 0.05f;
////            setMultimode(1.0f);
////            setResonance(filter_resonance);
////            value = Apply3Pole(value,filter_cutoff);
////            amp_env.Set_amp_envelope_rate(10);
////            float gain_val = amp_env.process(1.55, 1.5, 0.2, "attack_env");
////            value = value*gain_val;
//
////vadimFilter.setCutoffFrequency(3000*m_sharp + value*1000*m_sharp);
////value = vadimFilter.processSample(1, value);
//
//
//
//// sin with feedback - actually desmos pulse like
//case 5:
//
//{
//  float f = 2 + m_mod*20;
//  if (f > 20) { f = 20;}
//  float j = (f*m_pointer_pos)-1;
//  float x = (-1*pow(j,5.6)) + 1;
//  if (isnan(x)){x=0.0;}
//  if (x < 0) { x = 0.0 ;}
//  if (x>1 ){ x = 1.0 ;}
//
//  float filter_cutoff = m_sharp*5000;
//  float filter_resonance = 0.05f;
//  setMultimode(1.0f);
//   setResonance(filter_resonance);
//   value = Apply3Pole(x,filter_cutoff);
//  
//
////            //m_feedback = 0.93 - (0.0004*m_freq);
////            if(m_sharp<0.3){
////                m_sharp = 0.3;
////            }
////
////            m_feedback = m_sharp*0.95 - (0.0004*m_freq);
////            if (m_feedback > 1.0 || m_feedback < 0.1){
////                m_feedback = 0.6;
////            }
////
////            value = sinf(m_twopi * m_pointer_pos + (old_value*m_feedback));
////            old_value = value;
////value = hipass(value);
//
//
//
//
//break;
//
//}
//
//// 2 op fm with feedback
//case 6:
//
//
//{
//
//
//float f = m_twopi * m_pointer_pos;
//float A1 = 1.0;
//float f1 = 1.0;
//float A2 = 3.5;
//float f2 = 1.0;
//value = A1 * sin(f1*f + A2 * sin(f2*f) + (old_value*m_sharp))  ;
//old_value = value;
//prev_value = value;
//value = (value + prev_value)/2;
////value = hipass(value);
//break;
//
//}
//
//// waylo tan function with low pass
//case 7:
//
//
//{float pw = 3*(m_mod+ 0.3f);
//
//value = tanhf(m_twopi*sin(pw*M_PI*m_pointer_pos));
//if (m_pointer_pos>(1/pw)){
//    value = 0;
//}
//
//
//
//float filter_cutoff = m_sharp*5000;
//float filter_resonance = 0.05f;
//setMultimode(1.0f);
//setResonance(filter_resonance);
//value = Apply4Pole(value,filter_cutoff);
//
//
//break;
//
//}
//
//// pwm blep
//case 8:
//
//
//{
//
//
//if (m_mod > 0.8){m_mod = 0.8f;}
//if (m_mod < 0.2){m_mod = 0.2f;}
//float a = 0.15- (m_sharp / 10.0);
//float w = m_mod + (m_note_velocity/10);
//value = r1(m_pointer_pos, a,  w);
//float filter_cutoff = m_sharp*5000;
//float filter_resonance = 0.1f;
//setMultimode(1.0f);
//setResonance(filter_resonance);
//value = Apply4Pole(value,filter_cutoff);
//break;
//
//}
//
//case 9:
//
//
//{
//// dx7 2 op
//
//// f you have a signal x(t) = sin(w*t) and a modulation signal f(t) then:
//// x(t) = sin(w*t + f(t))
//
////  carrierPhase += carrierFreq
//// carrier=sin(carrierPhase + modIndex*modulatorOut).
//
//// value = sin((phase + modulation)*TWO_PI);
//m_feedback_x = 6.0;
//m_feedback_y = 8.0;
//float x = m_twopi * m_pointer_pos;
//float y = m_twopi * m_pointer_pos;
//float A1 = 1.0;
//float f1 = 1.0;
//float A2 = m_mod*10;
//float f2 = 1.0;
//value = sin(y + A2 * sin(x + m_feedback*old_x_value) + old_y_value);
//old_x_value = sin(x);
//old_y_value = sin(y);
//break;
//
//}
//
//
//
//}
//
//
//if (m_wavetype < 10) {
//
//m_pointer_pos += m_pitchbend* m_freq * m_oneOverSr;
//m_pointer_pos = _clip(m_pointer_pos);
//fixed_pulse_counter += 11000 * m_oneOverSr;
////fixed_pulse_counter = _clip(fixed_pulse_counter);
//
//}
//
