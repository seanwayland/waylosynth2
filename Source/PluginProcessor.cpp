
#include "PluginProcessor.h"
#include "PluginEditor.h"

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
    oscillator.setFreq(m_freq);
    oscillator.set_note_velocity(velocity);

    
}

void MySynthesiserVoice::stopNote(float /*velocity*/, bool allowTailOff) {
    envelope.noteOff();
    //oscillator.reset();
    
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
    oscillator.setSharp(sharp);
}

void MySynthesiserVoice::setModParameter(float mod) {
    oscillator.setMod(mod);
}

void MySynthesiserVoice::setCutoffParameter(float cutoff) {
    oscillator.setCutoff(cutoff);
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

void MySynthesiser::setCutoffParameter(float cutoff) {
    for (int i = 0; i < getNumVoices(); i++)
       dynamic_cast<MySynthesiserVoice *> (getVoice(i))->setCutoffParameter(cutoff);
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


static String cutoffSliderValueToText(float value) {
    return String(value, 4) + String(" x");
}

static float cutoffSliderTextToValue(const String& text) {
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

AudioProcessorValueTreeState::ParameterLayout createParameterLayout() {
    using Parameter = AudioProcessorValueTreeState::Parameter;

    std::vector<std::unique_ptr<Parameter>> parameters;

    parameters.push_back(std::make_unique<Parameter>(String("attack"), String("Attack"), String(),
                                                     NormalisableRange<float>(0.001f, 1.f, 0.001f, 0.5f),
                                                     0.005f, secondSliderValueToText, secondSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("decay"), String("Decay"), String(),
                                                     NormalisableRange<float>(0.001f, 1.f, 0.001f, 0.5f),
                                                     0.2f, secondSliderValueToText, secondSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("sustain"), String("Sustain"), String(),
                                                     NormalisableRange<float>(0.001f, 1.f, 0.001f, 0.3f),
                                                     0.708f, gainSliderValueToText, gainSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("release"), String("Release"), String(),
                                                     NormalisableRange<float>(0.001f, 1.f, 0.001f, 0.5f),
                                                     0.25f, secondSliderValueToText, secondSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("type"), String("Type"), String(),
                                                     NormalisableRange<float>(0.0f, 19.0f, 1.f, 1.0f),
                                                     0.0f, nullptr, nullptr));

    parameters.push_back(std::make_unique<Parameter>(String("sharp"), String("Sharp"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.001f, 0.5f),
                                                     0.5f, sharpSliderValueToText, sharpSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(String("mod"), String("Mod"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.001f, 0.5f),
                                                     0.5f, sharpSliderValueToText, sharpSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(String("cutoff"), String("Cutoff"), String(),
                                                     NormalisableRange<float>(0.f, 1.f, 0.001f, 0.5f),
                                                     0.5f, cutoffSliderValueToText, cutoffSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("gain"), String("Gain"), String(),
                                                     NormalisableRange<float>(0.001f, 7.94f, 0.001f, 0.3f),
                                                     1.0f, gainSliderValueToText, gainSliderTextToValue));

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
                       ),
#endif
    parameters (*this, nullptr, Identifier(JucePlugin_Name), createParameterLayout())
{

    for (auto i = 0; i < numberOfVoices; ++i)
        synthesiser.addVoice(new MySynthesiserVoice());

    synthesiser.addSound(new MySynthesiserSound());

    attackParameter = parameters.getRawParameterValue("attack");
    decayParameter = parameters.getRawParameterValue("decay");
    sustainParameter = parameters.getRawParameterValue("sustain");
    releaseParameter = parameters.getRawParameterValue("release");
    typeParameter = parameters.getRawParameterValue("type");
    sharpParameter = parameters.getRawParameterValue("sharp");
    modParameter = parameters.getRawParameterValue("mod");
    cutoffParameter = parameters.getRawParameterValue("cutoff");
    gainParameter = parameters.getRawParameterValue("gain");
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
    
    
    
//
//     //waylosynth code
//
//    MidiMessage m;
//    MidiBuffer processedMidi;
//    int time;
//
//    {
//            buffer.clear();
//
//
//            MidiBuffer processedMidi;
//            int time;
//            MidiMessage m;
//
//            for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
//            {
//                if (m.isNoteOn() && m.getNoteNumber() < 60 )
//
//
//                    {
//                        waylotrans = m.getNoteNumber() - 48;
//                        m = MidiMessage::noteOff(m.getChannel(), m.getNoteNumber(), m.getVelocity());
//
//                    }
//
//
//                else if (m.isNoteOff() && m.getNoteNumber() < 60)
//
//
//                    {
//                        waylotrans = 0;
//                        m = MidiMessage::noteOff(m.getChannel(), m.getNoteNumber(), m.getVelocity());
//                    }
//
//                else if (m.isNoteOn() && m.getNoteNumber() >= 60)
//
//                    {
//                        int NewNote = m.getNoteNumber() + waylotrans -12;
//                        playing[m.getNoteNumber()]= NewNote;
//                        m = MidiMessage::noteOn(m.getChannel(), NewNote , m.getVelocity());
//
//                    }
//                else if (m.isNoteOff() && m.getNoteNumber() >= 60)
//
//                {
//                    int NewNote = playing[m.getNoteNumber()];
//                     playing[m.getNoteNumber()] = NULL;
//                    m = MidiMessage::noteOff(m.getChannel(), NewNote , m.getVelocity());
//
//                }
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
    
    // end waylosynth code
    
    
    // zawinul reverse
    
//    MidiMessage m;
//        MidiMessage n;
//        buffer.clear();
//
//
//
//        MidiBuffer processedMidi;
//        int time;
//        for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
//        {
//            if (m.isNoteOn())
//            {
//
//
//                int note = m.getNoteNumber();
//                if (note<60)
//                {
//                    n = MidiMessage::noteOn(m.getChannel(), 60 + ( 60 - note ) , m.getVelocity());
//                    processedMidi.addEvent(n, time);
//
//                }
//                else
//                {
//                    n = MidiMessage::noteOn(m.getChannel(), 60 - ( note - 60) , m.getVelocity());
//                    processedMidi.addEvent(n, time);
//
//                }
//
//           }
//           else if (m.isNoteOff()) {
//
//
//                int note = m.getNoteNumber();
//                if (note<60)
//                {
//                    n = MidiMessage::noteOff(m.getChannel(), 60 + ( 60 - note ), m.getVelocity());
//                    processedMidi.addEvent(n, time);
//
//                }
//                else
//                {
//                    n = MidiMessage::noteOff(m.getChannel(), 60 - ( note - 60) , m.getVelocity());
//                    processedMidi.addEvent(n, time);
//
//                }
//
//
//            }
//
//           else if (m.isAftertouch())
//            {
//            }
//            else if (m.isPitchWheel())
//            {
//            }
//
//        }
//
//        midiMessages.swapWith  (processedMidi) ;
    
    
    //// end of zawinul reverse
    ///


    
//    //midi latch function
    
    
    
    
//    MidiMessage m;
//        MidiMessage n;
//
//
//
//        MidiBuffer processedMidi;
//        int time;
//        for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
//        {
//            if (m.isNoteOn())
//            {
//                // note off for any playing notes
//                for ( int j = 0 ; j < 127; j++)
//                { if (playing[j] == 1) {
//                    n = MidiMessage::noteOff(m.getChannel(), j);
//                    processedMidi.addEvent(n, time);
//                    playing[j] = 0;
//                }
//                }
//            }
//            else if (m.isNoteOff()) {
//
//                int note = m.getNoteNumber();
//                // if a note is not playing send a note on and set it to "playing"
//                if (playing[note] == 0){
//                    if (m.getNoteNumber() != 84){
//                        n = MidiMessage::noteOn(m.getChannel(), note, 127.0f);
//                        processedMidi.addEvent(n, time);
//                        playing[note] = 1;
//
//                    }
//                    else{
//                        playing[84] = 0;
//                    }
//                }
//            }
//
//            else if (m.isAftertouch())
//            {
//            }
//            else if (m.isPitchWheel())
//            {
//            }
//
//        }
//        midiMessages.swapWith  (processedMidi) ;
    
    
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
//                if (waylochili > 80)
//                {
//                    waylochili = 48;
//                }
//
//                if (waylochili < 30)
//                {
//                    waylochili = 48;
//                }
//
//
//                if (m.isNoteOn() && m.getNoteNumber() < 37 )
//
//
//                {
//                    waylochili = m.getNoteNumber() + 24 ;
//                    m = MidiMessage::noteOff(m.getChannel(), m.getNoteNumber(), m.getVelocity());
//
//                }
//
//
//                else if (m.isNoteOff() && m.getNoteNumber() < 37  )
//
//
//                {
//                    waylotrans = 0;
//                    m = MidiMessage::noteOff(m.getChannel(), m.getNoteNumber(), m.getVelocity());
//                }
//
//                else if (m.isNoteOn() && m.getNoteNumber() >= 37)
//
//                {
//                    waylochili = waylochili + m.getNoteNumber() - 60;
//                    int NewNote = waylochili + waylotrans ;
//                    playing[m.getNoteNumber()]= NewNote;
//
//                    m = MidiMessage::noteOn(m.getChannel(), NewNote , m.getVelocity());
//
//                }
//                else if (m.isNoteOff() && m.getNoteNumber() >= 37)
//
//                {
//                    int NewNote = playing[m.getNoteNumber()];
//                    playing[m.getNoteNumber()] = NULL;
//                    m = MidiMessage::noteOff(m.getChannel(), NewNote , m.getVelocity());
//
//                }
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
    synthesiser.setSharpParameter(*sharpParameter);
    synthesiser.setModParameter(*modParameter);
    synthesiser.setCutoffParameter(*cutoffParameter);
    synthesiser.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    buffer.applyGainRamp(0, buffer.getNumSamples(), lastGain, *gainParameter);
    

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
}

void waylosynth2::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new waylosynth2();
}
