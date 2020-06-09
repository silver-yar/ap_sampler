/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Ap_samplerAudioProcessor::Ap_samplerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    formatManager_.registerBasicFormats();
    for (int i = 0; i < numVoices_; i++)
    {
        sampler_.addVoice(new SamplerVoice());
    }
}

Ap_samplerAudioProcessor::~Ap_samplerAudioProcessor()
{
}

//==============================================================================
const String Ap_samplerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Ap_samplerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Ap_samplerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Ap_samplerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Ap_samplerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Ap_samplerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Ap_samplerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Ap_samplerAudioProcessor::setCurrentProgram (int index)
{
}

const String Ap_samplerAudioProcessor::getProgramName (int index)
{
    return {};
}

void Ap_samplerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Ap_samplerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    sampler_.setCurrentPlaybackSampleRate(sampleRate);
}

void Ap_samplerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Ap_samplerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Ap_samplerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto numSamples = buffer.getNumSamples();

    keystate_.processNextMidiBuffer(midiMessages, 0, numSamples, true);

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    MidiMessage m;
    MidiBuffer::Iterator it { midiMessages };
    int sample;

    while (it.getNextEvent (m, sample))
    {
        if (m.isNoteOn())
            isPlayed_ = true;
        else if (m.isNoteOff())
            isPlayed_ = false;
    }

    sampleCount_ = isPlayed_ ? sampleCount_ += numSamples : 0;

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        sampler_.renderNextBlock(buffer, midiMessages, 0, numSamples);
    }
}

//==============================================================================
bool Ap_samplerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Ap_samplerAudioProcessor::createEditor()
{
    return new Ap_samplerAudioProcessorEditor (*this);
}

//==============================================================================
void Ap_samplerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Ap_samplerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void Ap_samplerAudioProcessor::loadFile (const String& path)
{
    sampler_.clearSounds();

    auto file = File (path);
    fileName_ = file.getFileName();
    std::unique_ptr<AudioFormatReader> formatReader{formatManager_.createReaderFor(file) };

    auto sampleLength = static_cast<int>(formatReader->lengthInSamples);
    waveform_.setSize(1, sampleLength);

    if (formatReader)
    {
        BigInteger range;
        range.setRange(0,128,true);

        sampler_.addSound(new SamplerSound(
                "Sample",
                *formatReader,
                range,
                60,
                0.1,
                1.0,
                60));
        //updateSampleRate();
    }

    formatReader->read(&waveform_,
                       0,
                       sampleLength,
                       0,
                       true,
                       false);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Ap_samplerAudioProcessor();
}
