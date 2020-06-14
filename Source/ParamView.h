/*
  ==============================================================================

    ParamView.h
    Created: 1 Jun 2020 8:47:45pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PirateSlider.h"
#include "InfoScreen.h"

//==============================================================================
/*
*/
class ParamView    : public Component
{
public:
    ParamView();
    ~ParamView();

    void paint (Graphics&) override;
    void resized() override;

    //==============================================================================
    Rectangle<int> getFlexBounds() const;

    void setupSlider(Slider& slider);
    void setupFlexBoxes(); // Setup for the inner and outer flex boxes
    void setupFlexItems(); // Setup for the inner and outer flex items
    void addItem(FlexBox& flexBox, Component& item, float grow, float margin); // Add a component to a flex box
    static void addFlex(FlexBox& parentFlexBox, FlexBox& childFlexBox, float grow); // Add a flex box to a f

private:
    // Components
    InfoScreen infoScreen_;
    // TODO: Make Slider vector
    Slider slider1_, slider2_, slider3_, slider4_;
    Label label1_, label2_, label3_, label4_;

    // Styling
    PirateSlider pirateSlider_;
    FlexBox iFlexBox_, oFlexBox_, r1FlexBox_, r2FlexBox_; // Inner and outer flex boxes (respectively)

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParamView)
};
