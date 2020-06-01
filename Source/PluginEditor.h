/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MainWindow.h"

//==============================================================================
/**
*/
class Ap_samplerAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Ap_samplerAudioProcessorEditor (Ap_samplerAudioProcessor&);
    ~Ap_samplerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:

    Ap_samplerAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Ap_samplerAudioProcessorEditor)
};
