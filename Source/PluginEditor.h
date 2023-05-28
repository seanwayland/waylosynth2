
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
    
    Label  attackRateLabel;
    Slider attackRateKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackRateAttachment;
    
    Label  attackShapeLabel;
    Slider attackShapeKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackShapeAttachment;

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
    
    Label  cutoffLabel;
    Slider cutoffKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;
    
    Label  resonanceLabel;
    Slider ResonanceKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> resonanceAttachment;
    
    Label  bassoffLabel;
    Slider bassoffKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> bassoffAttachment;
    
    Label  detuneLabel;
    Slider detuneKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> detuneAttachment;

    Label  gainLabel;
    Slider gainKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    MidiKeyboardComponent keyboardComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (waylosynth2AudioProcessorEditor)
};

