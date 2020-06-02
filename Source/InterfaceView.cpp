/*
  ==============================================================================

    InterfaceView.cpp
    Created: 1 Jun 2020 7:51:01pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "InterfaceView.h"

//==============================================================================
InterfaceView::InterfaceView(Ap_samplerAudioProcessor& p) :
    processor(p),
    keyboard_ (p.getKeyboardState(), MidiKeyboardComponent::horizontalKeyboard)
{
    keyboard_.setLowestVisibleKey(59); // Note #59 = B2
    keyboard_.setKeyPressBaseOctave(5); // Octave #5 = C3
    keyboard_.setKeyWidth(30.0f);
    addAndMakeVisible(keyboard_);
}

InterfaceView::~InterfaceView()
{
}

void InterfaceView::paint (Graphics& g)
{

}

void InterfaceView::resized()
{
    keyboard_.setBounds(getLocalBounds());
}
