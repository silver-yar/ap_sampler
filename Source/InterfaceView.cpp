/*
  ==============================================================================

    InterfaceView.cpp
    Created: 1 Jun 2020 7:51:01pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PirateColors.h"
#include "InterfaceView.h"

//==============================================================================
InterfaceView::InterfaceView(Ap_samplerAudioProcessor& p) :
    processor(p)
{
    midiKeyboard_ = std::make_unique<MidiKeyboardComponent> (processor.getKeyboardState(), 
            MidiKeyboardComponent::horizontalKeyboard);

    midiKeyboard_ -> setLowestVisibleKey(59); // Note #59 = B2
    midiKeyboard_ -> setKeyPressBaseOctave(5); // Octave #5 = C3
    midiKeyboard_ -> setKeyWidth(30.0f);
    midiKeyboard_ -> setWantsKeyboardFocus (true);

    // Keyboard Colors
    midiKeyboard_ -> setColour (MidiKeyboardComponent::mouseOverKeyOverlayColourId,
            PirateColors::orange1.withAlpha (0.5f));
    midiKeyboard_ -> setColour (MidiKeyboardComponent::keyDownOverlayColourId, PirateColors::orange1);

    addAndMakeVisible(midiKeyboard_.get());
}

InterfaceView::~InterfaceView()
{
}

void InterfaceView::paint (Graphics& g)
{

}

void InterfaceView::resized()
{
    midiKeyboard_ -> setBounds(getLocalBounds());
}
