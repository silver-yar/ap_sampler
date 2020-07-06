/*
  ==============================================================================

    ParamView.h
    Created: 1 Jun 2020 8:47:45pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PirateSliderStyle.h"
#include "PirateSlider.h"
#include "InfoScreen.h"

//==============================================================================
/*
*/
class ParamView    : public Component
{
public:
    ParamView(Ap_samplerAudioProcessor&);
    ~ParamView();

    void paint (Graphics&) override;
    void resized() override;

    //==============================================================================
    Rectangle<int> getFlexBounds() const;

    void setupSlider (std::unique_ptr<Slider>& slider, std::unique_ptr<Label>& label, const String& name);
    void attachSlider (std::unique_ptr<Slider>& slider, std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>& attachment, const String& paramID);

private:
    // Styling
    PirateSliderStyle pirateSliderStyle_;

    // Components
    InfoScreen infoScreen_;
    // TODO: Make Slider vector
    std::unique_ptr<Slider> slider1_, slider2_, slider3_, slider4_;
    std::unique_ptr<Label> label1_, label2_, label3_, label4_;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> slider1Attachment_, slider2Attachment_, slider3Attachment_, slider4Attachment_;

    Ap_samplerAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParamView)
};
