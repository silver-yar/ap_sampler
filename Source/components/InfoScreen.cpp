/*
  ==============================================================================

    InfoScreen.cpp
    Created: 10 Jun 2020 7:07:09pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "InfoScreen.h"
#include "../styling/PirateColors.h"
#include "../styling/PirateStyle.h"

//==============================================================================
InfoScreen::InfoScreen(Ap_samplerAudioProcessor& p) : hideButton_("Hide"), bezel_(8), glare_(4), processor (p)
{
    Fonts::setCustomFont(Fonts::medium, myFont_);
    hideButton_.setColour (ToggleButton::textColourId, PirateColors::green2);
    hideButton_.setColour (ToggleButton::tickColourId, PirateColors::green2);
    addAndMakeVisible (hideButton_);
    hideButton_.onClick = [this]() {
        hideButton_.toggleButtonState();
        processor.hideEnv = !processor.hideEnv;
    };
    addAndMakeVisible (bezel_);
    addAndMakeVisible (glare_, 1);
}

InfoScreen::~InfoScreen()
{
}

void InfoScreen::paint (Graphics& g)
{
    g.setFont (*myFont_);
    g.fillAll (PirateColors::green1);   // clear the background

    // Draw Group Name
    drawGroupName (g);
}

void InfoScreen::resized()
{
    auto bounds = getLocalBounds();
    bounds.removeFromLeft (getWidth() * 2 / 3);
    bounds.reduce (10, 25);

    hideButton_.setBounds(bounds);
    bezel_.setBounds (getLocalBounds());
    glare_.setBounds (getLocalBounds());

}

void InfoScreen::drawGroupName(Graphics& g) {
    g.setColour (PirateColors::green2);
    g.setFont (32.0f);
    g.drawText (group_label, getLocalBounds().reduced(20),
                Justification::centredLeft, true);   // draw some placeholder text
}

void InfoScreen::mouseDown(const MouseEvent &e) {
    auto bounds = getLocalBounds();
    bounds.removeFromRight (getWidth() / 2);

    if (bounds.contains (e.getMouseDownPosition()) && onNameClicked != nullptr)
        onNameClicked();

}
