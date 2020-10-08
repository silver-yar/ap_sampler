/*
  ==============================================================================

    ShowHideSlider.cpp
    Created: 1 Oct 2020 6:42:42pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ShowHideSlider.h"

//==============================================================================
ShowHideSlider::ShowHideSlider()
{
}

ShowHideSlider::~ShowHideSlider()
= default;

void ShowHideSlider::mouseDoubleClick(const MouseEvent &e) {
    if (onDoubleClick != nullptr)
    {
        onDoubleClick();
    }
}


