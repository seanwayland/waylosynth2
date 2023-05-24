

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
struct MySynthesiserSound   : public SynthesiserSound
{
    MySynthesiserSound() {}
    bool appliesToNote    (int) override        { return true; }
    bool appliesToChannel (int) override        { return true; }
};

//==============================================================================
struct MySynthesiserVoice   : public SynthesiserVoice
{
    MySynthesiserVoice();

    void pitchWheelMoved (int value) override;
    void handleSustainPedal(int midiChannel,bool isDown);
    void controllerMoved (int, int) override {}

    bool canPlaySound (SynthesiserSound *sound) override;

    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound *, int /*currentPitchWheelPosition*/) override;
    void stopNote (float /*velocity*/, bool allowTailOff) override;

    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;

    void setEnvelopeParameters(ADSR::Parameters params);
    void setWavetypeParameter(int type);
    void setSharpParameter(float sharp);
    void setModParameter(float mod);
    void setCutoffParameter(float cutoff);
    void setDetuneParameter(float detune);
    
   
    
    
private:
    Oscillator oscillator;
    ADSR envelope;
    double level = 0.0;
    int voice_number = 0;
    bool sustain_down = 0;
    
    
};

//==============================================================================
class MySynthesiser : public Synthesiser
{
public:
    void setEnvelopeParameters(ADSR::Parameters params);
    void setWavetypeParameter(int type);
    void setSharpParameter(float sharp);
    void setModParameter(float mod);
    void setCutoffParameter(float cutoff);
    void setDetuneParameter(float detune);
};

//==============================================================================
class waylosynth2  : public AudioProcessor
{
public:
    //==============================================================================
    waylosynth2();
    ~waylosynth2();
    
    int waylotrans = 0;
    int playing[127];
    int waylochili = 60;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    juce::dsp::StateVariableTPTFilter<float> vadimFilter ;
    
    

    MidiKeyboardState keyboardState;

private:
    //==============================================================================
    AudioProcessorValueTreeState parameters;

    MySynthesiser synthesiser;

    std::atomic<float> *attackParameter = nullptr;
    std::atomic<float> *decayParameter = nullptr;
    std::atomic<float> *sustainParameter = nullptr;
    std::atomic<float> *releaseParameter = nullptr;
    std::atomic<float> *detuneParameter = nullptr;

    std::atomic<float> *typeParameter = nullptr;
    std::atomic<float> *sharpParameter = nullptr;
    std::atomic<float> *modParameter = nullptr;
    std::atomic<float> *cutoffParameter = nullptr;
    std::atomic<float> *gainParameter = nullptr;
    float lastGain = 0.f;
    


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (waylosynth2)
};
