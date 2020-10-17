/*
  ==============================================================================

    PirateSlider.h
    Created: 10 Jun 2020 6:59:14pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct Fonts
{
    enum Poppins {
        light,
        medium,
        regular,
        bold,
        retro
    };

    static void setCustomFont (Poppins font_style, std::unique_ptr<Font>& myFont)
    {
        switch (font_style) {
            case light:
                myFont = std::make_unique<Font> (
                        Typeface::createSystemTypefaceFor(BinaryData::PoppinsLight_ttf,
                                                          BinaryData::PoppinsLight_ttfSize));
                break;
            case medium:
                myFont = std::make_unique<Font> (
                        Typeface::createSystemTypefaceFor(BinaryData::PoppinsMedium_ttf,
                                                          BinaryData::PoppinsMedium_ttfSize));
                break;
            case regular:
                myFont = std::make_unique<Font> (
                        Typeface::createSystemTypefaceFor(BinaryData::PoppinsRegular_ttf,
                                                          BinaryData::PoppinsRegular_ttfSize));
                break;
            case bold:
                myFont = std::make_unique<Font> (
                        Typeface::createSystemTypefaceFor(BinaryData::PoppinsBold_ttf,
                                                          BinaryData::PoppinsBold_ttfSize));
                break;
            case retro:
                myFont = std::make_unique<Font> (
                        Typeface::createSystemTypefaceFor(BinaryData::ConnectionIiiRj3W_otf,
                                                          BinaryData::ConnectionIiiRj3W_otfSize));
            default:
                break;
        }
    }
};

class PirateStyle : public LookAndFeel_V4
{
public:
    PirateStyle() {
        Fonts::setCustomFont (Fonts::light, myFont_);
    };
    ~PirateStyle() {};

    void drawRotarySlider (Graphics&, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle,
                           float rotaryEndAngle, Slider&) override;
    void drawLabel (Graphics&, Label&) override;
    static void drawBezel (Graphics& g, float width, float height, float lineThickness);
    static void drawGlare (Graphics&, int width, int height, int boundarySize);

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

    std::unique_ptr<Font> myFont_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PirateStyle)
};

class Bezel : public Component
{
public:
    explicit Bezel (float lineThickness) : lineThickness_ (lineThickness)
    {
        setInterceptsMouseClicks(false, false);
    };
    ~Bezel() {};

    void paint (Graphics&) override;
private:
    float lineThickness_;
};

class Glare : public Component
{
public:
    explicit Glare (float boundarySize) : boundarySize_ (boundarySize)
    {
        setInterceptsMouseClicks (false, false);
    };
    ~Glare() {};

    void paint (Graphics&) override;
private:
    float boundarySize_;
};