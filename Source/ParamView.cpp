/*
  ==============================================================================

    ParamView.cpp
    Created: 1 Jun 2020 8:47:45pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ParamView.h"

//==============================================================================
ParamView::ParamView()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

ParamView::~ParamView()
{
}

void ParamView::paint (Graphics& g)
{
    g.fillAll (orange1_);   // clear the background

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("ParamView", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void ParamView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
