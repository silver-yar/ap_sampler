/*
  ==============================================================================

    ParamView.cpp
    Created: 1 Jun 2020 8:47:45pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ParamView.h"
#include "PirateColors.h"

//==============================================================================
ParamView::ParamView()
{
    setupSlider(slider1_);
    setupSlider(slider2_);
    setupSlider(slider3_);
    setupSlider(slider4_);
//    label1_.setText("Attack", NotificationType::dontSendNotification);
//    label1_.setLookAndFeel(&pirateSlider_);
//    label1_.attachToComponent(&slider1_, false);
    setupFlexBoxes();
    setupFlexItems();
}

ParamView::~ParamView()
{
}

void ParamView::resized()
{
    oFlexBox_.performLayout (getFlexBounds());
}

void ParamView::paint (Graphics& g)
{
    g.fillAll (PirateColors::orange1);   // clear the background
}

void ParamView::setupSlider(Slider& slider)
{
    slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(Slider::TextBoxBelow, false, 20, 10);
    slider.setLookAndFeel(&pirateSlider_);
    //addAndMakeVisible(slider);
}

Rectangle<int> ParamView::getFlexBounds() const
{
    return getLocalBounds().toFloat().reduced(15).toNearestInt();
}

void ParamView::setupFlexBoxes()
{
    // TODO: Refactor
    // Row 1 FlexBox
    r1FlexBox_.flexDirection = FlexBox::Direction::row;
    r1FlexBox_.flexWrap = FlexBox::Wrap::noWrap;
    r1FlexBox_.justifyContent = FlexBox::JustifyContent::spaceBetween;
    r1FlexBox_.alignItems = FlexBox::AlignItems::stretch;
    // Row 2 FlexBox
    r2FlexBox_.flexDirection = FlexBox::Direction::row;
    r2FlexBox_.flexWrap = FlexBox::Wrap::noWrap;
    r2FlexBox_.justifyContent = FlexBox::JustifyContent::spaceBetween;
    r2FlexBox_.alignItems = FlexBox::AlignItems::stretch;
    // Inner FlexBox
    iFlexBox_.flexDirection = FlexBox::Direction::column;
    iFlexBox_.flexWrap = FlexBox::Wrap::noWrap;
    iFlexBox_.justifyContent = FlexBox::JustifyContent::spaceBetween;
    iFlexBox_.alignItems = FlexBox::AlignItems::stretch;
    // Outer FlexBox
    oFlexBox_.flexDirection = FlexBox::Direction::column;
    oFlexBox_.justifyContent = FlexBox::JustifyContent::spaceAround;
    oFlexBox_.alignItems = FlexBox::AlignItems::center;
}

void ParamView::setupFlexItems()
{
    addItem(r1FlexBox_, slider1_, 1, 0);
    addItem(r1FlexBox_, slider2_, 1, 0);
    addItem(r2FlexBox_, slider3_, 1, 0);
    addItem(r2FlexBox_, slider4_, 1, 0);

    addFlex(iFlexBox_, r1FlexBox_, 1);
    addFlex(iFlexBox_, r2FlexBox_, 1);

    // TODO: Make for loop over slider vector
//    addItem(iFlexBox_, slider1_, 1, 0);
//    addItem(iFlexBox_, slider2_, 1, 0);
//    addItem(iFlexBox_, slider3_, 1, 0);
//    addItem(iFlexBox_, slider4_, 1, 0);

    addItem(oFlexBox_, infoScreen_, 1, 5);
    addFlex(oFlexBox_, iFlexBox_, 3);
}

void ParamView::addItem(FlexBox& flexBox, Component& item, float grow, float margin)
{
    flexBox.items.add (FlexItem (item).withFlex (grow, 1, 10)
                                                     .withMargin(FlexItem::Margin(margin))
                                                     );
    auto& flexItem = flexBox.items.getReference (flexBox.items.size() - 1);
    flexItem.associatedComponent = &item;
    addAndMakeVisible (item);
}

void ParamView::addFlex(FlexBox& parentFlexBox, FlexBox& childFlexBox, float grow)
{
    parentFlexBox.items.add (FlexItem (childFlexBox).withFlex (grow, 0, 10));
}
