/*
  ==============================================================================

    ScrollingBanner.cpp
    Created: 10 Oct 2020 7:47:43pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ScrollingBanner.h"
#include "../styling/PirateColors.h"

//==============================================================================
ScrollingBanner::ScrollingBanner() : bezel_ (8), glare_(4)
{
    scrollText_.setText ("audio pirate");
    scrollText_.setColour (PirateColors::green2);
    scrollText_.setJustification (Justification::centred);
    scrollText_.setFontHeight (24.0f);
    addAndMakeVisible (scrollText_);
    addAndMakeVisible (bezel_, 1);
    addAndMakeVisible (glare_, 2);
    startTimerHz(30);
}

ScrollingBanner::~ScrollingBanner()
{
    stopTimer();
}

void ScrollingBanner::paint (juce::Graphics& g)
{
    g.fillAll (PirateColors::green1);   // clear the background

    g.setColour (PirateColors::green2);

    auto textBounds = Rectangle<float> (x_, y_, textWidth_, getHeight());
    scrollText_.setBoundingBox (Parallelogram<float> (textBounds));
}

void ScrollingBanner::resized()
{
    auto localBounds = getLocalBounds();
    scrollText_.setBounds (localBounds);
    bezel_.setBounds (localBounds);
    glare_.setBounds (localBounds);
}

void ScrollingBanner::timerCallback()
{
    x_ += 2;
    if (x_ < getWidth())
        repaint();
    else {
        scrollText_.setText (bannerMessages_[randomInt_.nextInt(3)]);
        x_ = -textWidth_;
        repaint();
    }
}