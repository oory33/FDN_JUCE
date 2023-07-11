#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &p, juce::AudioProcessorValueTreeState &vts)
    : AudioProcessorEditor(&p), processorRef(p), valueTreeState(vts)
{
    juce::ignoreUnused(processorRef);
    delayTime1Attachment.reset(new SliderAttachment(valueTreeState, "delayTime1", delayTime1_Slider));
    delayTime1_Slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    delayTime1_Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, width * 2 / 5, delayTime1_Area.getHeight() / 3);
    addAndMakeVisible(delayTime1_Slider);

    gain1Attachment.reset(new SliderAttachment(valueTreeState, "gain1", gain1_Slider));
    gain1_Slider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    gain1_Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, width * 2 / 5, gain1_Area.getHeight() / 5);
    addAndMakeVisible(gain1_Slider);

    delayTime2Attachment.reset(new SliderAttachment(valueTreeState, "delayTime2", delayTime2_Slider));
    delayTime2_Slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    delayTime2_Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, width * 2 / 5, delayTime2_Area.getHeight() / 3);
    addAndMakeVisible(delayTime2_Slider);

    gain2Attachment.reset(new SliderAttachment(valueTreeState, "gain2", gain2_Slider));
    gain2_Slider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    gain2_Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, width * 2 / 5, gain2_Area.getHeight() / 5);
    addAndMakeVisible(gain2_Slider);

    delayTime3Attachment.reset(new SliderAttachment(valueTreeState, "delayTime3", delayTime3_Slider));
    delayTime3_Slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    delayTime3_Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, width * 2 / 5, delayTime3_Area.getHeight() / 3);
    addAndMakeVisible(delayTime3_Slider);

    gain3Attachment.reset(new SliderAttachment(valueTreeState, "gain3", gain3_Slider));
    gain3_Slider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    gain3_Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, width * 2 / 5, gain3_Area.getHeight() / 5);
    addAndMakeVisible(gain3_Slider);

    delayTime4Attachment.reset(new SliderAttachment(valueTreeState, "delayTime4", delayTime4_Slider));
    delayTime4_Slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    delayTime4_Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, width * 2 / 5, delayTime4_Area.getHeight() / 3);
    addAndMakeVisible(delayTime4_Slider);

    gain4Attachment.reset(new SliderAttachment(valueTreeState, "gain4", gain4_Slider));
    gain4_Slider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    gain4_Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, width * 2 / 5, gain4_Area.getHeight() / 5);
    addAndMakeVisible(gain4_Slider);

    gainMasterAttachment.reset(new SliderAttachment(valueTreeState, "gainMaster", gainMaster_Slider));
    gainMaster_Slider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    gainMaster_Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, width * 2 / 5, gainMaster_Area.getHeight() / 5);
    addAndMakeVisible(gainMaster_Slider);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(width, height);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colour::fromRGB(46, 52, 64));
    g.fillRect(delayTime1_Area.toFloat());
    g.fillRect(gain1_Area.toFloat());
    g.fillRect(delayTime2_Area.toFloat());
    g.fillRect(gain2_Area.toFloat());
    g.fillRect(delayTime3_Area.toFloat());
    g.fillRect(gain3_Area.toFloat());
    g.fillRect(delayTime4_Area.toFloat());
    g.fillRect(gain4_Area.toFloat());
    g.fillRect(gainMaster_Area.toFloat());
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    delayTime1_Slider.setBounds(delayTime1_Area.reduced(5));
    gain1_Slider.setBounds(gain1_Area.reduced(5));
    delayTime2_Slider.setBounds(delayTime2_Area.reduced(5));
    gain2_Slider.setBounds(gain2_Area.reduced(5));
    delayTime3_Slider.setBounds(delayTime3_Area.reduced(5));
    gain3_Slider.setBounds(gain3_Area.reduced(5));
    delayTime4_Slider.setBounds(delayTime4_Area.reduced(5));
    gain4_Slider.setBounds(gain4_Area.reduced(5));
    gainMaster_Slider.setBounds(gainMaster_Area.reduced(5));
}
