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
class Ap_samplerAudioProcessor  : public AudioProcessor
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
    MidiKeyboardState& getKeyboardState() { return keystate_; }
    String& getFileName() { return fileName_; }
    AudioBuffer<float>& getWaveForm() { return waveform_; };
    std::atomic<int>& getSampleCount() { return sampleCount_; };

    void loadFile (const String& path);
private:
    //==============================================================================
    Synthesiser sampler_;
    const int numVoices_ { 3 };
    std::atomic<bool> isPlayed_ {false }; // atomic because updated on process block
    std::atomic<int> sampleCount_ {0 };
    AudioBuffer<float> waveform_;
    AudioFormatManager formatManager_;
    String fileName_;
    MidiKeyboardState keystate_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Ap_samplerAudioProcessor)
};
