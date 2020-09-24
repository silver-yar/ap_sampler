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
void ParamBlock::layoutSliders (Array<Slider*>& sliders, Rectangle<int>& bounds)
{
    Grid grid;
    using Track = Grid::TrackInfo;
    using Fr = Grid::Fr;

    for (const auto &slider : sliders)
    {
        grid.items.add(GridItem (slider));
        if (shouldHide)
            slider->setVisible (false);
        else
            slider->setVisible (true);
    }

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
//==============================================================================
ParamView::ParamView(Ap_samplerAudioProcessor& p) : infoScreen_(p), processor (p)
{
    infoScreen_.onNameClicked = []() {
        DBG("name clicked.");
    };
    addAndMakeVisible (infoScreen_);

    addAndMakeVisible (adsrParams_);
    setupSlider (adsrParams_, attackSlider_, attackLabel_, "Attack");
    setupSlider (adsrParams_, decaySlider_, decayLabel_, "Decay");
    setupSlider (adsrParams_, sustainSlider_, sustainLabel_, "Sustain");
    setupSlider (adsrParams_, releaseSlider_, releaseLabel_, "Release");

    addAndMakeVisible (filterParams_);
    setupSlider (filterParams_, lowPassSlider_, lowPassLabel_, "Low Pass");
    setupSlider (filterParams_, bandPassSlider_, bandPassLabel_, "Band Pass");
    setupSlider (filterParams_, highPassSlider_, highPassLabel_, "High Pass");

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
    adsrParams_.setBounds (bounds);
    filterParams_.setBounds (bounds);
    rectTop.reduce (20, 20);

    infoScreen_.setBounds (rectTop);

//    const auto layoutSliders = [](const auto &sliders, const auto &bounds) {
//        Grid grid;
//        using Track = Grid::TrackInfo;
//        using Fr = Grid::Fr;
//
//        for (const auto &slider : sliders)
//        {
//            grid.items.add(GridItem (slider));
//        }
//
//
//        grid.templateColumns = {
//                Track (Fr (1)),
//                Track (Fr (1))
//        };
//
//        grid.templateRows = {
//                Track (Fr (1)),
//                Track (Fr (1))
//        };
//
//        //grid.columnGap = Grid::Px (10);
//        //grid.rowGap = Grid::Px (50);
//
//        grid.performLayout (bounds);
//    };

    Array<Slider*> adsrSliders
        ({attackSlider_.get(), decaySlider_.get(), sustainSlider_.get(), releaseSlider_.get()});
    //adsrParams_.shouldHide = true;
    adsrParams_.layoutSliders (adsrSliders, bounds);

    Array<Slider*> filterSliders
            ({lowPassSlider_.get(), bandPassSlider_.get(), highPassSlider_.get()});
    filterParams_.shouldHide = true;
    filterParams_.layoutSliders (filterSliders, bounds);
}

void ParamView::paint (Graphics& g)
{
    g.fillAll (PirateColors::orange1);   // clear the background
    auto bounds = getLocalBounds();
    bounds.removeFromTop (100);
    bounds.reduce (20, 10);
    g.setColour (Colours::limegreen);
    g.fillRect (bounds);
}

void ParamView::setupSlider(Component& parent, std::unique_ptr<Slider>& slider, std::unique_ptr<Label>& label, const String& name)
{
    slider = std::make_unique<Slider> (Slider::SliderStyle::RotaryVerticalDrag, Slider::TextBoxBelow);
    if (name == "Sustain")
        slider -> setTextValueSuffix (" dB");
    else
        slider -> setTextValueSuffix (" s");
    parent.addAndMakeVisible (slider.get());
    label = std::make_unique<Label> ("", name);
    parent.addAndMakeVisible (label.get());
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

