#pragma once

#include "PluginProcessor.h"

//==============================================================================
class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &, juce::AudioProcessorValueTreeState &vts);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics &) override;
    void resized() override;

private:
    int width = 400;
    int height = 600;
    juce::Rectangle<int> delayTime1_Area = {width, height * 1 / 5 - 30};
    juce::Rectangle<int> gain1_Area = {0, delayTime1_Area.getBottom(), width, height / 9 - 30};
    juce::Rectangle<int> delayTime2_Area = {0, gain1_Area.getBottom(), width, height / 5 - 30};
    juce::Rectangle<int> gain2_Area = {0, delayTime2_Area.getBottom(), width, height / 9 - 30};
    juce::Rectangle<int> delayTime3_Area = {0, gain2_Area.getBottom(), width, height / 5 - 30};
    juce::Rectangle<int> gain3_Area = {0, delayTime3_Area.getBottom(), width, height / 9 - 30};
    juce::Rectangle<int> delayTime4_Area = {0, gain3_Area.getBottom(), width, height / 5 - 30};
    juce::Rectangle<int> gain4_Area = {0, delayTime4_Area.getBottom(), width, height / 9 - 30};

    juce::Rectangle<int> gainMaster_Area = {0, gain4_Area.getBottom(), width, height / 7 - 30};

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor &processorRef;

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    juce::AudioProcessorValueTreeState &valueTreeState;

    juce::Slider delayTime1_Slider;
    std::unique_ptr<SliderAttachment> delayTime1Attachment;
    juce::Slider gain1_Slider;
    std::unique_ptr<SliderAttachment> gain1Attachment;

    juce::Slider delayTime2_Slider;
    std::unique_ptr<SliderAttachment> delayTime2Attachment;
    juce::Slider gain2_Slider;
    std::unique_ptr<SliderAttachment> gain2Attachment;

    juce::Slider delayTime3_Slider;
    std::unique_ptr<SliderAttachment> delayTime3Attachment;
    juce::Slider gain3_Slider;
    std::unique_ptr<SliderAttachment> gain3Attachment;

    juce::Slider delayTime4_Slider;
    std::unique_ptr<SliderAttachment> delayTime4Attachment;
    juce::Slider gain4_Slider;
    std::unique_ptr<SliderAttachment> gain4Attachment;

    juce::Slider gainMaster_Slider;
    std::unique_ptr<SliderAttachment> gainMasterAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
