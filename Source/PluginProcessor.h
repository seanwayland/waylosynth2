

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
    void setFilterTypeParameter(int filterType);
    void setSharpParameter(float sharp);
    void setModParameter(float mod);
    void setAttackRateParameter(float attackRate);
    void setAttackShapeParameter(float attackShape);
    void setFilterVelocityParameter(float filterVelocity);
    void setGreaseVelocityParameter(float greaseVelocity);
    void setGreaseKeyboardParameter(float greaseKeyboard);
    void setGravyVelocityParameter(float GravyVelocity);
    void setGravyKeyboardParameter(float GravyKeyboard);
    void setFilterAmountParameter(float filterAmount);
    void setFilterAttackParameter(float filterAttack);
    void setFilterAttackShapeParameter(float filterAttackShape);
    void setFilterDecayParameter(float filterDecay);
    void setFilterDecayShapeParameter(float filterDecayShape);
    void setFilterSustainParameter(float filterSustain);
    void setFilterReleaseParameter(float filterRelease);
    void setFilterFMParameter(float filterFM);
    void setFilterFMVelocityParameter(float filterFMVelocity);
    void setCutoffParameter(float cutoff);
    void setCutoffKeyboardParameter(float cutoffKeyboard);
    void setResParameter(float resonance);
    void setBassoffParameter(float bassoff);
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
    void setFilterTypeParameter(int filterType);
    void setSpacetypeParameter(int type);
    void setSharpParameter(float sharp);
    void setModParameter(float mod);
    void setAttackRateParameter(float attackRate);
    void setAttackShapeParameter(float attackshape);
    void setFilterVelocityParameter(float filterVelocity);
    void setGreaseVelocityParameter(float greaseVelocity);
    void setGreaseKeyboardParameter(float greaseKeyboard);
    void setGravyVelocityParameter(float GravyVelocity);
    void setGravyKeyboardParameter(float GravyKeyboard);
    void setFilterAmountParameter(float filterAmount);
    void setFilterAttackParameter(float filterAttack);
    void setFilterAttackShapeParameter(float filterAttackShape);
    void setFilterDecayParameter(float filterDecay);
    void setFilterFMParameter(float filterFM);
    void setFilterFMVelocityParameter(float filterFMVelocity);
    void setFilterDecayShapeParameter(float filterDecayShape);
    void setFilterSustainParameter(float filterSustain);
    void setFilterReleaseParameter(float filterRelease);
    void setCutoffParameter(float cutoff);
    void setCutoffKeyboardParameter(float cutoffKeyboard);
    void setResParameter(float resonance);
    void setBassoffParameter(float bassoff);
    void setDetuneParameter(float detune);
};

//==============================================================================
class waylosynth2  : public AudioProcessor
{
public:
    //==============================================================================
    waylosynth2();
    ~waylosynth2();
    
    AudioProcessorValueTreeState tree;
    
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
    
    //juce::dsp::StateVariableTPTFilter<float> vadimFilter ;
    


    MidiKeyboardState keyboardState;

private:
    //==============================================================================
    AudioProcessorValueTreeState parameters;

    MySynthesiser synthesiser;

    std::atomic<float> *attackParameter = nullptr;
    std::atomic<float> *attackRateParameter = nullptr;
    std::atomic<float> *attackShapeParameter = nullptr;
    std::atomic<float> *decayParameter = nullptr;
    std::atomic<float> *sustainParameter = nullptr;
    std::atomic<float> *releaseParameter = nullptr;
    std::atomic<float> *detuneParameter = nullptr;
    std::atomic<float> *filterTypeParameter = nullptr;
    std::atomic<float> *typeParameter = nullptr;
    std::atomic<float> *spaceParameter = nullptr;
    std::atomic<float> *sharpParameter = nullptr;
    std::atomic<float> *modParameter = nullptr;
    std::atomic<float> *greaseModParameter = nullptr;
    std::atomic<float> *cutoffParameter = nullptr;
    std::atomic<float> *cutoffModParameter = nullptr;
    std::atomic<float> *resonanceParameter = nullptr;
    std::atomic<float> *bassoffParameter = nullptr;
    std::atomic<float> *gainParameter = nullptr;
    std::atomic<float> *filtVelocityParameter = nullptr;
    std::atomic<float> *filtAmountParameter = nullptr;
    std::atomic<float> *filtAttackParameter = nullptr;
    std::atomic<float> *filtAttackShapeParameter = nullptr;
    std::atomic<float> *filtDecayParameter = nullptr;
    std::atomic<float> *filtDecayShapeParameter = nullptr;
    std::atomic<float> *filtSustainParameter = nullptr;
    std::atomic<float> *filtReleaseParameter = nullptr;
    std::atomic<float> *greaseAttackParameter = nullptr;
    std::atomic<float> *greaseAttackShapeParameter = nullptr;
    std::atomic<float> *greaseDecayParameter = nullptr;
    std::atomic<float> *greaseDecayShapeParameter = nullptr;
    std::atomic<float> *greaseSustainParameter = nullptr;
    std::atomic<float> *greaseReleaseParameter = nullptr;
    std::atomic<float> *greaseVelocityParameter = nullptr;
    std::atomic<float> *greaseKeyboardParameter = nullptr;
    std::atomic<float> *gravyVelocityParameter = nullptr;
    std::atomic<float> *gravyKeyboardParameter = nullptr;
    std::atomic<float> *cutoffVelocityParameter = nullptr;
    std::atomic<float> *cutoffKeyboardParameter = nullptr;
    std::atomic<float> *filtFMVelocityParameter = nullptr;
    std::atomic<float> *filtFMParameter = nullptr;

    
    float lastGain = 0.f;
    float lastSample[2] = { 0.0, 0.0};
    


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (waylosynth2)
};


