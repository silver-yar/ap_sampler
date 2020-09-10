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

    //==============================================================================
    void drawWaveform (Graphics&);
    void drawFileName (Graphics&);
    void drawADSR (Graphics&);
    void drawFilter (Graphics&);
    void timerCallback() override;

    void mouseDown (const MouseEvent& e) override;

private:

    // Objects
    std::vector<float> audioPoints_;
    std::vector<float> adsrPoints_;
    FileChooser fileChooser_ {"Choose a sample..."};

    Ap_samplerAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SampleView)
};
