/*
  ==============================================================================

    APButton.h
    Created: 10 Oct 2020 5:20:32pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class APButton  : public juce::Button
{
public:
    APButton(const String &buttonName);
    ~APButton() override;

    void paintButton (Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    void toggleButtonState() { state_ = !state_; }

private:
    bool state_ { false };
    std::unique_ptr<Font> myFont_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (APButton)
};
