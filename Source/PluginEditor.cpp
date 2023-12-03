
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
waylosynth2AudioProcessorEditor::waylosynth2AudioProcessorEditor(waylosynth2 &p,
                                                                 AudioProcessorValueTreeState &vts)
    : AudioProcessorEditor(&p), processor(p), valueTreeState(vts),
      keyboardComponent(p.keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
    setSize(1200, 900);
    setResizable(true, true);

    setLookAndFeel(&plugexLookAndFeel);
    plugexLookAndFeel.setTheme("yellow");

    title.setText("Waylosynth", NotificationType::dontSendNotification);
    title.setFont(title.getFont().withPointHeight(title.getFont().getHeightInPoints() + 4));
    title.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&title);

    attackLabel.setText("Linear Attack", NotificationType::dontSendNotification);
    attackLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&attackLabel);

    attackKnob.setLookAndFeel(&plugexLookAndFeel);
    attackKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    attackKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&attackKnob);

    attackAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "attack", attackKnob));

    attackRateLabel.setText("exp Att Rate", NotificationType::dontSendNotification);
    attackRateLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&attackRateLabel);

    attackRateKnob.setLookAndFeel(&plugexLookAndFeel);
    attackRateKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    attackRateKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&attackRateKnob);

    attackRateAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "attackRate", attackRateKnob));

    attackShapeLabel.setText("exp Att Shape", NotificationType::dontSendNotification);
    attackShapeLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&attackShapeLabel);

    attackShapeKnob.setLookAndFeel(&plugexLookAndFeel);
    attackShapeKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    attackShapeKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&attackShapeKnob);

    attackShapeAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "attackShape", attackShapeKnob));

    decayLabel.setText("Decay", NotificationType::dontSendNotification);
    decayLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&decayLabel);

    decayKnob.setLookAndFeel(&plugexLookAndFeel);
    decayKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    decayKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&decayKnob);

    decayAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "decay", decayKnob));

    sustainLabel.setText("Sustain", NotificationType::dontSendNotification);
    sustainLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&sustainLabel);

    sustainKnob.setLookAndFeel(&plugexLookAndFeel);
    sustainKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sustainKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&sustainKnob);

    sustainAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "sustain", sustainKnob));

    releaseLabel.setText("Release", NotificationType::dontSendNotification);
    releaseLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&releaseLabel);

    releaseKnob.setLookAndFeel(&plugexLookAndFeel);
    releaseKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    releaseKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&releaseKnob);

    releaseAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "release", releaseKnob));

    detuneLabel.setText("Detune", NotificationType::dontSendNotification);
    detuneLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&detuneLabel);

    detuneKnob.setLookAndFeel(&plugexLookAndFeel);
    detuneKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    detuneKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&detuneKnob);

    detuneAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "detune", detuneKnob));

    typeLabel.setText("Wave Type", NotificationType::dontSendNotification);
    typeLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&typeLabel);

    typeCombo.setLookAndFeel(&plugexLookAndFeel);
    typeCombo.addItemList({"FM 1", "Pulse Wave", "FM 2", "Sawtooth", "Fixed Pulse", "Pulse Up", "2 OP version2", "Tan of Sin", "Pulse Wave 2", "FM3", "Vari Osc", "Vari Saw", "Sin w Feedbk", "Saw 2", "sin wave", "FM4", "FM5", "organ", "FM6", "fM7"}, 1);
    typeCombo.setSelectedId(1);
    addAndMakeVisible(&typeCombo);

    typeAttachment.reset(new AudioProcessorValueTreeState::ComboBoxAttachment(valueTreeState, "type", typeCombo));

    filterTypeCombo.setLookAndFeel(&plugexLookAndFeel);
    filterTypeCombo.addItemList({"Funky Obxd", "Smooth Vadim", "none"}, 1);
    filterTypeCombo.setSelectedId(1);
    addAndMakeVisible(&filterTypeCombo);

    filterTypeLabel.setText("Filter Type", NotificationType::dontSendNotification);
    filterTypeLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&filterTypeLabel);

    filterTypeAttachment.reset(new AudioProcessorValueTreeState::ComboBoxAttachment(valueTreeState, "filterType", filterTypeCombo));
    
    
    presetTypeCombo.setLookAndFeel(&plugexLookAndFeel);
    presetTypeCombo.addItemList({"waylo lead", "Waylo piano", "Waylo chilli ", "Waylo transpo", "Zawinul midi", "waylo clav", "waylo clav 2 ", "waylo 5ths "}, 1);
    presetTypeCombo.setSelectedId(1);
    addAndMakeVisible(&presetTypeCombo);

    presetTypeLabel.setText("preset Type", NotificationType::dontSendNotification);
    presetTypeLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&presetTypeLabel);

    presetTypeAttachment.reset(new AudioProcessorValueTreeState::ComboBoxAttachment(valueTreeState, "presetType", presetTypeCombo));
    
    

    spaceLabel.setText("Hyperspace", NotificationType::dontSendNotification);
    spaceLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&spaceLabel);

    spaceCombo.setLookAndFeel(&plugexLookAndFeel);
    spaceCombo.addItemList({"Normal", "WayloSpace", "SpicySpace", "JoeSpace", "5thBelow"}, 1);
    spaceCombo.setSelectedId(1);
    addAndMakeVisible(&spaceCombo);
    spaceAttachment.reset(new AudioProcessorValueTreeState::ComboBoxAttachment(valueTreeState, "space", spaceCombo));

    sharpLabel.setText("Osc Gravy", NotificationType::dontSendNotification);
    sharpLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&sharpLabel);

    sharpKnob.setLookAndFeel(&plugexLookAndFeel);
    sharpKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sharpKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&sharpKnob);

    sharpAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "sharp", sharpKnob));

    modLabel.setText("Osc Grease", NotificationType::dontSendNotification);
    modLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&modLabel);

    modKnob.setLookAndFeel(&plugexLookAndFeel);
    modKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    modKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&modKnob);

    modAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "mod", modKnob));

    greaseModLabel.setText("grease mod", NotificationType::dontSendNotification);
    greaseModLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&greaseModLabel);

    greaseModKnob.setLookAndFeel(&plugexLookAndFeel);
    greaseModKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    greaseModKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&greaseModKnob);

    greaseModAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "greaseMod", greaseModKnob));

    cutoffLabel.setText("Cutoff", NotificationType::dontSendNotification);
    cutoffLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&cutoffLabel);

    cutoffKnob.setLookAndFeel(&plugexLookAndFeel);
    cutoffKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    cutoffKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&cutoffKnob);

    cutoffAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "cutoff", cutoffKnob));

    cutoffModLabel.setText("GravyMod", NotificationType::dontSendNotification);
    cutoffModLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&cutoffModLabel);

    cutoffModKnob.setLookAndFeel(&plugexLookAndFeel);
    cutoffModKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    cutoffModKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&cutoffModKnob);

    cutoffModAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "cutoffMod", cutoffModKnob));

    resonanceLabel.setText("Resonance", NotificationType::dontSendNotification);
    resonanceLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&resonanceLabel);

    ResonanceKnob.setLookAndFeel(&plugexLookAndFeel);
    ResonanceKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    ResonanceKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&ResonanceKnob);

    resonanceAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "resonance", ResonanceKnob));

    bassoffLabel.setText("Bassoff", NotificationType::dontSendNotification);
    bassoffLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&bassoffLabel);

    bassoffKnob.setLookAndFeel(&plugexLookAndFeel);
    bassoffKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    bassoffKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&bassoffKnob);

    bassoffAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "bassoff", bassoffKnob));

    gainLabel.setText("Gain", NotificationType::dontSendNotification);
    gainLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&gainLabel);

    gainKnob.setLookAndFeel(&plugexLookAndFeel);
    gainKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    gainKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&gainKnob);

    gainAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "gain", gainKnob));

    filtVelocityLabel.setText("Filter Velocity", NotificationType::dontSendNotification);
    filtVelocityLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&filtVelocityLabel);

    filtVelocityKnob.setLookAndFeel(&plugexLookAndFeel);
    filtVelocityKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    filtVelocityKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&filtVelocityKnob);

    filtVelocityAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "filtVelocity", filtVelocityKnob));

    filtAmountLabel.setText("Filter Amount", NotificationType::dontSendNotification);
    filtAmountLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&filtAmountLabel);

    filtAmountKnob.setLookAndFeel(&plugexLookAndFeel);
    filtAmountKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    filtAmountKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&filtAmountKnob);

    filtAmountAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "filtAmount", filtAmountKnob));

    filtAttackLabel.setText("Filter Attack", NotificationType::dontSendNotification);
    filtAttackLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&filtAttackLabel);

    filtAttackKnob.setLookAndFeel(&plugexLookAndFeel);
    filtAttackKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    filtAttackKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&filtAttackKnob);

    filtAttackAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "filtAttack", filtAttackKnob));

    filtAttackShapeLabel.setText("Flt Att Shape", NotificationType::dontSendNotification);
    filtAttackShapeLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&filtAttackShapeLabel);

    filtAttackShapeKnob.setLookAndFeel(&plugexLookAndFeel);
    filtAttackShapeKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    filtAttackShapeKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&filtAttackShapeKnob);

    filtAttackShapeAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "filtAttackShape", filtAttackShapeKnob));

    filtDecayLabel.setText("Filter Decay", NotificationType::dontSendNotification);
    filtDecayLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&filtDecayLabel);

    filtDecayKnob.setLookAndFeel(&plugexLookAndFeel);
    filtDecayKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    filtDecayKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&filtDecayKnob);

    filtDecayAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "filtDecay", filtDecayKnob));

    filtDecayShapeLabel.setText("Filt Decay Shp", NotificationType::dontSendNotification);
    filtDecayShapeLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&filtDecayShapeLabel);

    filtDecayShapeKnob.setLookAndFeel(&plugexLookAndFeel);
    filtDecayShapeKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    filtDecayShapeKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&filtDecayShapeKnob);

    filtDecayShapeAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "filtDecayShape", filtDecayShapeKnob));

    filtSustainLabel.setText("Filter Sustain", NotificationType::dontSendNotification);
    filtSustainLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&filtSustainLabel);

    filtSustainKnob.setLookAndFeel(&plugexLookAndFeel);
    filtSustainKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    filtSustainKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&filtSustainKnob);

    filtSustainAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "filtSustain", filtSustainKnob));

    filtReleaseLabel.setText("Filter Release", NotificationType::dontSendNotification);
    filtReleaseLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&filtReleaseLabel);

    filtReleaseKnob.setLookAndFeel(&plugexLookAndFeel);
    filtReleaseKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    filtReleaseKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&filtReleaseKnob);

    filtReleaseAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "filtRelease", filtReleaseKnob));

    greaseAttackLabel.setText("mod Atk", NotificationType::dontSendNotification);
    greaseAttackLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&greaseAttackLabel);

    greaseAttackKnob.setLookAndFeel(&plugexLookAndFeel);
    greaseAttackKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    greaseAttackKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&greaseAttackKnob);

    greaseAttackAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "greaseAttack", greaseAttackKnob));

    greaseAttackShapeLabel.setText("mod Att Shp", NotificationType::dontSendNotification);
    greaseAttackShapeLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&greaseAttackShapeLabel);

    greaseAttackShapeKnob.setLookAndFeel(&plugexLookAndFeel);
    greaseAttackShapeKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    greaseAttackShapeKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&greaseAttackShapeKnob);

    greaseAttackShapeAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "greaseAttackShape", greaseAttackShapeKnob));

    greaseDecayLabel.setText("mod Decay", NotificationType::dontSendNotification);
    greaseDecayLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&greaseDecayLabel);

    greaseDecayKnob.setLookAndFeel(&plugexLookAndFeel);
    greaseDecayKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    greaseDecayKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&greaseDecayKnob);

    greaseDecayAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "greaseDecay", greaseDecayKnob));

    greaseDecayShapeLabel.setText("mod Dcy Shp", NotificationType::dontSendNotification);
    greaseDecayShapeLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&greaseDecayShapeLabel);

    greaseDecayShapeKnob.setLookAndFeel(&plugexLookAndFeel);
    greaseDecayShapeKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    greaseDecayShapeKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&greaseDecayShapeKnob);

    greaseDecayShapeAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "greaseDecayShape", greaseDecayShapeKnob));

    greaseSustainLabel.setText("mod Sustain", NotificationType::dontSendNotification);
    greaseSustainLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&greaseSustainLabel);

    greaseSustainKnob.setLookAndFeel(&plugexLookAndFeel);
    greaseSustainKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    greaseSustainKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&greaseSustainKnob);

    greaseSustainAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "greaseSustain", greaseSustainKnob));

    greaseReleaseLabel.setText("mod Release", NotificationType::dontSendNotification);
    greaseReleaseLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&greaseReleaseLabel);

    greaseReleaseKnob.setLookAndFeel(&plugexLookAndFeel);
    greaseReleaseKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    greaseReleaseKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&greaseReleaseKnob);

    greaseReleaseAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "greaseRelease", greaseReleaseKnob));

    greaseVelocityLabel.setText("grease Velocity", NotificationType::dontSendNotification);
    greaseVelocityLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&greaseVelocityLabel);

    greaseVelocityKnob.setLookAndFeel(&plugexLookAndFeel);
    greaseVelocityKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    greaseVelocityKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&greaseVelocityKnob);

    greaseVelocityAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "greaseVelocity", greaseVelocityKnob));

    greaseKeyboardLabel.setText("grease Kboard", NotificationType::dontSendNotification);
    greaseKeyboardLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&greaseKeyboardLabel);

    greaseKeyboardKnob.setLookAndFeel(&plugexLookAndFeel);
    greaseKeyboardKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    greaseKeyboardKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&greaseKeyboardKnob);

    greaseKeyboardAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "greaseKeyboard", greaseKeyboardKnob));

    gravyVelocityLabel.setText("gravy Velocity", NotificationType::dontSendNotification);
    gravyVelocityLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&gravyVelocityLabel);

    gravyVelocityKnob.setLookAndFeel(&plugexLookAndFeel);
    gravyVelocityKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    gravyVelocityKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&gravyVelocityKnob);

    gravyVelocityAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "gravyVelocity", gravyVelocityKnob));

    gravyKeyboardLabel.setText("gravy Keyboard", NotificationType::dontSendNotification);
    gravyKeyboardLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&gravyKeyboardLabel);

    gravyKeyboardKnob.setLookAndFeel(&plugexLookAndFeel);
    gravyKeyboardKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    gravyKeyboardKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&gravyKeyboardKnob);

    gravyKeyboardAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "gravyKeyboard", gravyKeyboardKnob));

    cutoffVelocityLabel.setText("cutoff Velocity", NotificationType::dontSendNotification);
    cutoffVelocityLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&cutoffVelocityLabel);

    cutoffVelocityKnob.setLookAndFeel(&plugexLookAndFeel);
    cutoffVelocityKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    cutoffVelocityKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&cutoffVelocityKnob);

    cutoffVelocityAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "cutoffVelocity", cutoffVelocityKnob));

    cutoffKeyboardLabel.setText("cutoff Keyboard", NotificationType::dontSendNotification);
    cutoffKeyboardLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&cutoffKeyboardLabel);

    cutoffKeyboardKnob.setLookAndFeel(&plugexLookAndFeel);
    cutoffKeyboardKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    cutoffKeyboardKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&cutoffKeyboardKnob);

    cutoffKeyboardAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "cutoffKeyboard", cutoffKeyboardKnob));

    filtFMVelocityLabel.setText("filterFM Velocity", NotificationType::dontSendNotification);
    filtFMVelocityLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&filtFMVelocityLabel);

    filtFMVelocityKnob.setLookAndFeel(&plugexLookAndFeel);
    filtFMVelocityKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    filtFMVelocityKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&filtFMVelocityKnob);

    filtFMVelocityAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "filtFMVelocity", filtFMVelocityKnob));

    filtFMLabel.setText("filterFM", NotificationType::dontSendNotification);
    filtFMLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&filtFMLabel);

    filtFMKnob.setLookAndFeel(&plugexLookAndFeel);
    filtFMKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    filtFMKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&filtFMKnob);

    filtFMAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "filtFM", filtFMKnob));

    addAndMakeVisible(keyboardComponent);
}

waylosynth2AudioProcessorEditor::~waylosynth2AudioProcessorEditor()
{
    attackKnob.setLookAndFeel(nullptr);
    attackRateKnob.setLookAndFeel(nullptr);
    attackShapeKnob.setLookAndFeel(nullptr);
    decayKnob.setLookAndFeel(nullptr);
    sustainKnob.setLookAndFeel(nullptr);
    releaseKnob.setLookAndFeel(nullptr);
    typeCombo.setLookAndFeel(nullptr);
    presetTypeCombo.setLookAndFeel(nullptr);
    filterTypeCombo.setLookAndFeel(nullptr);
    spaceCombo.setLookAndFeel(nullptr);
    sharpKnob.setLookAndFeel(nullptr);
    modKnob.setLookAndFeel(nullptr);
    greaseModKnob.setLookAndFeel(nullptr);
    cutoffKnob.setLookAndFeel(nullptr);
    cutoffModKnob.setLookAndFeel(nullptr);
    ResonanceKnob.setLookAndFeel(nullptr);
    bassoffKnob.setLookAndFeel(nullptr);
    gainKnob.setLookAndFeel(nullptr);
    detuneKnob.setLookAndFeel(nullptr);
    filtVelocityKnob.setLookAndFeel(nullptr);
    filtAmountKnob.setLookAndFeel(nullptr);
    filtAttackKnob.setLookAndFeel(nullptr);
    filtAttackShapeKnob.setLookAndFeel(nullptr);
    filtDecayKnob.setLookAndFeel(nullptr);
    filtDecayShapeKnob.setLookAndFeel(nullptr);
    filtSustainKnob.setLookAndFeel(nullptr);
    filtReleaseKnob.setLookAndFeel(nullptr);
    greaseAttackKnob.setLookAndFeel(nullptr);
    greaseAttackShapeKnob.setLookAndFeel(nullptr);
    greaseDecayKnob.setLookAndFeel(nullptr);
    greaseDecayShapeKnob.setLookAndFeel(nullptr);
    greaseSustainKnob.setLookAndFeel(nullptr);
    greaseReleaseKnob.setLookAndFeel(nullptr);

    greaseKeyboardKnob.setLookAndFeel(nullptr);
    greaseVelocityKnob.setLookAndFeel(nullptr);
    gravyKeyboardKnob.setLookAndFeel(nullptr);
    gravyVelocityKnob.setLookAndFeel(nullptr);
    cutoffVelocityKnob.setLookAndFeel(nullptr);
    cutoffKeyboardKnob.setLookAndFeel(nullptr);

    filtFMVelocityKnob.setLookAndFeel(nullptr);
    filtFMKnob.setLookAndFeel(nullptr);
}

//==============================================================================
void waylosynth2AudioProcessorEditor::paint(Graphics &g)
{

    g.fillAll(Colour(51, 51, 51));
    auto myImage = juce::ImageCache::getFromMemory(BinaryData::logocolor_png, BinaryData::logocolor_pngSize);
    g.drawImageAt(myImage, 0, 320);
}

void waylosynth2AudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(12, 12);
    float width = area.getWidth();

    auto area1 = area.removeFromTop(130);

    auto sharpArea = area1.removeFromLeft(width / 8.0f).withSizeKeepingCentre(80, 100);
    sharpLabel.setBounds(sharpArea.removeFromTop(20));
    sharpKnob.setBounds(sharpArea);

    auto ModArea = area1.removeFromLeft(width / 8.0f).withSizeKeepingCentre(80, 100);
    modLabel.setBounds(ModArea.removeFromTop(20));
    modKnob.setBounds(ModArea);

    auto CutoffArea = area1.removeFromLeft(width / 8.0f).withSizeKeepingCentre(80, 100);
    cutoffLabel.setBounds(CutoffArea.removeFromTop(20));
    cutoffKnob.setBounds(CutoffArea);

    auto ResonanceArea = area1.removeFromLeft(width / 8.0f).withSizeKeepingCentre(80, 100);
    resonanceLabel.setBounds(ResonanceArea.removeFromTop(20));
    ResonanceKnob.setBounds(ResonanceArea);

    auto BassoffArea = area1.removeFromLeft(width / 8.0f).withSizeKeepingCentre(80, 100);
    bassoffLabel.setBounds(BassoffArea.removeFromTop(20));
    bassoffKnob.setBounds(BassoffArea);

    auto gainArea = area1.removeFromLeft(width / 8.0f).withSizeKeepingCentre(80, 100);
    gainLabel.setBounds(gainArea.removeFromTop(20));
    gainKnob.setBounds(gainArea);

    auto area2 = area.removeFromTop(100);

    auto attackArea = area2.removeFromLeft(width / 6.0f).withSizeKeepingCentre(80, 100);
    attackLabel.setBounds(attackArea.removeFromTop(20));
    attackKnob.setBounds(attackArea);

    auto attackRateArea = area2.removeFromLeft(width / 6.0f).withSizeKeepingCentre(80, 100);
    attackRateLabel.setBounds(attackRateArea.removeFromTop(20));
    attackRateKnob.setBounds(attackRateArea);

    auto attackShapeArea = area2.removeFromLeft(width / 6.0f).withSizeKeepingCentre(80, 100);
    attackShapeLabel.setBounds(attackShapeArea.removeFromTop(20));
    attackShapeKnob.setBounds(attackShapeArea);

    auto decayArea = area2.removeFromLeft(width / 6.0f).withSizeKeepingCentre(80, 100);
    decayLabel.setBounds(decayArea.removeFromTop(20));
    decayKnob.setBounds(decayArea);

    auto sustainArea = area2.removeFromLeft(width / 6.0f).withSizeKeepingCentre(80, 100);
    sustainLabel.setBounds(sustainArea.removeFromTop(20));
    sustainKnob.setBounds(sustainArea);

    auto releaseArea = area2.removeFromLeft(width / 6.0f).withSizeKeepingCentre(80, 100);
    releaseLabel.setBounds(releaseArea.removeFromTop(20));
    releaseKnob.setBounds(releaseArea);

    auto area3 = area.removeFromTop(110);

    auto filtAttackArea = area3.removeFromLeft(width / 8.0f).withSizeKeepingCentre(80, 100);
    filtAttackLabel.setBounds(filtAttackArea.removeFromTop(20));
    filtAttackKnob.setBounds(filtAttackArea);

    auto filtVelocityArea = area3.removeFromLeft(width / 8.0f).withSizeKeepingCentre(80, 100);
    filtVelocityLabel.setBounds(filtVelocityArea.removeFromTop(20));
    filtVelocityKnob.setBounds(filtVelocityArea);

    auto filtAmountArea = area3.removeFromLeft(width / 8.0f).withSizeKeepingCentre(80, 100);
    filtAmountLabel.setBounds(filtAmountArea.removeFromTop(20));
    filtAmountKnob.setBounds(filtAmountArea);

    auto filtAttackShapeArea = area3.removeFromLeft(width / 8.0f).withSizeKeepingCentre(80, 100);
    filtAttackShapeLabel.setBounds(filtAttackShapeArea.removeFromTop(20));
    filtAttackShapeKnob.setBounds(filtAttackShapeArea);

    auto filtDecayArea = area3.removeFromLeft(width / 8.0f).withSizeKeepingCentre(80, 100);
    filtDecayLabel.setBounds(filtDecayArea.removeFromTop(20));
    filtDecayKnob.setBounds(filtDecayArea);

    auto filtDecayShapeArea = area3.removeFromLeft(width / 8.0f).withSizeKeepingCentre(80, 100);
    filtDecayShapeLabel.setBounds(filtDecayShapeArea.removeFromTop(20));
    filtDecayShapeKnob.setBounds(filtDecayShapeArea);

    auto filtSustainArea = area3.removeFromLeft(width / 8.0f).withSizeKeepingCentre(80, 100);
    filtSustainLabel.setBounds(filtSustainArea.removeFromTop(20));
    filtSustainKnob.setBounds(filtSustainArea);

    auto filtReleaseArea = area3.removeFromLeft(width / 8.0f).withSizeKeepingCentre(80, 100);
    filtReleaseLabel.setBounds(filtReleaseArea.removeFromTop(20));
    filtReleaseKnob.setBounds(filtReleaseArea);

    auto area5 = area.removeFromTop(110);

    auto gravyVelocityArea = area5.removeFromRight(width / 6.0f).withSizeKeepingCentre(80, 100);
    gravyVelocityLabel.setBounds(gravyVelocityArea.removeFromTop(20));
    gravyVelocityKnob.setBounds(gravyVelocityArea);

    auto gravyKeyboardArea = area5.removeFromRight(width / 6.0f).withSizeKeepingCentre(80, 100);
    gravyKeyboardLabel.setBounds(gravyKeyboardArea.removeFromTop(20));
    gravyKeyboardKnob.setBounds(gravyKeyboardArea);

    auto cutoffVelocityArea = area5.removeFromRight(width / 6.0f).withSizeKeepingCentre(80, 100);
    cutoffVelocityLabel.setBounds(cutoffVelocityArea.removeFromTop(20));
    cutoffVelocityKnob.setBounds(cutoffVelocityArea);

    auto cutoffKeyboardArea = area5.removeFromRight(width / 6.0f).withSizeKeepingCentre(80, 100);
    cutoffKeyboardLabel.setBounds(cutoffKeyboardArea.removeFromTop(20));
    cutoffKeyboardKnob.setBounds(cutoffKeyboardArea);

    auto area6 = area.removeFromTop(110);

    auto greaseVelocityArea = area6.removeFromRight(width / 8.0f).withSizeKeepingCentre(80, 100);
    greaseVelocityLabel.setBounds(greaseVelocityArea.removeFromTop(20));
    greaseVelocityKnob.setBounds(greaseVelocityArea);

    auto greaseKeyboardArea = area6.removeFromRight(width / 8.0f).withSizeKeepingCentre(80, 100);
    greaseKeyboardLabel.setBounds(greaseKeyboardArea.removeFromTop(20));
    greaseKeyboardKnob.setBounds(greaseKeyboardArea);

//    auto filterFMVelocityArea = area6.removeFromRight(width / 8.0f).withSizeKeepingCentre(80, 100);
//    filtFMVelocityLabel.setBounds(filterFMVelocityArea.removeFromTop(20));
//    filtFMVelocityKnob.setBounds(filterFMVelocityArea);
//
//    auto filterFMArea = area6.removeFromRight(width / 8.0f).withSizeKeepingCentre(80, 100);
//    filtFMLabel.setBounds(filterFMArea.removeFromTop(20));
//    filtFMKnob.setBounds(filterFMArea);

    auto detuneArea = area6.removeFromRight(width / 8.0f).withSizeKeepingCentre(80, 100);
    detuneLabel.setBounds(detuneArea.removeFromTop(20));
    detuneKnob.setBounds(detuneArea);

    auto area7 = area.removeFromTop(100);

    auto typeArea = area7.removeFromRight(width / 6.0f).withSizeKeepingCentre(80, 100);
    typeLabel.setBounds(typeArea.removeFromTop(25));
    typeCombo.setBounds(typeArea.removeFromTop(20).withSizeKeepingCentre(170, 30));

    auto spaceArea = area7.removeFromRight(width / 6.0f).withSizeKeepingCentre(80, 100);
    spaceLabel.setBounds(spaceArea.removeFromTop(25));
    spaceCombo.setBounds(spaceArea.removeFromTop(20).withSizeKeepingCentre(170, 30));
    
    auto filterTypeArea = area7.removeFromRight(width / 6.0f).withSizeKeepingCentre(80, 100);
    filterTypeLabel.setBounds(filterTypeArea.removeFromTop(25));
    filterTypeCombo.setBounds(filterTypeArea.removeFromTop(20).withSizeKeepingCentre(170, 30));

    auto presetTypeArea = area7.removeFromRight(width / 6.0f).withSizeKeepingCentre(80, 100);
    presetTypeLabel.setBounds(presetTypeArea.removeFromTop(25));
    presetTypeCombo.setBounds(presetTypeArea.removeFromTop(20).withSizeKeepingCentre(170, 30));
    
    presetTypeCombo.onChange = [this] { getPreset(); };
    
    

    area.removeFromTop(12);

    keyboardComponent.setBounds(area.removeFromBottom(90));
    
    
}

void waylosynth2AudioProcessorEditor::getPreset(){
    auto& params = processor.getParameters();
    int preset = presetTypeCombo.getSelectedId();
    

      sharpKnob.setValue(settingsArray[preset][0]);
      modKnob.setValue(settingsArray[preset][1]);
      cutoffKnob.setValue(settingsArray[preset][2]);
      ResonanceKnob.setValue(settingsArray[preset][3]);
      bassoffKnob.setValue(settingsArray[preset][4]);
      gainKnob.setValue(settingsArray[preset][5]);
      attackKnob.setValue(settingsArray[preset][6]);
      attackRateKnob.setValue(settingsArray[preset][7]);
      attackShapeKnob.setValue(settingsArray[preset][8]);
      decayKnob.setValue(settingsArray[preset][9]);
      sustainKnob.setValue(settingsArray[preset][10]);
      releaseKnob.setValue(settingsArray[preset][11]);
      filtAttackKnob.setValue(settingsArray[preset][12]);
      filtVelocityKnob.setValue(settingsArray[preset][13]);
      filtAmountKnob.setValue(settingsArray[preset][14]);
      filtAttackShapeKnob.setValue(settingsArray[preset][15]);
      filtDecayKnob.setValue(settingsArray[preset][16]);
      filtDecayShapeKnob.setValue(settingsArray[preset][17]);
      filtSustainKnob.setValue(settingsArray[preset][18]);
      filtReleaseKnob.setValue(settingsArray[preset][19]);
      cutoffKeyboardKnob.setValue(settingsArray[preset][20]);
      cutoffVelocityKnob.setValue(settingsArray[preset][21]);
      gravyKeyboardKnob.setValue(settingsArray[preset][22]);
      gravyVelocityKnob.setValue(settingsArray[preset][23]);
      detuneKnob.setValue(settingsArray[preset][24]);
      greaseKeyboardKnob.setValue(settingsArray[preset][25]);
      greaseVelocityKnob.setValue(settingsArray[preset][26]);
      filterTypeCombo.setSelectedItemIndex(settingsArray[preset][27]);
      spaceCombo.setSelectedItemIndex(settingsArray[preset][28]);
      typeCombo.setSelectedItemIndex(settingsArray[preset][29]);
    

    
}
