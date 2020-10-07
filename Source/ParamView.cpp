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
#include "LabelSlider.h"
#include "PluginProcessor.h"

//==============================================================================
void ParamBlock::layoutSliders (Array<LabelSlider*>& sliders)
{
    auto bounds = getLocalBounds();

    Grid grid;
    using Track = Grid::TrackInfo;
    using Fr = Grid::Fr;

    for (const auto &slider : sliders)
    {
        grid.items.add(GridItem (slider));
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
    grid.rowGap = Grid::Px (10);

    grid.alignItems = Grid::AlignItems::center;

    grid.performLayout (bounds);
}
//==============================================================================
ParamView::ParamView(Ap_samplerAudioProcessor& p) : infoScreen_(p), processor (p)
{
    infoScreen_.onNameClicked = [this]() {
        switch (curr_group) {
            case GroupName::adsr:
                this->adsrParams_.setVisible(false);
                this->filterParams_.setVisible(true);
                curr_group = GroupName::filter;
                infoScreen_.group_label = "filter";
                break;
            case GroupName::filter:
                this->adsrParams_.setVisible(true);
                this->filterParams_.setVisible(false);
                curr_group = GroupName::adsr;
                infoScreen_.group_label = "adsr";
                break;
            default:
                break;
        }
        repaint();
        resized();
    };
    addAndMakeVisible (infoScreen_);

    addAndMakeVisible (adsrParams_);
    setupSlider (adsrParams_, attackSlider_, "Attack");
    setupSlider (adsrParams_, decaySlider_, "Decay");
    setupSlider (adsrParams_, sustainSlider_,"Sustain","dB");
    setupSlider (adsrParams_, releaseSlider_, "Release");

    addChildComponent (filterParams_);
    setupSlider (filterParams_, lowPassSlider_, "Low Pass","Hz");
    lowPassSlider_->setOnDoubleClick([this](){
        lowPassSlider_->setEnabled();
        bandPassSlider_->setDisabled();
        highPassSlider_->setDisabled();
        processor.setFilterType (Ap_samplerAudioProcessor::FilterType::low_pass);
    });
    setupSlider (filterParams_, bandPassSlider_, "Band Pass", false,"Hz");
    bandPassSlider_->setOnDoubleClick([this](){
        lowPassSlider_->setDisabled();
        bandPassSlider_->setEnabled();
        highPassSlider_->setDisabled();
        processor.setFilterType (Ap_samplerAudioProcessor::FilterType::band_pass);
    });
    setupSlider (filterParams_, highPassSlider_,  "High Pass", false,"Hz");
    highPassSlider_->setOnDoubleClick([this](){
        lowPassSlider_->setDisabled();
        bandPassSlider_->setDisabled();
        highPassSlider_->setEnabled();
        processor.setFilterType (Ap_samplerAudioProcessor::FilterType::high_pass);
    });

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
}

void ParamView::resized()
{
    auto bounds = getLocalBounds();
    auto rectTop = bounds.removeFromTop (100);
    bounds.reduce (20, 10);
    rectTop.reduce (20, 10);

    infoScreen_.setBounds (rectTop);
    adsrParams_.setBounds (bounds);
    filterParams_.setBounds (bounds);

    Array<LabelSlider*> adsrSliders
        ({attackSlider_.get(), decaySlider_.get(), sustainSlider_.get(), releaseSlider_.get()});
    adsrParams_.layoutSliders (adsrSliders);

    Array<LabelSlider*> filterSliders
            ({lowPassSlider_.get(), bandPassSlider_.get(), highPassSlider_.get()});
    filterParams_.layoutSliders (filterSliders);
}

void ParamView::paint (Graphics& g)
{
    g.fillAll (PirateColors::orange1);   // clear the background
}

void ParamView::setupSlider(Component& parent, std::unique_ptr<LabelSlider>& label_slider,
                            const String& name, bool isEnabled, const String& suffix)
{
    label_slider = std::make_unique<LabelSlider>();
    label_slider->slider.setTextValueSuffix (" " + suffix);
    label_slider->label.setText(name, dontSendNotification);
    parent.addAndMakeVisible (label_slider.get());
    if (!isEnabled)
        label_slider->setDisabled();
}

void ParamView::attachSlider(std::unique_ptr<LabelSlider> &label_slider,
                             std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> &attachment,
                             const String &paramID) {
    attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.apvts, paramID, label_slider->slider);
}

