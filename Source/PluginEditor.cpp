
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
waylosynth2AudioProcessorEditor::waylosynth2AudioProcessorEditor (waylosynth2& p,
                                                                                                  AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState (vts),
      keyboardComponent (p.keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
    setSize (800, 400);

    setLookAndFeel(&plugexLookAndFeel);
    plugexLookAndFeel.setTheme("lightgreen");

    title.setText("Plugex - 38 - Waveform Midi Synth", NotificationType::dontSendNotification);
    title.setFont(title.getFont().withPointHeight(title.getFont().getHeightInPoints() + 4));
    title.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&title);

    attackLabel.setText("Attack", NotificationType::dontSendNotification);
    attackLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&attackLabel);

    attackKnob.setLookAndFeel(&plugexLookAndFeel);
    attackKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    attackKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&attackKnob);

    attackAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "attack", attackKnob));

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

    typeLabel.setText("Wave Type", NotificationType::dontSendNotification);
    typeLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&typeLabel);

    typeCombo.setLookAndFeel(&plugexLookAndFeel);
    typeCombo.addItemList({"FM_Feedback_1", "Pulse Wave", "2_OP_FM", "Sawtooth", "Fixed_Pulse", "Sin_w_Feedback", "2_OP_version2", "Tan_of_Sin", "patrice_blep"}, 1);
    typeCombo.setSelectedId(1);
    addAndMakeVisible(&typeCombo);

    typeAttachment.reset(new AudioProcessorValueTreeState::ComboBoxAttachment(valueTreeState, "type", typeCombo));

    sharpLabel.setText("Bright", NotificationType::dontSendNotification);
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

    gainLabel.setText("Gain", NotificationType::dontSendNotification);
    gainLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&gainLabel);

    gainKnob.setLookAndFeel(&plugexLookAndFeel);
    gainKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    gainKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&gainKnob);

    gainAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "gain", gainKnob));

    addAndMakeVisible(keyboardComponent);
}

waylosynth2AudioProcessorEditor::~waylosynth2AudioProcessorEditor()
{
    attackKnob.setLookAndFeel(nullptr);
    decayKnob.setLookAndFeel(nullptr);
    sustainKnob.setLookAndFeel(nullptr);
    releaseKnob.setLookAndFeel(nullptr);
    typeCombo.setLookAndFeel(nullptr);
    sharpKnob.setLookAndFeel(nullptr);
    modKnob.setLookAndFeel(nullptr);
    gainKnob.setLookAndFeel(nullptr);
}

//==============================================================================
void waylosynth2AudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void waylosynth2AudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(12, 12);
    float width = area.getWidth();

    title.setBounds(area.removeFromTop(36));
    area.removeFromTop(12);

    auto area1 = area.removeFromTop(100);

    auto attackArea = area1.removeFromLeft(width/4.0f).withSizeKeepingCentre(80, 100);
    attackLabel.setBounds(attackArea.removeFromTop(20));
    attackKnob.setBounds(attackArea);

    auto decayArea = area1.removeFromLeft(width/4.0f).withSizeKeepingCentre(80, 100);
    decayLabel.setBounds(decayArea.removeFromTop(20));
    decayKnob.setBounds(decayArea);

    auto sustainArea = area1.removeFromLeft(width/4.0f).withSizeKeepingCentre(80, 100);
    sustainLabel.setBounds(sustainArea.removeFromTop(20));
    sustainKnob.setBounds(sustainArea);

    auto releaseArea = area1.removeFromLeft(width/4.0f).withSizeKeepingCentre(80, 100);
    releaseLabel.setBounds(releaseArea.removeFromTop(20));
    releaseKnob.setBounds(releaseArea);

    auto area2 = area.removeFromTop(140);

    auto typeArea = area2.removeFromLeft(width/4.0f).withSizeKeepingCentre(80, 100);
    typeLabel.setBounds(typeArea.removeFromTop(20));
    typeCombo.setBounds(typeArea.removeFromTop(20).withSizeKeepingCentre(200, 24));

    auto sharpArea = area2.removeFromLeft(width/4.0f).withSizeKeepingCentre(80, 100);
    sharpLabel.setBounds(sharpArea.removeFromTop(20));
    sharpKnob.setBounds(sharpArea);
    
    auto ModArea = area2.removeFromLeft(width/4.0f).withSizeKeepingCentre(80, 100);
    modLabel.setBounds(ModArea.removeFromTop(20));
    modKnob.setBounds(ModArea);

    auto gainArea = area2.removeFromLeft(width/4.0f).withSizeKeepingCentre(80, 100);
    gainLabel.setBounds(gainArea.removeFromTop(20));
    gainKnob.setBounds(gainArea);

    area.removeFromTop(12);

    keyboardComponent.setBounds(area.removeFromBottom(80));
}
