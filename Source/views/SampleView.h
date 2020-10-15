/*
  ==============================================================================

    SampleView.h
    Created: 1 Jun 2020 8:47:27pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "../components/SpectrumAnalyser.h"
#include "../styling/PirateStyle.h"

//==============================================================================
/*
*/
class SampleView    : public Component,
                      public Timer,
                      public ChangeListener
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
    void drawAxis (Graphics&);
    void drawFilter (Graphics&);
    void timerCallback() override;

    void mouseDown (const MouseEvent& e) override;
    void changeListenerCallback (ChangeBroadcaster *source) override;

private:
    Ap_samplerAudioProcessor& processor;

    std::function<void(Graphics&)> toDraw_ = [this](Graphics& g) { drawWaveform(g); };

    // Objects
    SpectrumAnalyser spectrum_;
    Bezel bezel_;
    Glare glare_;

    std::vector<float> audioPoints_;
    std::vector<float> adsrPoints_;
    FileChooser fileChooser_ {"Choose a sample..."};
    std::unique_ptr<Font> myFont_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SampleView)
};
