/*
  ==============================================================================

    AnimatedArrow.h
    Created: 16 Oct 2020 5:25:11pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AnimatedArrow  : public juce::Component,
                       public Timer
{
public:
    AnimatedArrow();
    ~AnimatedArrow() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    float index_ = 0;
    float x_ = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnimatedArrow)
};
