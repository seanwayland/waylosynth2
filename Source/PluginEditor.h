
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
    
    //myimage = juce::ImageCache::getFromMemory(BinaryData::logocolor_png, BinaryData::logocolor_pngSize);

private:
    waylosynth2& processor;

    waylo_look_and_feel plugexLookAndFeel;

    AudioProcessorValueTreeState& valueTreeState;
    
    //Image myimage;


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
    
    Label spaceLabel;
    ComboBox spaceCombo;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> spaceAttachment;

    Label  sharpLabel;
    Slider sharpKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sharpAttachment;
    
    Label  modLabel;
    Slider modKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> modAttachment;
    
    Label  greaseModLabel;
    Slider greaseModKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> greaseModAttachment;
    
    Label  cutoffLabel;
    Slider cutoffKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;
    
    Label  cutoffModLabel;
    Slider cutoffModKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> cutoffModAttachment;
    
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
    
    Label  filtAttackLabel;
    Slider filtAttackKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtAttackAttachment;
    
    Label  filtAttackShapeLabel;
    Slider filtAttackShapeKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtAttackShapeAttachment;
    
    Label  filtDecayLabel;
    Slider filtDecayKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtDecayAttachment;
    
    Label  filtDecayShapeLabel;
    Slider filtDecayShapeKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtDecayShapeAttachment;
    
    Label  filtSustainLabel;
    Slider filtSustainKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtSustainAttachment;
    
    Label  filtReleaseLabel;
    Slider filtReleaseKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtReleaseAttachment;
    
    Label  greaseAttackLabel;
    Slider greaseAttackKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> greaseAttackAttachment;
    
    Label  greaseAttackShapeLabel;
    Slider greaseAttackShapeKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> greaseAttackShapeAttachment;
    
    Label  greaseDecayLabel;
    Slider greaseDecayKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> greaseDecayAttachment;
    
    Label  greaseDecayShapeLabel;
    Slider greaseDecayShapeKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> greaseDecayShapeAttachment;
    
    Label  greaseSustainLabel;
    Slider greaseSustainKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> greaseSustainAttachment;
    
    Label  greaseReleaseLabel;
    Slider greaseReleaseKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> greaseReleaseAttachment;
    
    
    
    Label  greaseVelocityLabel;
    Slider greaseVelocityKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> greaseVelocityAttachment;
    
    Label  greaseKeyboardLabel;
    Slider greaseKeyboardKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> greaseKeyboardAttachment;
    
    Label  gravyVelocityLabel;
    Slider gravyVelocityKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gravyVelocityAttachment;
    
    Label  gravyKeyboardLabel;
    Slider gravyKeyboardKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gravyKeyboardAttachment;
    
    Label  cutoffVelocityLabel;
    Slider cutoffVelocityKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> cutoffVelocityAttachment;
    
    Label  cutoffKeyboardLabel;
    Slider cutoffKeyboardKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> cutoffKeyboardAttachment;
    
    
    
    
    
    
    
    

    MidiKeyboardComponent keyboardComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (waylosynth2AudioProcessorEditor)
};

