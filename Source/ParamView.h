/*
  ==============================================================================

    ParamView.h
    Created: 1 Jun 2020 8:47:45pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ParamView    : public Component
{
public:
    ParamView();
    ~ParamView();

    void paint (Graphics&) override;
    void resized() override;

private:
    Colour orange1_ { 0xfff79256 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParamView)
};
