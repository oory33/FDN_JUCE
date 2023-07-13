#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
                         ),
      parameters(*this, nullptr, juce::Identifier("Parameters"),
                 {std::make_unique<juce::AudioParameterFloat>("delayTime1", "Delay Time 1", juce::NormalisableRange<float>(0.0f, 1000.0f), 60.0f), std::make_unique<juce::AudioParameterFloat>("gain1", "Gain 1", juce::NormalisableRange<float>(0.0f, 1.0f), 0.3f),
                  std::make_unique<juce::AudioParameterFloat>("delayTime2", "Delay Time 2", juce::NormalisableRange<float>(0.0f, 1000.0f), 53.0f), std::make_unique<juce::AudioParameterFloat>("gain2", "Gain 2", juce::NormalisableRange<float>(0.0f, 1.0f), 0.6f),
                  std::make_unique<juce::AudioParameterFloat>("delayTime3", "Delay Time 3", juce::NormalisableRange<float>(0.0f, 1000.0f), 61.0f), std::make_unique<juce::AudioParameterFloat>("gain3", "Gain 3", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f),
                  std::make_unique<juce::AudioParameterFloat>("delayTime4", "Delay Time 4", juce::NormalisableRange<float>(0.0f, 1000.0f), 97.0f), std::make_unique<juce::AudioParameterFloat>("gain4", "Gain 4", juce::NormalisableRange<float>(0.0f, 1.0f), 0.4f),
                  std::make_unique<juce::AudioParameterFloat>("gainMaster", "Gain Master", juce::NormalisableRange<float>(0.0f, 1.0f), 0.6f)})
{
    delayTime1 = parameters.getRawParameterValue("delayTime1");
    gain1 = parameters.getRawParameterValue("gain1");
    delayTime2 = parameters.getRawParameterValue("delayTime2");
    gain2 = parameters.getRawParameterValue("gain2");
    delayTime3 = parameters.getRawParameterValue("delayTime3");
    gain3 = parameters.getRawParameterValue("gain3");
    delayTime4 = parameters.getRawParameterValue("delayTime4");
    gain4 = parameters.getRawParameterValue("gain4");
    gainMaster = parameters.getRawParameterValue("gainMaster");
}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor()
{
}

//==============================================================================
const juce::String AudioPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AudioPluginAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool AudioPluginAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool AudioPluginAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double AudioPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudioPluginAudioProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
              // so this should be at least 1, even if you're not really implementing programs.
}

int AudioPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudioPluginAudioProcessor::setCurrentProgram(int index)
{
    juce::ignoreUnused(index);
}

const juce::String AudioPluginAudioProcessor::getProgramName(int index)
{
    juce::ignoreUnused(index);
    return {};
}

void AudioPluginAudioProcessor::changeProgramName(int index, const juce::String &newName)
{
    juce::ignoreUnused(index, newName);
}

//==============================================================================
void AudioPluginAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused(sampleRate, samplesPerBlock);

    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 2;
    spec.sampleRate = sampleRate;

    delayLine1.prepare(spec);
    delayLine1.setMaximumDelayInSamples(sampleRate);
    delayLine2.prepare(spec);
    delayLine2.setMaximumDelayInSamples(sampleRate);
    delayLine3.prepare(spec);
    delayLine3.setMaximumDelayInSamples(sampleRate);
    delayLine4.prepare(spec);
    delayLine4.setMaximumDelayInSamples(sampleRate);
}

void AudioPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool AudioPluginAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

        // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}

void AudioPluginAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                             juce::MidiBuffer &midiMessages)
{
    juce::ignoreUnused(midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    const int numSamples = buffer.getNumSamples();
    const int sampleRate = spec.sampleRate;

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto *channelData = buffer.getWritePointer(channel);
        juce::ignoreUnused(channelData);
        // ..do something to the data...
        for (int i = 0; i < numSamples; ++i)
        {
            float delayedSample1 = delayLine1.popSample(channel, *delayTime1 * sampleRate / 1000);
            float delayedSample2 = delayLine2.popSample(channel, *delayTime2 * sampleRate / 1000);
            float delayedSample3 = delayLine3.popSample(channel, *delayTime3 * sampleRate / 1000);
            float delayedSample4 = delayLine4.popSample(channel, *delayTime4 * sampleRate / 1000);

            float data1 = 0.5f * (delayedSample1 + delayedSample2 + delayedSample3 + delayedSample4);
            float data2 = 0.5f * (delayedSample1 - delayedSample2 + delayedSample3 - delayedSample4);
            float data3 = 0.5f * (delayedSample1 + delayedSample2 - delayedSample3 - delayedSample4);
            float data4 = 0.5f * (delayedSample1 - delayedSample2 - delayedSample3 + delayedSample4);

            float delayedSampleSum = data1 * (float)*gain1 + data2 * (float)*gain2 + data3 * (float)*gain3 + data4 * (float)*gain4;

            channelData[i] = channelData[i] * (float)*gainMaster + delayedSampleSum * (1.0f - (float)*gainMaster);

            delayLine1.pushSample(channel, (channelData[i] + data1) / 2);
            delayLine2.pushSample(channel, (channelData[i] + data2) / 2);
            delayLine3.pushSample(channel, (channelData[i] + data3) / 2);
            delayLine4.pushSample(channel, (channelData[i] + data4) / 2);
        }
    }
}

//==============================================================================
bool AudioPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *AudioPluginAudioProcessor::createEditor()
{
    return new AudioPluginAudioProcessorEditor(*this, parameters);
}

//==============================================================================
void AudioPluginAudioProcessor::getStateInformation(juce::MemoryBlock &destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused(destData);
}

void AudioPluginAudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused(data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPluginAudioProcessor();
}
