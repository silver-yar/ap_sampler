/*
  ==============================================================================

    InfoScreen.cpp
    Created: 10 Jun 2020 7:07:09pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "InfoScreen.h"
#include "PirateColors.h"

//==============================================================================
InfoScreen::InfoScreen()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

InfoScreen::~InfoScreen()
{
}

void InfoScreen::paint (Graphics& g)
{
    g.fillAll (PirateColors::green1);   // clear the background

    // TODO: Make this a method in a Style Class
    // Draw Bezel
    g.setColour(PirateColors::green1.brighter(0.6f));
    g.drawLine(0,0,0,getHeight(), 8);
    g.drawLine(getWidth(),getHeight(),0,getHeight(), 8);
    g.drawLine(getWidth(),0,getWidth(),getHeight(), 8);
    g.setColour(PirateColors::green1.darker(0.6f));
    g.drawLine(0,0,getWidth(),0, 8);

    // Left Corner
    Path p;
    p.startNewSubPath(0, 0);
    p.lineTo(0, 4);
    p.lineTo(4, 4);
    p.closeSubPath();
    g.setColour(PirateColors::green1.brighter(0.6f));
    g.fillPath(p);

    // Right Corner
    p.startNewSubPath(getWidth(), 0);
    p.lineTo(getWidth(), 4);
    p.lineTo(getWidth() - 4, 4);
    p.closeSubPath();
    g.setColour(PirateColors::green1.brighter(0.6f));
    g.fillPath(p);

    g.setColour (PirateColors::green2);
    g.setFont (20.0f);
    g.drawText (grpName_, getLocalBounds().reduced(20),
                Justification::topLeft, true);   // draw some placeholder text
}

void InfoScreen::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
