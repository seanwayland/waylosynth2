
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "waylo_look_and_feel.h"

class waylosynth2AudioProcessorEditor : public AudioProcessorEditor
{
public:
    waylosynth2AudioProcessorEditor(waylosynth2 &, AudioProcessorValueTreeState &vts);
    ~waylosynth2AudioProcessorEditor();

    void paint(Graphics &) override;
    void resized() override;
    void getPreset();

private:
    waylosynth2 &processor;

    waylo_look_and_feel plugexLookAndFeel;

    AudioProcessorValueTreeState &valueTreeState;

    Label title;

    Label attackLabel;
    Slider attackKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackAttachment;

    Label attackRateLabel;
    Slider attackRateKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackRateAttachment;

    Label attackShapeLabel;
    Slider attackShapeKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackShapeAttachment;

    Label decayLabel;
    Slider decayKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> decayAttachment;

    Label sustainLabel;
    Slider sustainKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;

    Label releaseLabel;
    Slider releaseKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;

    Label typeLabel;
    ComboBox typeCombo;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> typeAttachment;

    Label filterTypeLabel;
    ComboBox filterTypeCombo;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;
    
    Label presetTypeLabel;
    ComboBox presetTypeCombo;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> presetTypeAttachment;

    Label spaceLabel;
    ComboBox spaceCombo;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> spaceAttachment;

    Label sharpLabel;
    Slider sharpKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sharpAttachment;

    Label modLabel;
    Slider modKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> modAttachment;

    Label greaseModLabel;
    Slider greaseModKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> greaseModAttachment;

    Label cutoffLabel;
    Slider cutoffKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;

    Label cutoffModLabel;
    Slider cutoffModKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> cutoffModAttachment;

    Label resonanceLabel;
    Slider ResonanceKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> resonanceAttachment;

    Label bassoffLabel;
    Slider bassoffKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> bassoffAttachment;

    Label detuneLabel;
    Slider detuneKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> detuneAttachment;

    Label gainLabel;
    Slider gainKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    Label filtVelocityLabel;
    Slider filtVelocityKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtVelocityAttachment;

    Label filtAmountLabel;
    Slider filtAmountKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtAmountAttachment;

    Label filtAttackLabel;
    Slider filtAttackKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtAttackAttachment;

    Label filtAttackShapeLabel;
    Slider filtAttackShapeKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtAttackShapeAttachment;

    Label filtDecayLabel;
    Slider filtDecayKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtDecayAttachment;

    Label filtDecayShapeLabel;
    Slider filtDecayShapeKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtDecayShapeAttachment;

    Label filtSustainLabel;
    Slider filtSustainKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtSustainAttachment;

    Label filtReleaseLabel;
    Slider filtReleaseKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtReleaseAttachment;

    Label filtFMLabel;
    Slider filtFMKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtFMAttachment;

    Label filtFMVelocityLabel;
    Slider filtFMVelocityKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtFMVelocityAttachment;

    Label greaseAttackLabel;
    Slider greaseAttackKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> greaseAttackAttachment;

    Label greaseAttackShapeLabel;
    Slider greaseAttackShapeKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> greaseAttackShapeAttachment;

    Label greaseDecayLabel;
    Slider greaseDecayKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> greaseDecayAttachment;

    Label greaseDecayShapeLabel;
    Slider greaseDecayShapeKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> greaseDecayShapeAttachment;

    Label greaseSustainLabel;
    Slider greaseSustainKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> greaseSustainAttachment;

    Label greaseReleaseLabel;
    Slider greaseReleaseKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> greaseReleaseAttachment;

    Label greaseVelocityLabel;
    Slider greaseVelocityKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> greaseVelocityAttachment;

    Label greaseKeyboardLabel;
    Slider greaseKeyboardKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> greaseKeyboardAttachment;

    Label gravyVelocityLabel;
    Slider gravyVelocityKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gravyVelocityAttachment;

    Label gravyKeyboardLabel;
    Slider gravyKeyboardKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gravyKeyboardAttachment;

    Label cutoffVelocityLabel;
    Slider cutoffVelocityKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> cutoffVelocityAttachment;

    Label cutoffKeyboardLabel;
    Slider cutoffKeyboardKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> cutoffKeyboardAttachment;

    MidiKeyboardComponent keyboardComponent;
    
    float settingsArray [9][30] = {
        
        {},
        // waylo lead
        
        {
//          gravy , grease , citoff, resonance, bassoff, gain
            0.1782, 0.2316, 0.01425, 0.3273, 0.500, 10.00,
//          lin attack, exp att, att shape, decay, sustain, release
            0.047,  0.562, 0.797, 2.83, 0.75, 0.025,
//          flt atck,flt vel,flt amt,flt att shp,flt decy,flt dec shp, flt sus, flt rel
            0.0095, 0.3734, 0.1873, 0.2416,0.0844,0.0525,0.0227,0.0089,
//          cut key,cut vel,grvy key,grvy vel,
            0.2092,0.3086, 0.0838, 0.7700,
//          detune, grease keyboard, grease vel
            1.0, -0.9600, 1.0000,
//          filt type , hyperspace, wave type,
            2, 0, 9
        },
        // waylo piano
        {
//          gravy , grease , citoff, resonance, bassoff, gain
            0.55, 0.51, 0.05, 0.1397, 0.7532, 12.00,
//          lin attack, exp att, att shape, decay, sustain, release
            0.006,  0.923, 0.958, 1.425, 0.07, 0.015,
//          flt atck,flt vel,flt amt,flt att shp,flt decy,flt dec shp, flt sus, flt rel
            0.105, 1.0, 0.9783,0.6427,0.2592,1.0,0.0,0.0162,
//          cut key,cut vel,grvy key,grvy vel,
            0.0926,0.3977, 0.0794, 1.00,
//          detune, grease keyboard, grease vel
            1.0, -0.85, 1.0,
//          filt type , hyperspace, wave type,
            2, 0, 18
        },
        // waylo chilli
        {
            
            //          gravy , grease , citoff, resonance, bassoff, gain
                        0.1082, 0.2409, 0.01425, 0.3273, 0.5535, 10.00,
            //          lin attack, exp att, att shape, decay, sustain, release
                        0.010,  0.815, 0.787, 2.622, 0.184, 0.006,
            //          flt atck,flt vel,flt amt,flt att shp,flt decy,flt dec shp, flt sus, flt rel
                        0.0095, 0.3734, 0.1873, 0.2416,0.0844,0.0525,0.0227,0.0089,
            //          cut key,cut vel,grvy key,grvy vel,
                        0.2092,0.3086, 0.0825, 0.4252,
            //          detune, grease keyboard, grease vel
                        1.0, -0.2898, 0.1777,
            //          filt type , hyperspace, wave type,
                        2, 2, 9
        },

    
        // steve hunt fm 
        {
            //          gravy , grease , citoff, resonance, bassoff, gain
                        0.1782, 0.2316, 0.01425, 0.3273, 0.500, 10.00,
            //          lin attack, exp att, att shape, decay, sustain, release
                        0.047,  0.562, 0.797, 2.83, 0.75, 0.025,
            //          flt atck,flt vel,flt amt,flt att shp,flt decy,flt dec shp, flt sus, flt rel
                        0.0095, 0.3734, 0.1873, 0.2416,0.0844,0.0525,0.0227,0.0089,
            //          cut key,cut vel,grvy key,grvy vel,
                        0.2092,0.3086, 0.0838, 0.7700,
            //          detune, grease keyboard, grease vel
                        1.0, -0.9600, 1.0000,
            //          filt type , hyperspace, wave type,
                        2, 1, 9
        },
        
        {
            //          gravy , grease , citoff, resonance, bassoff, gain
                        0.1782, 0.2316, 0.01425, 0.3273, 0.500, 10.00,
            //          lin attack, exp att, att shape, decay, sustain, release
                        0.047,  0.562, 0.797, 2.83, 0.75, 0.025,
            //          flt atck,flt vel,flt amt,flt att shp,flt decy,flt dec shp, flt sus, flt rel
                        0.0095, 0.3734, 0.1873, 0.2416,0.0844,0.0525,0.0227,0.0089,
            //          cut key,cut vel,grvy key,grvy vel,
                        0.2092,0.3086, 0.0838, 0.7700,
            //          detune, grease keyboard, grease vel
                        1.0, -0.9600, 1.0000,
            //          filt type , hyperspace, wave type,
                        2, 3, 9
        },
        {
//          gravy , grease , citoff, resonance, bassoff, gain
            0.22, 0.23, 0.64, 0.2797, 0.2032, 12.00,
//          lin attack, exp att, att shape, decay, sustain, release
            0.003,  0.874, 0.825, 0.283, 0.3, 0.023,
//          flt atck,flt vel,flt amt,flt att shp,flt decy,flt dec shp, flt sus, flt rel
            0.105, 0.1437, 0.45,0.3,0.2,0.15,0.0,0.3,
//          cut key,cut vel,grvy key,grvy vel,
            0.0217,0.6081, 0.0324, 1.00,
//          detune, grease keyboard, grease vel
            1.0, -0.95, 1.0,
//          filt type , hyperspace, wave type,
            0, 0, 3
        },
        {
//          gravy , grease , citoff, resonance, bassoff, gain
            0.31, 0.39, 0.569, 0.4012, 0.1989, 12.00,
//          lin attack, exp att, att shape, decay, sustain, release
            0.008,  0.893, 0.825, 0.283, 0.156, 0.023,
//          flt atck,flt vel,flt amt,flt att shp,flt decy,flt dec shp, flt sus, flt rel
            0.0322, 0.1437, 0.45,0.3,0.2,0.15,0.0,0.3,
//          cut key,cut vel,grvy key,grvy vel,
            0.0217,0.6081, 0.0324, 1.00,
//          detune, grease keyboard, grease vel
            1.0, -0.95, 1.0,
//          filt type , hyperspace, wave type,
            0, 0, 19
        },
        
        {
//          gravy , grease , citoff, resonance, bassoff, gain
            0.11, 0.06, 0.569, 0.4012, 0.2589, 12.00,
//          lin attack, exp att, att shape, decay, sustain, release
            0.008,  0.893, 0.825, 2.5, 0.366, 0.023,
//          flt atck,flt vel,flt amt,flt att shp,flt decy,flt dec shp, flt sus, flt rel
            0.0322, 0.1437, 0.45,0.3,0.2,0.15,0.0,0.3,
//          cut key,cut vel,grvy key,grvy vel,
            0.0217,0.6081, 0.0324, 1.00,
//          detune, grease keyboard, grease vel
            1.0, -0.95, 1.0,
//          filt type , hyperspace, wave type,
            2, 4, 3
        },
        
        

        
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(waylosynth2AudioProcessorEditor)
};
