/*
  =============================================================================

    LabelSlider.h
    Created: 24 Sep 2020 11:35:41p
    Author:  Johnathan Handy

  =============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../styling/PirateStyle.h"
#include "./ShowHideSlider.h"

//=============================================================================
class LabelSlider : public Component {
public:
    LabelSlider();
    ~LabelSlider() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    //==============================================================================
    // TODO: consider using juce setEnabled && override enablement changed for repaint
    void setDisabled ()
    {
        current_state = SliderState::disabled;
        repaint();
    }
    void setEnabled ()
    {
        current_state = SliderState::enabled;
        repaint();
    }
    void setOnDoubleClick (const std::function<void()>& onDoubleClick);
    //void mouseDoubleClick (const MouseEvent& e) override;

    Label label;
    ShowHideSlider slider;
    PirateStyle pirateSliderStyle;

    enum SliderState {
        enabled,
        disabled
    };
private:
    SliderState current_state = SliderState::enabled;
    std::unique_ptr<Font> myFont_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LabelSlider)
};

