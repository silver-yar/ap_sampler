/*
  ==============================================================================

    InfoScreen.h
    Created: 10 Jun 2020 7:07:09pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class InfoScreen    : public Component,
                      public Button::Listener
{
public:
    InfoScreen(Ap_samplerAudioProcessor&);
    ~InfoScreen();

    void paint (Graphics&) override;
    void resized() override;

    //==============================================================================
    void mouseDown (const MouseEvent& e) override;
    void buttonClicked (Button* button) override;
    void drawGroupName (Graphics&);
    std::function<void()> onNameClicked = nullptr;

private:
    //String grpName_ [3] { "adsr_", "filter_", "misc_" };
    //int groupIndex_ { 0 };
    std::unique_ptr<ToggleButton> hideButton_;

    Ap_samplerAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InfoScreen)
};
