#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>

//==============================================================================
class AudioPluginAudioProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    AudioPluginAudioProcessor();
    ~AudioPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;

    void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor *createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String &newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock &destData) override;
    void setStateInformation(const void *data, int sizeInBytes) override;

private:
    //==============================================================================
    juce::AudioProcessorValueTreeState parameters;

    std::atomic<float> *delayTime1 = nullptr;
    std::atomic<float> *gain1 = nullptr;
    std::atomic<float> *delayTime2 = nullptr;
    std::atomic<float> *gain2 = nullptr;
    std::atomic<float> *delayTime3 = nullptr;
    std::atomic<float> *gain3 = nullptr;
    std::atomic<float> *delayTime4 = nullptr;
    std::atomic<float> *gain4 = nullptr;

    std::atomic<float> *gainMaster = nullptr;

    juce::dsp::DelayLine<float> delayLine1;
    juce::dsp::DelayLine<float> delayLine2;
    juce::dsp::DelayLine<float> delayLine3;
    juce::dsp::DelayLine<float> delayLine4;

    juce::dsp::ProcessSpec spec;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessor)
};
