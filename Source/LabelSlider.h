/*
  =============================================================================

    LabelSlider.h
    Created: 24 Sep 2020 11:35:41p
    Author:  Johnathan Handy

  =============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PirateStyle.h"

//=============================================================================

class LabelSlider  : public juce::Component
{
public:
    LabelSlider();
    ~LabelSlider() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    Label label;
    Slider slider;
    PirateStyle pirateSliderStyle;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LabelSlider)
};

