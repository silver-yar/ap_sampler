/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class Ap_samplerAudioProcessor  : public AudioProcessor,
                                  public ValueTree::Listener
{
public:
    //==============================================================================
    Ap_samplerAudioProcessor();
    ~Ap_samplerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    // ValueTree
    AudioProcessorValueTreeState apvts;
    ADSR::Parameters adsrParams;

    bool hideEnv { false };

    // Enums
    enum FilterType {
        low_pass,
        high_pass,
        band_pass
    };
    enum GroupName {
        adsr,
        filter
    };
    enum fft
    {
        fftOrder = 11,
        fftSize = 1 << fftOrder
    };
    GroupName curr_group = GroupName::adsr;

    // Getters
    MidiKeyboardState& getKeyboardState() { return keystate_; }
    String& getFileName() { return fileName_; }
    AudioBuffer<float>& getWaveForm() { return waveform_; };
    std::atomic<int>& getSampleCount() { return sampleCount_; }
    FilterType getFilterType() { return filter_type; }
    float* getFFTData() { return fftData_; }
    bool isFFTBlockReady() { return nextFFTBlockReady_; }

    // Setters
    void setFilterType (FilterType type) { filter_type = type; }
    void setFFTBlockReady(bool isReady) { nextFFTBlockReady_ = isReady; }

    // Apply IIR filtering to samples in buffer
    void filterSample (int channel, float* channelData, int numSamples);
    // Push samples into fifo for fft
    void pushNextSampleIntoFifo (float sample);
    void loadFile (const String& path);
    // Passes the sample rate and buffer size to DSP
    void prepare (double sampleRate, int samplesPerBlock);
    // Updates DSP when user changes parameters
    void update();
    // Overrides AudioProcessor reset, reset DSP parameters
    void reset() override;
    // Create parameter layout for apvts
    AudioProcessorValueTreeState::ParameterLayout createParameters();

private:
    //==============================================================================
    Synthesiser sampler_;
    const int numVoices_ { 3 };
    bool mustUpdateProcessing_ { false }, isActive_ { false };
    std::atomic<bool> isPlayed_ {false }; // atomic because updated on process block
    std::atomic<int> sampleCount_ { 0 };
    AudioBuffer<float> waveform_;
    AudioFormatManager formatManager_;
    String fileName_ { "" };
    MidiKeyboardState keystate_;

    // Filter Params
    IIRFilter lowPass_ [2];
    IIRFilter bandPass_ [2];
    IIRFilter highPass_ [2];
    FilterType filter_type { FilterType::low_pass };

    // FFT
    float fifo_ [fftSize];
    float fftData_ [2 * fftSize];
    int fifoIndex_ { 0 };
    bool nextFFTBlockReady_ { false };

    // Callback for DSP parameter changes
    void valueTreePropertyChanged (ValueTree& treeWhosePropertyChanged, const Identifier& property) override
    {
        mustUpdateProcessing_ = true;
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Ap_samplerAudioProcessor)
};
