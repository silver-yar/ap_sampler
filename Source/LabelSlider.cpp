/*
  =============================================================================

    LabelSlider.cpp
    Created: 24 Sep 2020 11:35:41p
    Author:  Johnathan Handy

  =============================================================================
*/

#include <JuceHeader.h>
#include "LabelSlider.h"

//=============================================================================
LabelSlider::LabelSlider()
{
    slider.setSliderStyle (Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle (Slider::TextBoxBelow, true,
                             slider.getTextBoxWidth(), slider.getTextBoxHeight());
    slider.setLookAndFeel(&pirateSliderStyle);
    addAndMakeVisible (slider);

    label.setJustificationType (Justification::centred);
    label.setLookAndFeel (&pirateSliderStyle);
    addAndMakeVisible (label);
}

LabelSlider::~LabelSlider()
{
    slider.setLookAndFeel (nullptr);
    label.setLookAndFeel (nullptr);
}

void LabelSlider::paint (juce::Graphics& g)
{
    switch (current_state) {
        case SliderState::enabled:
            setAlpha (1.0f);
            break;
        case SliderState::disabled:
            setAlpha (0.3f);
            break;
        default:
            break;
    }
}

void LabelSlider::resized()
{
    auto localBounds = getLocalBounds();
    auto label_ratio = 0.2;

    label.setBounds (localBounds.removeFromTop (localBounds.getHeight() * label_ratio));
    slider.setBounds (localBounds);
}

void LabelSlider::setOnDoubleClick(const std::function<void()> onDoubleClick)
{
    slider.onDoubleClick = onDoubleClick;
}

//void LabelSlider::mouseDoubleClick(const MouseEvent &e) {
//    auto bounds = getLocalBounds();
//    DBG("Slider clicked.");
//
//    if (bounds.contains (e.getMouseDownPosition())) {
//        DBG("Slider clicked.");
//        switch (current_state) {
//            case SliderState::enabled:
//                setDisabled();
//                repaint();
//                DBG("disabled.");
//                break;
//            case SliderState::disabled:
//                setEnabled();
//                repaint();
//                DBG("enabled.");
//                break;
//            default:
//                break;
//        }
//    }
//}

