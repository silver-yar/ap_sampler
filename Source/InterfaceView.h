/*
  ==============================================================================

    InterfaceView.h
    Created: 1 Jun 2020 7:51:01pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class InterfaceView    : public Component
{
public:
    InterfaceView(Ap_samplerAudioProcessor&);
    ~InterfaceView();

    void paint (Graphics&) override;
    void resized() override;

private:
    Ap_samplerAudioProcessor& processor;

    MidiKeyboardComponent keyboard_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InterfaceView)
};
