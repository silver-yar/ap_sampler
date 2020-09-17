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
ParamView::ParamView(Ap_samplerAudioProcessor& p) : infoScreen_(p), processor (p)
{
    addAndMakeVisible (infoScreen_);
    setupSlider (attackSlider_, attackLabel_, "Attack");
    setupSlider (decaySlider_, decayLabel_, "Decay");
    setupSlider (sustainSlider_, sustainLabel_, "Sustain");
    setupSlider (releaseSlider_, releaseLabel_, "Release");
    setupSlider (lowPassSlider_, lowPassLabel_, "Low Pass");
    setupSlider (bandPassSlider_, bandPassLabel_, "Band Pass");
    setupSlider (highPassSlider_, highPassLabel_, "High Pass");
    attachSlider (attackSlider_, attackAttachment_, "ATT");
    attachSlider (decaySlider_, decayAttachment_, "DEC");
    attachSlider (sustainSlider_, sustainAttachment_, "SUS");
    attachSlider (releaseSlider_, releaseAttachment_, "REL");
    attachSlider (lowPassSlider_, lowPassAttachment_, "LPF");
    attachSlider (bandPassSlider_, bandPassAttachment_, "BPF");
    attachSlider (highPassSlider_, highPassAttachment_, "HPF");
}

ParamView::~ParamView()
{
    attackSlider_-> setLookAndFeel(nullptr);
    decaySlider_-> setLookAndFeel(nullptr);
    sustainSlider_-> setLookAndFeel(nullptr);
    releaseSlider_-> setLookAndFeel(nullptr);
    lowPassSlider_ -> setLookAndFeel(nullptr);
    bandPassSlider_ -> setLookAndFeel(nullptr);
    highPassSlider_ -> setLookAndFeel(nullptr);

    attackLabel_->setLookAndFeel(nullptr);
    decayLabel_->setLookAndFeel(nullptr);
    sustainLabel_->setLookAndFeel(nullptr);
    releaseLabel_->setLookAndFeel(nullptr);
    lowPassLabel_ -> setLookAndFeel(nullptr);
    bandPassLabel_ -> setLookAndFeel(nullptr);
    highPassLabel_ -> setLookAndFeel(nullptr);
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

    grid.items.add (GridItem (attackSlider_.get()));
    grid.items.add (GridItem (decaySlider_.get()));
    grid.items.add (GridItem (sustainSlider_.get()));
    grid.items.add (GridItem (releaseSlider_.get()));


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
}

void ParamView::paint (Graphics& g)
{
    g.fillAll (PirateColors::orange1);   // clear the background
}

void ParamView::setupSlider(std::unique_ptr<Slider>& slider, std::unique_ptr<Label>& label, const String& name)
{
    slider = std::make_unique<Slider> (Slider::SliderStyle::RotaryVerticalDrag, Slider::TextBoxBelow);
    if (name == "Sustain")
        slider -> setTextValueSuffix (" dB");
    else
        slider -> setTextValueSuffix (" s");
    addAndMakeVisible (slider.get());
    label = std::make_unique<Label> ("", name);
    addAndMakeVisible (label.get());
    label->attachToComponent (slider.get(), false);
    label->setJustificationType (Justification::centred);
    slider->setLookAndFeel(&pirateSliderStyle_);
    label->setLookAndFeel (&pirateSliderStyle_);
}

void ParamView::attachSlider(std::unique_ptr<Slider> &slider,
                             std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> &attachment,
                             const String &paramID) {
    attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.apvts, paramID, *slider);
}

