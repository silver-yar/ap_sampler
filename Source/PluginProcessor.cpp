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
, apvts(*this, nullptr, "Parameters", createParameters())
{
    apvts.state.addListener (this);
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
    update();
    reset();
    isActive_ = true;
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
    if (!isActive_) return;
    if (mustUpdateProcessing_) update();

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

    sampler_.renderNextBlock (buffer, midiMessages, 0, numSamples);

    for (int channel = 0; channel < totalNumInputChannels; ++channel) {
        auto* channelData = buffer.getWritePointer (channel);
        filterSample (channel, channelData, numSamples);

        for (int sample = 0; sample < numSamples; ++sample)
            pushNextSampleIntoFifo (channelData[sample]);
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
    // Save state information to xml -> binary to retrieve on startup
    ValueTree copyState = apvts.copyState();
    std::unique_ptr<XmlElement> xml = copyState.createXml();
    copyXmlToBinary (*xml, destData);
}

void Ap_samplerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xml = getXmlFromBinary (data, sizeInBytes);
    ValueTree copyState = ValueTree::fromXml (*xml);
    apvts.replaceState (copyState);
}

void Ap_samplerAudioProcessor::filterSample(int channel, float* channelData, int numSamples)
{
    switch (filter_type) {
        case FilterType::low_pass:
            lowPass_[channel].processSamples (channelData, numSamples);
            break;
        case FilterType::band_pass:
            bandPass_[channel].processSamples (channelData, numSamples);
            break;
        case FilterType::high_pass:
            highPass_[channel].processSamples (channelData, numSamples);
            break;
        default:
            break;
    }
}

void Ap_samplerAudioProcessor::pushNextSampleIntoFifo(float sample) {
    if (fifoIndex_ == fftSize) {
        if (!nextFFTBlockReady_) {
            zeromem (fftData_, sizeof (fftData_));
            memcpy (fftData_, fifo_, sizeof (fifo_));
            nextFFTBlockReady_ = true;
        }
        fifoIndex_ = 0;
    }
    fifo_[fifoIndex_++] = sample;
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
                0.0,
                0.0,
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

void Ap_samplerAudioProcessor::prepare(double sampleRate, int samplesPerBlock) {

}

void Ap_samplerAudioProcessor::update() {
    // Updates DSP when user changes parameters
    mustUpdateProcessing_ = false;
    auto numChannels = 2;

    adsrParams.attack = apvts.getRawParameterValue ("ATT") -> load();
    adsrParams.decay = apvts.getRawParameterValue ("DEC") -> load();
    adsrParams.sustain = apvts.getRawParameterValue ("SUS") -> load();
    adsrParams.release = apvts.getRawParameterValue ("REL") -> load();

    auto lowFreq = apvts.getRawParameterValue ("LPF") -> load();
    auto bandFreq = apvts.getRawParameterValue ("BPF") -> load();
    auto highFreq = apvts.getRawParameterValue ("HPF") -> load();

    for (int channel = 0; channel < numChannels; ++channel) {
        lowPass_[channel].setCoefficients (IIRCoefficients::makeLowPass (getSampleRate(), lowFreq));
        bandPass_[channel].setCoefficients (IIRCoefficients::makeBandPass (getSampleRate(), bandFreq));
        highPass_[channel].setCoefficients (IIRCoefficients::makeHighPass (getSampleRate(), highFreq));
    }

    for (auto i = 0; i < sampler_.getNumSounds(); ++i)
    {
        if (auto sound = dynamic_cast<SamplerSound*>(sampler_.getSound(i).get())) {
            sound->setEnvelopeParameters(adsrParams);
        }
    }
}

void Ap_samplerAudioProcessor::reset() {
    auto numChannels = 2;

    for (int channel = 0; channel < numChannels; ++channel) {
        lowPass_[channel].reset();
        bandPass_[channel].reset();
        highPass_[channel].reset();
    }
}

AudioProcessorValueTreeState::ParameterLayout Ap_samplerAudioProcessor::createParameters() {
// Create parameter layout for apvts
    std::vector<std::unique_ptr<RangedAudioParameter>> parameters;

    auto valueToTextFunction = [](float val, int len) { return String(val, len); };
    auto textToValueFunction = [](const String& text) { return text.getFloatValue(); };

    // **Attack Parameter** - in s
    parameters.emplace_back (std::make_unique<AudioParameterFloat>(
            "ATT",
            "Attack",
            NormalisableRange<float>(0.0f, 5.0f, 0.01f),
            0.0f,
            "s",
            AudioProcessorParameter::genericParameter,
            valueToTextFunction,
            textToValueFunction
    ));

    // **Decay Parameter** - in s
    parameters.emplace_back (std::make_unique<AudioParameterFloat>(
            "DEC",
            "Decay",
            NormalisableRange<float>(0.0f, 5.0f, 0.01f),
            2.0f,
            "s",
            AudioProcessorParameter::genericParameter,
            valueToTextFunction,
            textToValueFunction
    ));

    // **Sustain Parameter** - in dB
    parameters.emplace_back (std::make_unique<AudioParameterFloat>(
            "SUS",
            "Sustain",
            NormalisableRange<float>(-60.0f, 0.0f, 0.01f),
            0.0f,
            "dB",
            AudioProcessorParameter::genericParameter,
            valueToTextFunction,
            textToValueFunction
    ));

    // **Release Parameter** - in s
    parameters.emplace_back (std::make_unique<AudioParameterFloat>(
            "REL",
            "Release",
            NormalisableRange<float>(0.0f, 5.0f, 0.01f),
            0.0f,
            "s",
            AudioProcessorParameter::genericParameter,
            valueToTextFunction,
            textToValueFunction
    ));

    // **Low Pass Parameter** - in Hz
    parameters.emplace_back (std::make_unique<AudioParameterFloat>(
            "LPF",
            "Low Pass Filter",
            NormalisableRange<float>(20.0f, 22000.0f, 10.0f, 0.2f),
            20000.0f,
            "Hz",
            AudioProcessorParameter::genericParameter,
            valueToTextFunction,
            textToValueFunction
    ));

    // **Band Pass Parameter** - in Hz
    parameters.emplace_back (std::make_unique<AudioParameterFloat>(
            "BPF",
            "Band Pass Filter",
            NormalisableRange<float>(20.0f, 22000.0f, 10.0f, 0.2f),
            20000.0f,
            "Hz",
            AudioProcessorParameter::genericParameter,
            valueToTextFunction,
            textToValueFunction
    ));

    // **High Pass Parameter** - in Hz
    parameters.emplace_back (std::make_unique<AudioParameterFloat>(
            "HPF",
            "High Pass Filter",
            NormalisableRange<float>(20.0f, 22000.0f, 10.0f, 0.2f),
            50.0f,
            "Hz",
            AudioProcessorParameter::genericParameter,
            valueToTextFunction,
            textToValueFunction
    ));

    return { parameters.begin(), parameters.end() };
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Ap_samplerAudioProcessor();
}
