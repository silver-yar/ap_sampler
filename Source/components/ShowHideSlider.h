/*
  ==============================================================================

    ShowHideSlider.h
    Created: 1 Oct 2020 6:42:42pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ShowHideSlider  : public Slider
{
public:
    ShowHideSlider();

    ~ShowHideSlider() override;

    //==============================================================================
    void mouseDoubleClick (const MouseEvent& e) override;

    std::function<void()> onDoubleClick = nullptr;

private:
    //LabelSlider::SliderState& state_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ShowHideSlider)
};
