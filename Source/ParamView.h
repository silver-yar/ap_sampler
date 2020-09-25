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
#include "PirateStyle.h"
#include "InfoScreen.h"

//==============================================================================
/*
*/
class ParamBlock : public Component
{
public:
    ParamBlock() = default;;
    ~ParamBlock() override {};

    void paint (Graphics& g) override
    {
        g.fillAll(Colours::limegreen);
    }

    void layoutSliders (Array<Slider*>& sliders, Rectangle<int>& bounds);

    bool shouldHide { false };
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParamBlock)
};

class ParamView    : public Component
{
public:
    ParamView(Ap_samplerAudioProcessor&);
    ~ParamView();

    void paint (Graphics&) override;
    void resized() override;

    //==============================================================================
    void setupSlider (Component& parent, std::unique_ptr<Slider>& slider, std::unique_ptr<Label>& label,
                      const String& name, const String& suffix = "s");
    void attachSlider (std::unique_ptr<Slider>& slider, std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>& attachment,
                       const String& paramID);

private:
    // Styling
    PirateStyle pirateSliderStyle_;

    // Components
    InfoScreen infoScreen_;
    ParamBlock adsrParams_;
    ParamBlock filterParams_;

    std::unique_ptr<Slider> attackSlider_, decaySlider_, sustainSlider_, releaseSlider_,
                                lowPassSlider_, bandPassSlider_, highPassSlider_;
    std::unique_ptr<Label> attackLabel_, decayLabel_, sustainLabel_, releaseLabel_,
                                lowPassLabel_, bandPassLabel_, highPassLabel_;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackAttachment_, decayAttachment_,
                                sustainAttachment_, releaseAttachment_, lowPassAttachment_, bandPassAttachment_,
                                highPassAttachment_;

    Ap_samplerAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParamView)
};
