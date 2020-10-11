/*
  ==============================================================================

    InfoScreen.h
    Created: 10 Jun 2020 7:07:09pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "APButton.h"
#include "../styling/PirateStyle.h"

//==============================================================================
/*
*/
class InfoScreen    : public Component
{
public:
    InfoScreen(Ap_samplerAudioProcessor&);
    ~InfoScreen();

    void paint (Graphics&) override;
    void resized() override;

    //==============================================================================
    void mouseDown (const MouseEvent& e) override;
    void drawGroupName (Graphics&);
    std::function<void()> onNameClicked = nullptr;

    String group_label = "adsr";
private:
    APButton hideButton_;
    Bezel bezel_;
    Glare glare_;

    Ap_samplerAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InfoScreen)
};
