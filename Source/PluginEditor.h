/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "InterfaceView.h"

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
    Rectangle<float> shadow_bounds_ {0.0f, 0.0f, 800.0f, 50.0f};

    // Colour Palette
    Colour main_blue_{ 0xff3056bf };
    Colour sec_blue_{0xff203980};

    // Child Components
    InterfaceView interface_;

    Ap_samplerAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Ap_samplerAudioProcessorEditor)
};
