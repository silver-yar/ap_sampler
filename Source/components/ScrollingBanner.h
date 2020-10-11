/*
  ==============================================================================

    ScrollingBanner.h
    Created: 10 Oct 2020 7:47:43pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../styling/PirateStyle.h"

//==============================================================================
/*
*/
class ScrollingBanner  : public juce::Component,
                         public Timer
{
public:
    ScrollingBanner();
    ~ScrollingBanner() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    Random randomInt_;
    Bezel bezel_;
    Glare glare_;

    int index_, x_, y_ = 0;
    int textWidth_ = 100;
    String bannerMessages_ [3] {"audio_pirate", "ap_sampler", "$!@#*^&"};
    DrawableText scrollText_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScrollingBanner)
};
