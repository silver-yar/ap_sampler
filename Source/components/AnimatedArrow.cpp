/*
  ==============================================================================

    AnimatedArrow.cpp
    Created: 16 Oct 2020 5:25:11pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AnimatedArrow.h"
#include "../styling/PirateColors.h"

//==============================================================================
AnimatedArrow::AnimatedArrow()
{
   startTimerHz (30);
}

AnimatedArrow::~AnimatedArrow()
{
    stopTimer();
}

void AnimatedArrow::paint (juce::Graphics& g)
{
    Path p;
    p.startNewSubPath(Point<float> (x_, getHeight() * 0.25f));
    p.lineTo (Point<float> (x_ + getWidth() * 0.25f, getHeight() * 0.5f));
    p.lineTo (Point<float> (x_, getHeight() * 0.75f));
    p.closeSubPath();

    g.setColour (PirateColors::green2.withAlpha (index_ * 0.1f));
    g.fillPath (p);

    if (x_ > getWidth() * 0.75f) {
        x_ = 0;
        index_ = 0;
    }
    else {
        x_ += getWidth() * 0.015;
        index_ += 0.15f;
    }
}

void AnimatedArrow::resized()
{
}

void AnimatedArrow::timerCallback()
{
    repaint();
}
