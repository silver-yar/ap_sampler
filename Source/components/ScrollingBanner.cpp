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
ScrollingBanner::ScrollingBanner(Ap_samplerAudioProcessor& p) : processor (p), bezel_ (8), glare_(4)
{
    Fonts::setCustomFont (Fonts::light, myFont_);
    scrollText_.setFont (*myFont_, true);
    scrollText_.setText (bannerMessages_[0]);
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
    if (x_ > getWidth()) {
        if (index_ > (bannerMessages_.size() - 1))
            index_ = 0;
        scrollText_.setText (bannerMessages_[index_]);
        x_ = -textWidth_;
        index_++;
    }
    repaint();
}

void ScrollingBanner::changeListenerCallback (ChangeBroadcaster *source)
{
    bannerMessages_[0] = processor.getFileName();
    index_ = 0;
}