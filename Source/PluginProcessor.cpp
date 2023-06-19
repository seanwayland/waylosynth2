
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include<iostream>
#include<cstdlib>
#include<ctime>

static const int numberOfVoices = 10;

//==============================================================================
MySynthesiserVoice::MySynthesiserVoice() {
    oscillator.setup(getSampleRate());
    envelope.setSampleRate(getSampleRate());

    
}

bool MySynthesiserVoice::canPlaySound(SynthesiserSound *sound) {
    return dynamic_cast<MySynthesiserSound *> (sound) != nullptr;
}

void MySynthesiserVoice::startNote(int midiNoteNumber, float velocity,
                                   SynthesiserSound *, int currentPitchWheelPosition) {
    oscillator.reset();
    level = velocity * 0.15;
    envelope.noteOn();
    auto m_freq = (MidiMessage::getMidiNoteInHertz (midiNoteNumber));
    
    // random pitch slop
//    int max;
//    max = 200; //set the upper bound to generate the random number
//    srand(time(0));
//    int pitchchange = rand()%max;
//    float pp = float(pitchchange)/100000.f;
//    float rand_detune = 0.0005 + pp;
//    m_freq = m_freq*(1-rand_detune);
    
    
    oscillator.set_midi_note_number(midiNoteNumber);
    oscillator.setFreq(m_freq);
    oscillator.set_note_velocity(velocity);
    
    oscillator.open_filter_env();
    
    //

    
}

void MySynthesiserVoice::stopNote(float /*velocity*/, bool allowTailOff) {
    envelope.noteOff();
    //oscillator.reset();
    oscillator.gate_filter_env();
    
}


void MySynthesiserVoice::pitchWheelMoved(int value){
    oscillator.setPitchBend(value);

}





void MySynthesiserVoice::renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) {
    while (--numSamples >= 0) {
        
        
        //oscillator.setPitchBend(MidiMessage::getPitchWheelValue());
        auto envAmp = envelope.getNextSample();
        auto thisSample = oscillator.process();
        auto currentSample = thisSample * level * envAmp;
        //vadimFilter.setCutoffFrequency(500);
        //vadimFilter.setCutoffFrequency(2000 + currentSample*1000);
        //currentSample = vadimFilter.processSample(1, currentSample);

        for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
            outputBuffer.addSample(i, startSample, currentSample);

        ++startSample;
        
    

        if (envAmp <= 0.0) {
            clearCurrentNote();
            break;
        }
    }
}

void MySynthesiserVoice::setEnvelopeParameters(ADSR::Parameters params) {
    envelope.setParameters(params);
}

void MySynthesiserVoice::setWavetypeParameter(int type) {
    oscillator.setWavetype(type);
}

void MySynthesiserVoice::setSharpParameter(float sharp) {
    
    // random  slop
//    int mm;
//    mm = 500; //set the upper bound to generate the random number
//    srand(time(0));
//    int rr = rand()%mm;
//    float pp = float(rr)/100000.f;
    oscillator.setSharp(sharp);
}

void MySynthesiserVoice::setModParameter(float mod) {
    
    
    // random  slop
//    int mmm;
//    mmm = 500; //set the upper bound to generate the random number
//    srand(time(0));
//    int rrr = rand()%mmm;
//    float ppp = float(rrr)/100000.f;
    oscillator.setMod(mod);
}

void MySynthesiserVoice::setAttackRateParameter(float attackRate) {
    oscillator.setAttackRate(attackRate);
}

void MySynthesiserVoice::setAttackShapeParameter(float attackShape) {
    oscillator.setAttackshape(attackShape);
}

void MySynthesiserVoice::setFilterVelocityParameter(float filterVelocity) {
    oscillator.setFilterVelocity(filterVelocity);
}

void MySynthesiserVoice::setGreaseVelocityParameter(float GreaseVelocity) {
    oscillator.setGreaseVelocity(GreaseVelocity);
}

void MySynthesiserVoice::setGreaseKeyboardParameter(float GreaseKeyboard) {
    oscillator.setGreaseKeyboard(GreaseKeyboard);
}

void MySynthesiserVoice::setGravyKeyboardParameter(float GravyKeyboard) {
    oscillator.setGravyKeyboard(GravyKeyboard);
}

void MySynthesiserVoice::setGravyVelocityParameter(float GravyVelocity) {
    oscillator.setGravyVelocity(GravyVelocity);
}

void MySynthesiserVoice::setFilterAmountParameter(float filterAmount) {
    oscillator.setFilterAmount(filterAmount);
}

void MySynthesiserVoice::setFilterSustainParameter(float filterSustain) {
    oscillator.setFilterSustain(filterSustain);
}

void MySynthesiserVoice::setFilterAttackParameter(float filterAttack) {
    oscillator.setFilterAttack(filterAttack);
}

void MySynthesiserVoice::setFilterAttackShapeParameter(float filterAttackShape) {
    oscillator.setFilterAttackShape(filterAttackShape);
}
//
//
void MySynthesiserVoice::setFilterDecayShapeParameter(float filterDecayShape) {
    oscillator.setFilterDecayShape(filterDecayShape);
}
void MySynthesiserVoice::setFilterDecayParameter(float filterdecay) {
    oscillator.setFilterDecay(filterdecay);
}

void MySynthesiserVoice::setFilterReleaseParameter(float filterRelease) {
    oscillator.setFilterRelease(filterRelease);
}

void MySynthesiserVoice::setFilterFMParameter(float filterFM) {
    oscillator.setFilterFM(filterFM);
}

void MySynthesiserVoice::setFilterFMVelocityParameter(float filterFMVelocity) {
    oscillator.setFilterFMVelocity(filterFMVelocity);
}

void MySynthesiserVoice::setCutoffKeyboardParameter(float CutoffKeyboard) {
    oscillator.setCutoffKeyboard(CutoffKeyboard);
}


void MySynthesiserVoice::setCutoffParameter(float cutoff) {
    
    
    // random pitch slop
//    int max;
//    max = 200; //set the upper bound to generate the random number
//    srand(time(0));
//    int pitchchange = rand()%max;
//    float pp = float(pitchchange)/100000.f;
//    float rand_detune = 0.0005 + pp;
//    m_freq = m_freq*(1-rand_detune);
    
//    int mmmm;
//    mmmm = 500; //set the upper bound to generate the random number
//    srand(time(0));
//    int rrrr = rand()%mmmm;
//    float pppp = float(rrrr)/100000.f;
    
    oscillator.setCutoff(cutoff);
}

void MySynthesiserVoice::setResParameter(float resonance) {
    oscillator.setRes(resonance);
}

//void MySynthesiserVoice::setBassoffParameter(float bassoff) {
//    oscillator.setBassoff(bassoff);
//}

void MySynthesiserVoice::setDetuneParameter(float detune) {
    oscillator.setDetune(detune);
}

//==============================================================================
void MySynthesiser::setEnvelopeParameters(ADSR::Parameters params) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setEnvelopeParameters(params);
}

void MySynthesiser::setWavetypeParameter(int type) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setWavetypeParameter(type);
}

void MySynthesiser::setSharpParameter(float sharp) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setSharpParameter(sharp);
}

void MySynthesiser::setModParameter(float mod) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setModParameter(mod);
}

void MySynthesiser::setAttackRateParameter(float attackRate) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setAttackRateParameter(attackRate);
}

void MySynthesiser::setAttackShapeParameter(float attackShape) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setAttackShapeParameter(attackShape);
}

void MySynthesiser::setFilterVelocityParameter(float filterVelocity) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setFilterVelocityParameter(filterVelocity);
}

void MySynthesiser::setGreaseVelocityParameter(float GreaseVelocity) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setGreaseVelocityParameter(GreaseVelocity);
}

void MySynthesiser::setGravyVelocityParameter(float GravyVelocity) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setGravyVelocityParameter(GravyVelocity);
}

void MySynthesiser::setGreaseKeyboardParameter(float GreaseKeyboard) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setGreaseKeyboardParameter(GreaseKeyboard);
}

void MySynthesiser::setGravyKeyboardParameter(float GravyKeyboard) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setGravyKeyboardParameter(GravyKeyboard);
}


void MySynthesiser::setFilterReleaseParameter(float filterRelease) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setFilterReleaseParameter(filterRelease);
}

void MySynthesiser::setFilterAmountParameter(float filterAmount) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setFilterAmountParameter(filterAmount);
}

void MySynthesiser::setFilterSustainParameter(float filterSustain) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setFilterSustainParameter(filterSustain);
}

void MySynthesiser::setFilterAttackParameter(float filterAttack) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setFilterAttackParameter(filterAttack);
}

void MySynthesiser::setFilterAttackShapeParameter(float filterAttackShape) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setFilterAttackShapeParameter(filterAttackShape);
}
//
void MySynthesiser::setFilterDecayParameter(float filterDecay) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setFilterDecayParameter(filterDecay);
}

void MySynthesiser::setFilterDecayShapeParameter(float filterDecayShape) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setFilterDecayShapeParameter(filterDecayShape);
}




void MySynthesiser::setCutoffParameter(float cutoff) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setCutoffParameter(cutoff);
}

void MySynthesiser::setCutoffKeyboardParameter(float CutoffKeyboard) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setCutoffKeyboardParameter(CutoffKeyboard);
}

void MySynthesiser::setResParameter(float resonance) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setResParameter(resonance);
}

//void MySynthesiser::setBassoffParameter(float bassoff) {
//    for (int i = 0; i < getNumVoices(); i++)
//       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setBassoffParameter(bassoff);
//}

void MySynthesiser::setDetuneParameter(float detune) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setDetuneParameter(detune);
}

void MySynthesiser::setFilterFMParameter(float FilterFM) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setFilterFMParameter(FilterFM);
}

void MySynthesiser::setFilterFMVelocityParameter(float FilterFMVelocity) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setFilterFMVelocityParameter(FilterFMVelocity);
}



//==============================================================================
static String secondSliderValueToText(float value) {
    return String(value, 3) + String(" sec");
}

static float secondSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String sharpSliderValueToText(float value) {
    return String(value, 4) + String(" x");
}

static float sharpSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static float modSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String modSliderValueToText(float value) {
    return String(value, 4) + String(" x");
}


static String cutoffSliderValueToText(float value) {
    return String(value, 4) + String(" x");
}

static float cutoffSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String resonanceSliderValueToText(float value) {
    return String(value, 4) + String(" x");
}

static float resonanceSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

//static String bassoffSliderValueToText(float value) {
//    return String(value, 4) + String(" x");
//}

//static float bassoffSliderTextToValue(const String& text) {
//    return text.getFloatValue();
//}


static String detuneSliderValueToText(float value) {
    return String(value, 4) + String(" x");
}

static float detuneSliderTextToValue(const String& text) {
    return text.getFloatValue();
}




static String gainSliderValueToText(float value) {
    float val = 20.0f * log10f(jmax(0.001f, value));
    return String(val, 2) + String(" dB");
}

static float gainSliderTextToValue(const String& text) {
    float val = jlimit(-60.0f, 18.0f, text.getFloatValue());
    return powf(10.0f, val * 0.05f);
}

static String filtAttackSliderValueToText(float value) {
    return String(value, 4) + String(" x");
}

static float filtAttackSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String filtDecaySliderValueToText(float value) {
    return String(value, 4) + String(" x");
}

static float filtDecaySliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String filtAttackShapeSliderValueToText(float value) {
    return String(value, 4) + String(" x");
}

static float filtAttackShapeSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String filtDecayShapeSliderValueToText(float value) {
    return String(value, 4) + String(" x");
}

static float filtDecayShapeSliderTextToValue(const String& text) {
    return text.getFloatValue();
}


static String filtSustainSliderValueToText(float value) {
    return String(value, 4) + String(" x");
}

static float filtSustainSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String filtReleaseSliderValueToText(float value) {
    return String(value, 4) + String(" x");
}

static float filtReleaseSliderTextToValue(const String& text) {
    return text.getFloatValue();
}



AudioProcessorValueTreeState::ParameterLayout createParameterLayout() {
    using Parameter = AudioProcessorValueTreeState::Parameter;

    std::vector<std::unique_ptr<Parameter>> parameters;

    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("attack"),1), String("Attack"), String(),
                                                     NormalisableRange<float>(0.001f, 1.f, 0.001f, 0.5f),
                                                     0.005f, secondSliderValueToText, secondSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("attackRate"),1), String("AttackRate"), String(),
                                                     NormalisableRange<float>(0.001f, 1.f, 0.0001f, 0.5f),
                                                     0.01f, secondSliderValueToText, secondSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("attackShape"),1), String("AttackShape"), String(),
                                                     NormalisableRange<float>(0.001f, 1.f, 0.0001f, 0.5f),
                                                     0.75f, secondSliderValueToText, secondSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("decay"),1), String("Decay"), String(),
                                                     NormalisableRange<float>(0.001f, 10.f, 0.001f, 0.5f),
                                                     0.2f, secondSliderValueToText, secondSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("sustain"),1), String("Sustain"), String(),
                                                     NormalisableRange<float>(0.001f, 1.f, 0.001f, 0.3f),
                                                     0.708f, gainSliderValueToText, gainSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("release"),1), String("Release"), String(),
                                                     NormalisableRange<float>(0.001f, 1.f, 0.001f, 0.5f),
                                                     1.0f, secondSliderValueToText, secondSliderTextToValue));
    
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("detune"),1), String("Detune"), String(),
                                                     NormalisableRange<float>(0.5f, 2.f, 0.0001f, 1.0f),
                                                     1.0f, detuneSliderValueToText, detuneSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("type"),1), String("Type"), String(),
                                                     NormalisableRange<float>(0.0f, 19.0f, 1.f, 1.0f),
                                                     0.0f, nullptr, nullptr));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("space"),1), String("Space"), String(),
                                                     NormalisableRange<float>(0.0f, 4.0f, 1.f, 1.0f),
                                                     0.0f, nullptr, nullptr));

    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("sharp"),1), String("Sharp"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.1f, sharpSliderValueToText, sharpSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("mod"),1), String("Mod"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.1f, modSliderValueToText, modSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("greaseMod"),1), String("GreaseMod"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.1f, modSliderValueToText, modSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("cutoff"),1), String("Cutoff"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, cutoffSliderValueToText, cutoffSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("cutoffMod"),1), String("CutoffMod"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, modSliderValueToText, modSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("resonance"),1), String("Resonance"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.05f, resonanceSliderValueToText, resonanceSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("bassoff"),1), String("Bassoff"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.05f, resonanceSliderValueToText, resonanceSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("gain"),1), String("Gain"), String(),
                                                     NormalisableRange<float>(0.001f, 7.94f, 0.001f, 0.3f),
                                                     1.0f, gainSliderValueToText, gainSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("filtVelocity"),1), String("FilterVelocity"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtAttackSliderValueToText, filtAttackSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("filtAmount"),1), String("FilterAmount"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtAttackSliderValueToText, filtAttackSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("filtAttack"),1), String("FilterAttack"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtAttackSliderValueToText, filtAttackSliderTextToValue));
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("filtSustain"),1), String("FilterSustain"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtAttackSliderValueToText, filtAttackSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("filtAttackShape"),1), String("FilterAttackShape"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtAttackSliderValueToText, filtAttackSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("filtDecay"),1), String("FilterDecay"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtAttackSliderValueToText, filtAttackSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("filtDecayShape"),1), String("FilterDecayShape"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtDecaySliderValueToText, filtDecaySliderTextToValue));
    
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("filtRelease"),1), String("FilterRelease"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtReleaseSliderValueToText, filtReleaseSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("greaseAttack"),1), String("GreaseAttack"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtAttackSliderValueToText, filtAttackSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("greaseAttackShape"),1), String("greaseAttackShape"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtAttackSliderValueToText, filtAttackSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("greaseDecay"),1), String("greaseDecay"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtAttackSliderValueToText, filtAttackSliderTextToValue));
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("greaseDecayShape"),1), String("greaseDecayShape"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtDecaySliderValueToText, filtDecaySliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("greaseSustain"),1), String("greaseSustain"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtSustainSliderValueToText, filtSustainSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("greaseRelease"),1), String("greaseRelease"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtReleaseSliderValueToText, filtReleaseSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("greaseVelocity"),1), String("greaseVelocity"), String(),
                                                     NormalisableRange<float>(-1.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtAttackSliderValueToText, filtAttackSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("greaseKeyboard"),1), String("greaseKeyboard"), String(),
                                                     NormalisableRange<float>(-1.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtAttackSliderValueToText, filtAttackSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("gravyVelocity"),1), String("gravyVelocity"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtAttackSliderValueToText, filtAttackSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("gravyKeyboard"),1), String("gravyKeyboard"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtAttackSliderValueToText, filtAttackSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("cutoffVelocity"),1), String("cutoffVelocity"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtAttackSliderValueToText, filtAttackSliderTextToValue));
    
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("cutoffKeyboard"),1), String("cutoffKeyboard"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtAttackSliderValueToText, filtAttackSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("filtFMVelocity"),1), String("filtFMVelocity"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtAttackSliderValueToText, filtAttackSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(ParameterID(String("filtFM"),1), String("filtFM"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.0001f, 0.5f),
                                                     0.3f, filtAttackSliderValueToText, filtAttackSliderTextToValue));
    
    

    return { parameters.begin(), parameters.end() };
}

//==============================================================================
waylosynth2::waylosynth2()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), tree(*this, nullptr),
parameters (*this, nullptr, Identifier(JucePlugin_Name), createParameterLayout())
//lowPassFilter(dsp::IIR::Coefficients<float>::makeLowPass(96000, 7000.0f, 0.1))
     

// lowPassFilterLeft  (juce::dsp::IIR::Coefficients<float>::makeLowPass  (getSampleRate(), 17000.0f)),
// lowPassFilterRight (juce::dsp::IIR::Coefficients<float>::makeLowPass  (getSampleRate(), 17000.0f)),

#endif
//lowPassFilter(*this, nullptr, dsp::IIR::Coefficients<float>::makeLowPass(96000, 10000.0f, 0.1f))
{

    for (auto i = 0; i < numberOfVoices; ++i)
        synthesiser.addVoice(new MySynthesiserVoice());

    synthesiser.addSound(new MySynthesiserSound());

    attackParameter = parameters.getRawParameterValue("attack");
    attackRateParameter = parameters.getRawParameterValue("attackRate");
    attackShapeParameter = parameters.getRawParameterValue("attackShape");
    decayParameter = parameters.getRawParameterValue("decay");
    sustainParameter = parameters.getRawParameterValue("sustain");
    releaseParameter = parameters.getRawParameterValue("release");
    typeParameter = parameters.getRawParameterValue("type");
    spaceParameter = parameters.getRawParameterValue("space");
    sharpParameter = parameters.getRawParameterValue("sharp");
    modParameter = parameters.getRawParameterValue("mod");
    greaseModParameter = parameters.getRawParameterValue("greaseMod");
    cutoffParameter = parameters.getRawParameterValue("cutoff");
    cutoffModParameter = parameters.getRawParameterValue("cutoffMod");
    resonanceParameter = parameters.getRawParameterValue("resonance");
    bassoffParameter = parameters.getRawParameterValue("bassoff");
    gainParameter = parameters.getRawParameterValue("gain");
    detuneParameter = parameters.getRawParameterValue("detune");
    filtVelocityParameter = parameters.getRawParameterValue("filtVelocity");
    filtAmountParameter = parameters.getRawParameterValue("filtAmount");
    filtAttackParameter = parameters.getRawParameterValue("filtAttack");
    filtAttackShapeParameter = parameters.getRawParameterValue("filtAttackShape");
    filtDecayParameter = parameters.getRawParameterValue("filtDecay");
    filtDecayShapeParameter = parameters.getRawParameterValue("filtDecayShape");
    filtSustainParameter = parameters.getRawParameterValue("filtSustain");
    filtReleaseParameter = parameters.getRawParameterValue("filtRelease");
    greaseAttackParameter = parameters.getRawParameterValue("greaseAttack");
    greaseAttackShapeParameter = parameters.getRawParameterValue("greaseAttackShape");
    greaseDecayParameter = parameters.getRawParameterValue("greaseDecay");
    greaseDecayShapeParameter = parameters.getRawParameterValue("greaseDecaykShape");
    greaseSustainParameter = parameters.getRawParameterValue("greaseSustain");
    greaseReleaseParameter = parameters.getRawParameterValue("greaseRelease");
    greaseKeyboardParameter = parameters.getRawParameterValue("greaseKeyboard");
    greaseVelocityParameter = parameters.getRawParameterValue("greaseVelocity");
    gravyKeyboardParameter = parameters.getRawParameterValue("gravyKeyboard");
    gravyVelocityParameter = parameters.getRawParameterValue("gravyVelocity");
    cutoffKeyboardParameter = parameters.getRawParameterValue("cutoffKeyboard");
    cutoffVelocityParameter = parameters.getRawParameterValue("cutoffVelocity");
    filtFMParameter = parameters.getRawParameterValue("filtFM");
    filtFMVelocityParameter = parameters.getRawParameterValue("filtFMVelocity");
    
    
}

waylosynth2::~waylosynth2()
{
}

//==============================================================================
const String waylosynth2::getName() const
{
    return JucePlugin_Name;
}

bool waylosynth2::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool waylosynth2::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool waylosynth2::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double waylosynth2::getTailLengthSeconds() const
{
    return 0.0;
}

int waylosynth2::getNumPrograms()
{
return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int waylosynth2::getCurrentProgram()
{
    return 0;
}

void waylosynth2::setCurrentProgram (int index)
{
}

const String waylosynth2::getProgramName (int index)
{
    return {};
}

void waylosynth2::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void waylosynth2::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    keyboardState.reset();
    synthesiser.setCurrentPlaybackSampleRate(sampleRate);
    
    for ( int j = 0 ; j < 127; j++){
        playing[j] = 0;
    }
    
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
//    lowPassFilter.prepare(spec);
//    lowPassFilter.reset();
//
//    ladderFilter.reset();
//    ladderFilter.prepare(spec);
//    ladderFilter.setEnabled(true);

    
    
    

}

void waylosynth2::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    keyboardState.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool waylosynth2::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void waylosynth2::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    if((int)*spaceParameter == 1){
        
        //
        //     //waylosynth code
        //
            MidiMessage m;
            MidiBuffer processedMidi;
            //int time;
        
            {
                    buffer.clear();
        
        
                    MidiBuffer processedMidi;
                    int time;
                    MidiMessage m;
        
                    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
                    {
                        if (m.isNoteOn() && m.getNoteNumber() < 60 )
        
        
                            {
                                waylotrans = m.getNoteNumber() - 48;
                                m = MidiMessage::noteOff(m.getChannel(), m.getNoteNumber(), m.getVelocity());
        
                            }
        
        
                        else if (m.isNoteOff() && m.getNoteNumber() < 60)
        
        
                            {
                                waylotrans = 0;
                                m = MidiMessage::noteOff(m.getChannel(), m.getNoteNumber(), m.getVelocity());
                            }
        
                        else if (m.isNoteOn() && m.getNoteNumber() >= 60)
        
                            {
                                int NewNote = m.getNoteNumber() + waylotrans -12;
                                playing[m.getNoteNumber()]= NewNote;
                                m = MidiMessage::noteOn(m.getChannel(), NewNote , m.getVelocity());
        
                            }
                        else if (m.isNoteOff() && m.getNoteNumber() >= 60)
        
                        {
                            int NewNote = playing[m.getNoteNumber()];
                             playing[m.getNoteNumber()] = NULL;
                            m = MidiMessage::noteOff(m.getChannel(), NewNote , m.getVelocity());
        
                        }
        
        
                        else if (m.isAftertouch())
                        {
                        }
                        else if (m.isPitchWheel())
                        {
                        }
        
                        processedMidi.addEvent (m, time);
                    }
        
                    midiMessages.swapWith (processedMidi);
                }
        
    }
    
    // end waylosynth code
    
    
    // zawinul reverse
    if((int)*spaceParameter == 3){
        
            MidiMessage m;
                MidiMessage n;
                buffer.clear();
        
        
        
                MidiBuffer processedMidi;
                int time;
                for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
                {
                    if (m.isNoteOn())
                    {
        
        
                        int note = m.getNoteNumber();
                        if (note<60)
                        {
                            n = MidiMessage::noteOn(m.getChannel(), 60 + ( 60 - note ) , m.getVelocity());
                            processedMidi.addEvent(n, time);
        
                        }
                        else
                        {
                            n = MidiMessage::noteOn(m.getChannel(), 60 - ( note - 60) , m.getVelocity());
                            processedMidi.addEvent(n, time);
        
                        }
        
                   }
                   else if (m.isNoteOff()) {
        
        
                        int note = m.getNoteNumber();
                        if (note<60)
                        {
                            n = MidiMessage::noteOff(m.getChannel(), 60 + ( 60 - note ), m.getVelocity());
                            processedMidi.addEvent(n, time);
        
                        }
                        else
                        {
                            n = MidiMessage::noteOff(m.getChannel(), 60 - ( note - 60) , m.getVelocity());
                            processedMidi.addEvent(n, time);
        
                        }
        
        
                    }
        
                   else if (m.isAftertouch())
                    {
                    }
                    else if (m.isPitchWheel())
                    {
                    }
        
                }
        
                midiMessages.swapWith  (processedMidi) ;
    }
    
    
    //// end of zawinul reverse
    ///


    
//    //midi latch function
    
//
//    if((int)*spaceParameter == 4){
//
//            MidiMessage m;
//                MidiMessage n;
//                MidiBuffer processedMidi;
//                int time;
//                for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
//                {
//                    if (m.isNoteOn())
//                    {
//                        // note off for any playing notes
//                        for ( int j = 0 ; j < 127; j++)
//                        { if (playing[j] == 1) {
//                            n = MidiMessage::noteOff(m.getChannel(), j);
//                            processedMidi.addEvent(n, time);
//                            playing[j] = 0;
//                        }
//                        }
//                    }
//                    else if (m.isNoteOff()) {
//
//                        int note = m.getNoteNumber();
//                        // if a note is not playing send a note on and set it to "playing"
//                        if (playing[note] == 0){
//                            if (m.getNoteNumber() != 84){
//                                n = MidiMessage::noteOn(m.getChannel(), note, 127.0f);
//                                processedMidi.addEvent(n, time);
//                                playing[note] = 1;
//
//                            }
//                            else{
//                                playing[84] = 0;
//                            }
//                        }
//                    }
//
//                    else if (m.isAftertouch())
//                    {
//                    }
//                    else if (m.isPitchWheel())
//                    {
//                    }
//
//                }
//                midiMessages.swapWith  (processedMidi) ;
//    }
    
    
     //end of midi latch function
    
            // transpose up a 5th
    
//            MidiMessage m;
//            MidiMessage n;
//
//            MidiBuffer processedMidi;
//             int keyboard_transpo = 7;
//            int time;
//            for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
//            {
//                int note = m.getNoteNumber();
//                if (m.isNoteOn())
//                {
//                
//                n = MidiMessage::noteOn(m.getChannel(), note + keyboard_transpo , m.getVelocity());
//                processedMidi.addEvent(n, time);
//                
//                }
//                else if (m.isNoteOff()) {
//                    
//                    n = MidiMessage::noteOff(m.getChannel(), note + keyboard_transpo , m.getVelocity());
//                    processedMidi.addEvent(n, time);
//                }
//    
//                else if (m.isAftertouch())
//                {
//                }
//                else if (m.isPitchWheel())
//                {
//                }
//            }
//            midiMessages.swapWith  (processedMidi) ;
//        
        
         //end of midi latch function
    
    
    // WAYLO CHILI FUNCTION
//
    if((int)*spaceParameter == 2){
            MidiMessage m;
        
                {
        
                    MidiBuffer processedMidi;
                    int time;
                    MidiMessage m;
        
                    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
                    {
        
        
                        if (waylochili > 80)
                        {
                            waylochili = 48;
                        }
        
                        if (waylochili < 30)
                        {
                            waylochili = 48;
                        }
        
        
                        if (m.isNoteOn() && m.getNoteNumber() < 37 )
        
        
                        {
                            waylochili = m.getNoteNumber() + 24 ;
                            m = MidiMessage::noteOff(m.getChannel(), m.getNoteNumber(), m.getVelocity());
        
                        }
        
        
                        else if (m.isNoteOff() && m.getNoteNumber() < 37  )
        
        
                        {
                            waylotrans = 0;
                            m = MidiMessage::noteOff(m.getChannel(), m.getNoteNumber(), m.getVelocity());
                        }
        
                        else if (m.isNoteOn() && m.getNoteNumber() >= 37)
        
                        {
                            waylochili = waylochili + m.getNoteNumber() - 60;
                            int NewNote = waylochili + waylotrans ;
                            playing[m.getNoteNumber()]= NewNote;
        
                            m = MidiMessage::noteOn(m.getChannel(), NewNote , m.getVelocity());
        
                        }
                        else if (m.isNoteOff() && m.getNoteNumber() >= 37)
        
                        {
                            int NewNote = playing[m.getNoteNumber()];
                            playing[m.getNoteNumber()] = NULL;
                            m = MidiMessage::noteOff(m.getChannel(), NewNote , m.getVelocity());
        
                        }
        
        
                        else if (m.isAftertouch())
                        {
                        }
                        else if (m.isPitchWheel())
                        {
                        }
        
                        processedMidi.addEvent (m, time);
                    }
        
                    midiMessages.swapWith (processedMidi);
                }
    }
    
    
    // WAYLO CHILI END
    
    
    
    // octave transpose keyboard
//
//    MidiMessage m;
//
//        {
//
//
//            MidiBuffer processedMidi;
//            int time;
//            MidiMessage m;
//
//            for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
//            {
//
//
//
//
//
//                if (m.isNoteOn() && m.getNoteNumber() < 60 )
//
//
//                {
//
//                    m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber() + 12, m.getVelocity());
//                    playing[m.getNoteNumber() + 12 ] = 1;
//
//                }
//
//
//                else if (m.isNoteOff() && m.getNoteNumber() < 60  )
//
//
//                {
//                    m = MidiMessage::noteOff(m.getChannel(), m.getNoteNumber() + 12 , m.getVelocity());
//                    playing[m.getNoteNumber() +12 ] = 0;
//                }
//
//                else if (m.isNoteOn() && m.getNoteNumber() >= 60)
//
//                {
//
//
//                    m = MidiMessage::noteOn(m.getChannel(),  m.getNoteNumber() - 24 , m.getVelocity());
//
//                }
//                else if (m.isNoteOff() && m.getNoteNumber() >= 60)
//
//                {
//                    if (playing[m.getNoteNumber()] == 1){}
//                    else {m = MidiMessage::noteOff(m.getChannel(), m.getNoteNumber() - 24, m.getVelocity());}
//
//                }
//
//
//
//
//                else if (m.isAftertouch())
//                {
//                }
//                else if (m.isPitchWheel())
//                {
//                }
//
//                processedMidi.addEvent (m, time);
//            }
//
//            midiMessages.swapWith (processedMidi);
//        }
//
    
    // RETRANSPOSE END
    

    

    keyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);
    

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    synthesiser.setEnvelopeParameters(ADSR::Parameters {*attackParameter, *decayParameter, *sustainParameter, *releaseParameter});
    synthesiser.setWavetypeParameter((int)*typeParameter);
    //synthesiser.setSpacetypeParameter((int)*spaceParameter);
    synthesiser.setSharpParameter(*sharpParameter);
    synthesiser.setModParameter(*modParameter);
    synthesiser.setAttackRateParameter(*attackRateParameter);
    synthesiser.setAttackShapeParameter(*attackShapeParameter);
    synthesiser.setFilterVelocityParameter(*filtVelocityParameter);
    synthesiser.setGreaseVelocityParameter(*greaseVelocityParameter);
    synthesiser.setGreaseKeyboardParameter(*greaseKeyboardParameter);
    synthesiser.setGravyVelocityParameter(*gravyVelocityParameter);
    synthesiser.setGravyKeyboardParameter(*gravyKeyboardParameter);
    synthesiser.setFilterAmountParameter(*filtAmountParameter);
    synthesiser.setFilterAttackParameter(*filtAttackParameter);
    synthesiser.setFilterFMParameter(*filtFMParameter);
    synthesiser.setFilterFMVelocityParameter(*filtFMVelocityParameter);
    synthesiser.setFilterSustainParameter(*filtSustainParameter);
    synthesiser.setFilterAttackShapeParameter(*filtAttackShapeParameter);
    synthesiser.setFilterReleaseParameter(*filtReleaseParameter);
    synthesiser.setFilterDecayParameter(*filtDecayParameter);
    synthesiser.setFilterDecayShapeParameter(*filtDecayShapeParameter);
    synthesiser.setCutoffParameter(*cutoffParameter);
    synthesiser.setCutoffKeyboardParameter(*cutoffKeyboardParameter);
    synthesiser.setResParameter(*resonanceParameter);
    //synthesiser.setBassoffParameter(*bassoffParameter);
    synthesiser.setDetuneParameter(*detuneParameter);
    synthesiser.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    buffer.applyGainRamp(0, buffer.getNumSamples(), lastGain, *gainParameter);
    
    
    // IIR filter set at 10000
    //dsp::AudioBlock<float> block (buffer);
    

    //lowPassFilter.process(dsp::ProcessContextReplacing<float> (block));
   
    //ladderFilter.process(dsp::ProcessContextReplacing<float> (block));
    
//    //ladderFilter.setMode(juce::dsp::LadderFilter<float>::Mode::LPF24);
//    ladderFilter.setMode(juce::dsp::LadderFilter<float>::Mode::LPF12);
//    ladderFilter.setCutoffFrequencyHz(4000.0f);
//    ladderFilter.setResonance(0.2f);
//    ladderFilter.process(dsp::ProcessContextReplacing<float> (block));

    
    
    
    // average value with last sampling anti aliasing
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        //input data
        const float* inputData = buffer.getReadPointer(channel);

        float* outputData = buffer.getWritePointer(channel);
        
        //place audio samples into buffer
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            //get current value from read pointer
            float inputSample = inputData[sample];
            float returnval = (inputSample + lastSample[channel])/2.0f;
            outputData[sample] = returnval;
            lastSample[channel] = returnval;
            

        }
    }
    

    
    

    lastGain = *gainParameter;
}

//==============================================================================
bool waylosynth2::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* waylosynth2::createEditor()
{
    return new waylosynth2AudioProcessorEditor (*this, parameters);
}

//==============================================================================
void waylosynth2::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void waylosynth2::setStateInformation (const void* data, int sizeInBytes) 
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (juce::ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new waylosynth2();
}
