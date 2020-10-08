/*
  ==============================================================================

    PirateSlider.h
    Created: 10 Jun 2020 6:59:14pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class PirateStyle : public LookAndFeel_V4
{
public:
    PirateStyle() = default;

    void drawRotarySlider (Graphics&, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle,
                           float rotaryEndAngle, Slider&) override;
    void drawLabel (Graphics&, Label&) override;
    static void drawBezel (Graphics& g, float width, float height, float lineThickness);

private:
    struct knobImages
    {
        knobImages (Image bg, Image fg) : backgroundImage {bg}, foregroundImage {fg} {}
        knobImages (const knobImages& src) = default;
        knobImages (knobImages&& src) = default;

        Image backgroundImage;
        Image foregroundImage;
    };
    std::map<int, knobImages> knobsBgs;
    int knobsMaxSize {6};

    // hardcoded colors for the knobs
    const Colour whiteA010 = Colours::white.withAlpha (uint8 ( 10));
    const Colour whiteA042 = Colours::white.withAlpha (uint8 ( 42));
    const Colour blackA042 = Colours::black.withAlpha (uint8 ( 42));
    const Colour blackA092 = Colours::black.withAlpha (uint8 ( 92));
    const Colour blackA122 = Colours::black.withAlpha (uint8 (122));
    const Colour blackA142 = Colours::black.withAlpha (uint8 (142));

    knobImages& getKnobImages (int diameter);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PirateStyle)
};