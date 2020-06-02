/*
  ==============================================================================

    SampleView.h
    Created: 1 Jun 2020 8:47:27pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SampleView    : public Component
{
public:
    SampleView();
    ~SampleView();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SampleView)
};
