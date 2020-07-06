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
ParamView::ParamView(Ap_samplerAudioProcessor& p) : processor (p)
{
    addAndMakeVisible (infoScreen_);
    setupSlider (slider1_, label1_, "Attack");
    setupSlider (slider2_, label2_, "Decay");
    setupSlider (slider3_, label3_, "Sustain");
    setupSlider (slider4_, label4_, "Release");
    attachSlider (slider1_, slider1Attachment_, "ATT");
    attachSlider (slider2_, slider2Attachment_, "DEC");
    attachSlider (slider3_, slider3Attachment_, "SUS");
    attachSlider (slider4_, slider4Attachment_, "REL");
//    label1_.setText("Attack", NotificationType::dontSendNotification);
//    label1_.setLookAndFeel(&pirateSliderStyle_);
//    label1_.attachToComponent(&slider1_, false);
}

ParamView::~ParamView()
{
    slider1_->setLookAndFeel(nullptr);
    slider2_->setLookAndFeel(nullptr);
    slider3_->setLookAndFeel(nullptr);
    slider4_->setLookAndFeel(nullptr);
    label1_->setLookAndFeel(nullptr);
    label2_->setLookAndFeel(nullptr);
    label3_->setLookAndFeel(nullptr);
    label4_->setLookAndFeel(nullptr);
}

void ParamView::resized()
{
    auto bounds = getLocalBounds();
    auto rectTop = bounds.removeFromTop (100);
    bounds.reduce (20, 10);
    rectTop.reduce (20, 20);

    infoScreen_.setBounds (rectTop);

    Grid grid;
    using Track = Grid::TrackInfo;
    using Fr = Grid::Fr;

    grid.items.add (GridItem (slider1_.get()));
    grid.items.add (GridItem (slider2_.get()));
    grid.items.add (GridItem (slider3_.get()));
    grid.items.add (GridItem (slider4_.get()));

    grid.templateColumns = {
            Track (Fr (1)),
            Track (Fr (1))
    };

    grid.templateRows = {
            Track (Fr (1)),
            Track (Fr (1))
    };

    grid.columnGap = Grid::Px (10);
    grid.rowGap = Grid::Px (50);

    grid.performLayout (bounds);
    //oFlexBox_.performLayout (getFlexBounds());
}

void ParamView::paint (Graphics& g)
{
    g.fillAll (PirateColors::orange1);   // clear the background
}

void ParamView::setupSlider(std::unique_ptr<Slider>& slider, std::unique_ptr<Label>& label, const String& name)
{
    slider = std::make_unique<Slider> (Slider::SliderStyle::RotaryVerticalDrag, Slider::TextBoxBelow);
    addAndMakeVisible (slider.get());
    label = std::make_unique<Label> ("", name);
    addAndMakeVisible (label.get());
    label->attachToComponent (slider.get(), false);
    label->setJustificationType (Justification::centred);
    slider->setLookAndFeel(&pirateSliderStyle_);
    label->setLookAndFeel (&pirateSliderStyle_);
    //addAndMakeVisible(slider);
}

void ParamView::attachSlider(std::unique_ptr<Slider> &slider,
                             std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> &attachment,
                             const String &paramID) {
    attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.apvts, paramID, *slider);
}

