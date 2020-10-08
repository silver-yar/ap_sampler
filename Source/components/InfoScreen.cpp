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
InfoScreen::InfoScreen(Ap_samplerAudioProcessor& p) : processor (p)
{
    hideButton_ = std::make_unique<ToggleButton> ("Hide");
    hideButton_ -> setColour (ToggleButton::textColourId, PirateColors::green2);
    hideButton_ -> setColour (ToggleButton::tickColourId, PirateColors::green2);
    addAndMakeVisible (hideButton_.get());
    hideButton_ -> addListener (this);
}

InfoScreen::~InfoScreen()
{
}

void InfoScreen::paint (Graphics& g)
{
    g.fillAll (PirateColors::green1);   // clear the background

    // Draw Group Name
    drawGroupName (g);

    // Draw Bezel
    PirateStyle::drawBezel (g, getWidth(), getHeight(), 8);
}

void InfoScreen::resized()
{
    auto bounds = getLocalBounds();
    bounds.removeFromLeft (getWidth() * 2 / 3);
    bounds.reduce (0, 20);

    hideButton_ -> setBounds(bounds);

}

void InfoScreen::drawGroupName(Graphics& g) {
    g.setColour (PirateColors::green2);
    g.setFont (20.0f);
    g.drawText (group_label, getLocalBounds().reduced(20),
                Justification::centredLeft, true);   // draw some placeholder text
}

void InfoScreen::mouseDown(const MouseEvent &e) {
    auto bounds = getLocalBounds();
    bounds.removeFromRight (getWidth() / 2);

    if (bounds.contains (e.getMouseDownPosition()) && onNameClicked != nullptr)
        onNameClicked();

}

void InfoScreen::buttonClicked(Button *button) {
    if (button == hideButton_.get()) {
        processor.hideEnv = hideButton_ -> getToggleState();
    }
}
