/*
  ==============================================================================

    PirateSlider.cpp
    Created: 10 Jun 2020 6:59:14pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PirateStyle.h"
#include "PirateColors.h"

static inline void clipToEllipse (Graphics& g, Rectangle<float>& bounds)
{
    Path p;
    p.addEllipse (bounds);
    g.reduceClipRegion (p);
}

static inline ColourGradient makeGradient (juce::Point<float> point1,
                                                 juce::Point<float> point2,
                                                 bool isRadial,
                                                 std::initializer_list<std::pair<double, Colour>> list)
{
    ColourGradient gr {};
    gr.isRadial = isRadial;
    gr.point1 = point1;
    gr.point2 = point2;

    for (auto pair : list)
        gr.addColour (pair.first, pair.second);

    return gr;
}

static inline void fillEllipse (Graphics& g, const Rectangle<float>& bounds, Colour colour)
{
    g.setColour (colour);
    g.fillEllipse (bounds);
}

static inline void fillEllipse (Graphics& g, const Rectangle<float>& bounds, const ColourGradient& gradient)
{
    g.setGradientFill (gradient);
    g.fillEllipse (bounds);
}

const PirateStyle::knobImages& PirateStyle::getKnobImages (int diameter)
{
    auto search = knobsBgs.find (diameter);
    if (search != knobsBgs.end()) return search->second;

    float radius = diameter * 0.5f;
    bool isTiny  = diameter < 20;
    bool isSmall = diameter < 60;

    juce::Point<float>     centre { radius, radius };
    Rectangle<float> bounds { 0.0f, 0.0f, float (diameter), float (diameter) };

    if (knobsBgs.size() > size_t (knobsMaxSize))
        knobsBgs.clear();


    // background
    Image bg { Image::ARGB, diameter, diameter + 3, true };
    {
        Graphics g (bg);
        fillEllipse (g, bounds.translated (0.0f, 1.0f), whiteA010);
        fillEllipse (g, bounds.translated (0.0f, 2.0f), whiteA010);
        fillEllipse (g, bounds,                         { 50, 51, 61});

        auto backgroundGr = isTiny? makeGradient (centre, { centre.x, centre.y + radius }, true,
                                                  {  { 0.0, Colours::transparentBlack },
                                                     { 0.9, Colours::transparentBlack },
                                                     { 1.0, blackA122 }  }) :
                            makeGradient (centre, { centre.x, centre.y + radius }, true,
                                          {  { 0.0,                          Colours::transparentBlack },
                                             { 0.52,                         blackA092 },
                                             { 0.9,                          Colours::transparentBlack },
                                             { double (1 - (4.0f / radius)), Colours::transparentBlack },
                                             { 1.0,                          blackA092 } });
        fillEllipse (g, bounds, backgroundGr);
    }


    bounds.reduce (diameter * 0.15f, diameter * 0.15f);
    auto fgRadius = bounds.getWidth() * 0.5f;


    // foreground
    Image fg { Image::ARGB, diameter, diameter, true };
    {
        Graphics g (fg); // lower shadow
        {
            auto xOffset = fgRadius * 0.12f;
            auto yOffset = fgRadius * 0.32f;

            ColourGradient shadowGr = makeGradient ({ centre.x + xOffset, centre.y + yOffset },
                                                          { centre.x, centre.y + fgRadius + yOffset }, true,
                                                          {  { 0.0,  blackA122                 },
                                                             { 0.72, blackA122                 },
                                                             { 1.0,  Colours::transparentBlack }  });
            fillEllipse (g, bounds.translated (xOffset, yOffset), shadowGr);
        }

        // middle
        {
            {
                Graphics::ScopedSaveState save (g);
                clipToEllipse (g, bounds);

                ColourGradient gr { { 55, 55, 66 }, 0.0f, bounds.getY(),
                                          { 34, 35, 41 }, 0.0f, bounds.getBottom(), false };
                fillEllipse (g, bounds, gr);

                ColourGradient ringGr = makeGradient (centre, { centre.x, centre.y + fgRadius }, true,
                                                            {  { 0.0,  Colours::transparentBlack },
                                                               { 0.72, Colours::transparentBlack },
                                                               { 1.0,  blackA042                 }  });
                fillEllipse (g, bounds, ringGr);

                g.setColour (whiteA042);
                g.drawEllipse (bounds.translated (0.0f, 1.0f), 1.0f);
                if (!isSmall) g.drawEllipse (bounds.translated (0.0f, 2.0f), 1.0f);
            }

            g.setColour (blackA092);
            g.drawEllipse (bounds, 1.0f);
        }
    }

    knobsBgs.insert ({diameter, knobImages { std::move (bg), std::move (fg) }});
    return knobsBgs.find (diameter)->second;
}

void PirateStyle::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                    const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    int diameter = (width > height)? height : width;
    if (diameter < 16) return;

    juce::Point<float> centre (x + std::floor (width * 0.5f + 0.5f), y + std::floor (height * 0.5f + 0.5f));
    diameter -= (diameter % 2)? 9 : 8;
    float radius = diameter * 0.5f;
    x = int (centre.x - radius);
    y = int (centre.y - radius);

    const auto bounds = Rectangle<int> (x, y, diameter, diameter).toFloat();

    bool isTiny  = diameter < 20;
    bool isSmall = diameter < 60;

    const auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    const Colour fill = slider.findColour (Slider::rotarySliderFillColourId);

    const knobImages& images = getKnobImages (diameter);
    g.drawImageAt (images.backgroundImage, x, y);

    if (!isSmall) // marker dot
    {
        auto dot = centre.getPointOnCircumference (radius * 0.825f, toAngle);
        auto dotRadius = radius * 0.072f;
        Rectangle<float> dotBounds { dot.x - dotRadius, dot.y - dotRadius, dotRadius * 2.0f, dotRadius * 2.0f };

        {
            Graphics::ScopedSaveState save (g);
            fillEllipse (g, dotBounds, fill);

            clipToEllipse (g, dotBounds);

            g.setColour (fill.brighter (0.15f));
            g.drawEllipse (dotBounds.translated (0.0f, -1.0f), 1.5f);

            g.setColour (fill.darker (0.3f));
            g.drawEllipse (dotBounds.translated (0.0f, 0.5f), 1.5f);
        }

        g.setColour (blackA092);
        g.drawEllipse (dotBounds.expanded (0.5f), 1.0f);
    }

    // position arc
    {
        Path valueArc;
        radius -= 1.0f;

        if (isTiny)
        {
            valueArc.addCentredArc (centre.x, centre.y, radius, radius, 0.0f, rotaryStartAngle, toAngle, true);

            g.setColour (fill.brighter (0.5f));
            g.strokePath (valueArc, PathStrokeType { 3.0f });
        }
        else
        {
            ColourGradient arcGr = makeGradient (centre, { centre.x, centre.y + radius }, true,
                                                       {  { 0.0,   Colours::transparentWhite },
                                                          { 0.952, Colours::transparentWhite },
                                                          { 1.0,   fill.withAlpha (0.8f) }      });
            g.setGradientFill (arcGr);

            valueArc.addPieSegment (bounds.reduced (1.5f), rotaryStartAngle, toAngle, 0);
            g.fillPath (valueArc);

            valueArc.clear();
            valueArc.addCentredArc (centre.x, centre.y, radius, radius, 0.0f, rotaryStartAngle, toAngle, true);

            g.setColour (fill.brighter (0.5f));
            g.strokePath (valueArc, PathStrokeType { 1.5f });
        }
    }

    g.setColour (blackA092);
    g.drawEllipse (bounds, 1.0f);

    g.setColour (Colours::black);
    if (!isTiny) g.drawImageAt (images.foregroundImage, x, y);
}

void PirateStyle::drawLabel(Graphics& g, Label& label)
{
    //auto bounds = Rectangle<int>(20, 10);
    //auto bounds = Rectangle<int>(0, 0, label.getWidth(), label.getHeight());
    auto bounds = label.getLocalBounds();
    g.setColour(PirateColors::green1);
    g.fillRect(bounds);
    g.setColour(PirateColors::green2);
    g.drawRect (bounds);
    drawBezel(g, label.getWidth(), label.getHeight(), 4);
    g.setColour(PirateColors::green2);
    g.setFont(14.0f);
    label.setJustificationType (Justification::centred);
    g.drawText(label.getText(), bounds, Justification::centred, true);
}

void PirateStyle::drawBezel(Graphics& g, float width, float height, float lineThickness) {
    // Draw Bezel
    g.setColour(PirateColors::green1.brighter(0.6f));
    g.drawLine(0,0,0, height, lineThickness);
    g.drawLine(width, height,0, height, lineThickness);
    g.drawLine(width,0,width, height, lineThickness);
    g.setColour(PirateColors::green1.darker(0.6f));
    g.drawLine(0,0,width,0, lineThickness);

    auto half = lineThickness / 2;

    // Left Corner
    Path p;
    p.startNewSubPath(0, 0);
    p.lineTo(0, half);
    p.lineTo(half, half);
    p.closeSubPath();
    g.setColour(PirateColors::green1.brighter(0.6f));
    g.fillPath(p);

    // Right Corner
    p.startNewSubPath(width, 0);
    p.lineTo(width, half);
    p.lineTo(width - half, half);
    p.closeSubPath();
    g.setColour(PirateColors::green1.brighter(0.6f));
    g.fillPath(p);
}
