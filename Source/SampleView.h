/*
  ==============================================================================

    SampleView.h
    Created: 1 Jun 2020 8:47:27pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class SampleView    : public Component,
                      public Timer
{
public:
    SampleView(Ap_samplerAudioProcessor&);
    ~SampleView();

    void paint (Graphics&) override;
    void resized() override;

    void setFileLoaded (bool loaded) { fileLoaded_ = loaded; }
    void drawWaveform(Graphics&);
    void timerCallback() override;

private:
    // Colours
    Colour green1_ {0xff94d17d};
    Colour green2_ {0xff398020};
    bool fileLoaded_ { false };
    std::vector<float> audioPoints_;
    Ap_samplerAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SampleView)
};
