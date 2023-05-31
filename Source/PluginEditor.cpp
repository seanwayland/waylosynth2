
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
waylosynth2AudioProcessorEditor::waylosynth2AudioProcessorEditor (waylosynth2& p,
                                                                                                  AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState (vts),
      keyboardComponent (p.keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
    setSize (1000, 800);
    
    

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
    typeCombo.addItemList({"FM_Feedback_1", "Pulse Wave", "2_OP_FM", "Sawtooth", "Fixed_Pulse", "pulse_up", "2_OP_version2", "Tan_of_Sin", "pwm_bleb", "face_dx", "variosc", "varisaw", "sin_w_feedbk", "band_lim_saw_2", "band_lim_pulse_2", "empty", "empty","organ","empty","empty"}, 1);
    typeCombo.setSelectedId(1);
    addAndMakeVisible(&typeCombo);

    typeAttachment.reset(new AudioProcessorValueTreeState::ComboBoxAttachment(valueTreeState, "type", typeCombo));

    sharpLabel.setText("Shape", NotificationType::dontSendNotification);
    sharpLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&sharpLabel);

    sharpKnob.setLookAndFeel(&plugexLookAndFeel);
    sharpKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sharpKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&sharpKnob);

    sharpAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "sharp", sharpKnob));
    
    modLabel.setText("Mod", NotificationType::dontSendNotification);
    modLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(& modLabel);

    modKnob.setLookAndFeel(&plugexLookAndFeel);
    modKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    modKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(& modKnob);

    modAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "mod",  modKnob));
    
    cutoffLabel.setText("Cutoff", NotificationType::dontSendNotification);
    cutoffLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(& cutoffLabel);

    cutoffKnob.setLookAndFeel(&plugexLookAndFeel);
    cutoffKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    cutoffKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(& cutoffKnob);
    
    cutoffAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "cutoff",  cutoffKnob));
    
    resonanceLabel.setText("Resonance", NotificationType::dontSendNotification);
    resonanceLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(& resonanceLabel);

    ResonanceKnob.setLookAndFeel(&plugexLookAndFeel);
    ResonanceKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    ResonanceKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(& ResonanceKnob);

    resonanceAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "resonance",  ResonanceKnob));
    
    bassoffLabel.setText("Bassoff", NotificationType::dontSendNotification);
    bassoffLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(& bassoffLabel);

    bassoffKnob.setLookAndFeel(&plugexLookAndFeel);
    bassoffKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    bassoffKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(& bassoffKnob);

    bassoffAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "bassoff",  bassoffKnob));

    gainLabel.setText("Gain", NotificationType::dontSendNotification);
    gainLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&gainLabel);

    gainKnob.setLookAndFeel(&plugexLookAndFeel);
    gainKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    gainKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&gainKnob);

    gainAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "gain", gainKnob));
    
    
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
    sharpKnob.setLookAndFeel(nullptr);
    modKnob.setLookAndFeel(nullptr);
    cutoffKnob.setLookAndFeel(nullptr);
    ResonanceKnob.setLookAndFeel(nullptr);
    bassoffKnob.setLookAndFeel(nullptr);
    gainKnob.setLookAndFeel(nullptr);
    detuneKnob.setLookAndFeel(nullptr);
    filtAttackKnob.setLookAndFeel(nullptr);
    filtAttackShapeKnob.setLookAndFeel(nullptr);
    filtDecayKnob.setLookAndFeel(nullptr);
    filtDecayShapeKnob.setLookAndFeel(nullptr);
}

//==============================================================================
void waylosynth2AudioProcessorEditor::paint (Graphics& g)
{
    
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    //g.drawImage (myimage, 0, 0, 50, 50,0, 0, 50, 50, false);
    auto myImage = juce::ImageCache::getFromMemory(BinaryData::logocolor_png, BinaryData::logocolor_pngSize);
    
    g.drawImage (myImage, getLocalBounds().toFloat());
    //g.drawImage (myImage, 0, 500, 500, 500,500, 0, 0, 800, false);
    //drawImage (const Image &imageToDraw, int destX, int destY, int destWidth, int destHeight, int sourceX, int sourceY, int //sourceWidth, int sourceHeight, bool fillAlphaChannelWithCurrentBrush=false)
    
}

void waylosynth2AudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(12, 12);
    float width = area.getWidth();

    //title.setBounds(area.removeFromTop(40));
    //area.removeFromTop(14);

    auto area1 = area.removeFromTop(100);
    
    auto area3 = area.removeFromTop(100);

    auto attackArea = area1.removeFromLeft(width/7.0f).withSizeKeepingCentre(80, 100);
    attackLabel.setBounds(attackArea.removeFromTop(20));
    attackKnob.setBounds(attackArea);
    
    auto attackRateArea = area1.removeFromLeft(width/7.0f).withSizeKeepingCentre(80, 100);
    attackRateLabel.setBounds(attackRateArea.removeFromTop(20));
    attackRateKnob.setBounds(attackRateArea);
    
    auto attackShapeArea = area1.removeFromLeft(width/7.0f).withSizeKeepingCentre(80, 100);
    attackShapeLabel.setBounds(attackShapeArea.removeFromTop(20));
    attackShapeKnob.setBounds(attackShapeArea);

    auto decayArea = area1.removeFromLeft(width/7.0f).withSizeKeepingCentre(80, 100);
    decayLabel.setBounds(decayArea.removeFromTop(20));
    decayKnob.setBounds(decayArea);

    auto sustainArea = area1.removeFromLeft(width/7.0f).withSizeKeepingCentre(80, 100);
    sustainLabel.setBounds(sustainArea.removeFromTop(20));
    sustainKnob.setBounds(sustainArea);

    auto releaseArea = area1.removeFromLeft(width/7.0f).withSizeKeepingCentre(80, 100);
    releaseLabel.setBounds(releaseArea.removeFromTop(20));
    releaseKnob.setBounds(releaseArea);
    
    auto detuneArea = area1.removeFromLeft(width/7.0f).withSizeKeepingCentre(80, 100);
    detuneLabel.setBounds(detuneArea.removeFromTop(20));
    detuneKnob.setBounds(detuneArea);

    auto area2 = area.removeFromTop(100);

    auto typeArea = area2.removeFromLeft(width/7.0f).withSizeKeepingCentre(80, 100);
    typeLabel.setBounds(typeArea.removeFromTop(25));
    typeCombo.setBounds(typeArea.removeFromTop(20).withSizeKeepingCentre(170, 30));

    auto sharpArea = area2.removeFromLeft(width/7.0f).withSizeKeepingCentre(80, 100);
    sharpLabel.setBounds(sharpArea.removeFromTop(20));
    sharpKnob.setBounds(sharpArea);

    auto ModArea = area2.removeFromLeft(width/7.0f).withSizeKeepingCentre(80, 100);
    modLabel.setBounds(ModArea.removeFromTop(20));
    modKnob.setBounds(ModArea);
    
    auto CutoffArea = area2.removeFromLeft(width/7.0f).withSizeKeepingCentre(80, 100);
    cutoffLabel.setBounds(CutoffArea.removeFromTop(20));
    cutoffKnob.setBounds(CutoffArea);
    
    auto ResonanceArea = area2.removeFromLeft(width/7.0f).withSizeKeepingCentre(80, 100);
    resonanceLabel.setBounds(ResonanceArea.removeFromTop(20));
    ResonanceKnob.setBounds(ResonanceArea);
    
    auto BassoffArea = area2.removeFromLeft(width/7.0f).withSizeKeepingCentre(80, 100);
    bassoffLabel.setBounds(BassoffArea.removeFromTop(20));
    bassoffKnob.setBounds(BassoffArea);

    auto gainArea = area2.removeFromLeft(width/7.0f).withSizeKeepingCentre(80, 100);
    gainLabel.setBounds(gainArea.removeFromTop(20));
    gainKnob.setBounds(gainArea);
    
    auto filtAttackArea = area3.removeFromLeft(width/5.0f).withSizeKeepingCentre(80, 100);
    filtAttackLabel.setBounds(filtAttackArea.removeFromTop(20));
    filtAttackKnob.setBounds(filtAttackArea);
    
    auto filtAttackShapeArea = area3.removeFromLeft(width/5.0f).withSizeKeepingCentre(80, 100);
    filtAttackShapeLabel.setBounds(filtAttackShapeArea.removeFromTop(20));
    filtAttackShapeKnob.setBounds(filtAttackShapeArea);
    
    auto filtDecayArea = area3.removeFromLeft(width/5.0f).withSizeKeepingCentre(80, 100);
    filtDecayLabel.setBounds(filtDecayArea.removeFromTop(20));
    filtDecayKnob.setBounds(filtDecayArea);
    
    auto filtDecayShapeArea = area3.removeFromLeft(width/5.0f).withSizeKeepingCentre(80, 100);
    filtDecayShapeLabel.setBounds(filtDecayShapeArea.removeFromTop(20));
    filtDecayShapeKnob.setBounds(filtDecayShapeArea);

    area.removeFromTop(12);

    keyboardComponent.setBounds(area.removeFromBottom(80));
}






