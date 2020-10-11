/*
  ==============================================================================

    APButton.cpp
    Created: 10 Oct 2020 5:20:32pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "APButton.h"
#include "../styling/PirateColors.h"

//==============================================================================
APButton::APButton(const String &buttonName) : Button (buttonName)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

APButton::~APButton()
{
}

void APButton::paintButton(Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {

    if (state_) {
        g.fillAll (PirateColors::green2);
        g.setColour (PirateColors::green1);

        if (shouldDrawButtonAsHighlighted) {
            g.fillAll (PirateColors::green1);
            g.setColour (PirateColors::green2);
            g.drawRect (getLocalBounds(), 1);
        }
        if (shouldDrawButtonAsDown){
            g.fillAll (PirateColors::green2);
            g.setColour (PirateColors::green1);
        }

        setButtonText ("Show");
    } else {
        g.fillAll (Colours::transparentWhite);
        g.setColour (PirateColors::green2);

        if (shouldDrawButtonAsHighlighted) {
            g.fillAll (PirateColors::green2);
            g.setColour (PirateColors::green1);
        }
        if (shouldDrawButtonAsDown){
            g.fillAll (PirateColors::green1);
            g.setColour (PirateColors::green2);
            g.drawRect (getLocalBounds());
        }
        setButtonText ("Hide");
    }


    g.drawText (getButtonText(), getLocalBounds(),
                juce::Justification::centred, true);
}
