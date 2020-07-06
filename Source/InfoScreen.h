/*
  ==============================================================================

    InfoScreen.h
    Created: 10 Jun 2020 7:07:09pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class InfoScreen    : public Component
{
public:
    InfoScreen();
    ~InfoScreen();

    void paint (Graphics&) override;
    void resized() override;

private:
    String grpName_ {"adsr_"};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InfoScreen)
};
