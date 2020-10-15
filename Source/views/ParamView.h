/*
  ==============================================================================

    ParamView.h
    Created: 1 Jun 2020 8:47:45pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "../styling/PirateStyle.h"
#include "../components/InfoScreen.h"

class LabelSlider;

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
    }

    void layoutSliders (Array<LabelSlider*>& sliders);

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
    void setupSlider (Component& parent, std::unique_ptr<LabelSlider>& label_slider,
                      const String& name, bool isEnabled = true, const String& suffix = "s");
    void attachSlider (std::unique_ptr<LabelSlider>& label_slider, std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>& attachment,
                       const String& paramID);

private:
    // Components
    InfoScreen infoScreen_;
    ParamBlock adsrParams_;
    ParamBlock filterParams_;
    ParamBlock miscParams_;

    std::unique_ptr<LabelSlider> attackSlider_, decaySlider_, sustainSlider_, releaseSlider_,
                                lowPassSlider_, bandPassSlider_, highPassSlider_, gainSlider_,
                                sampleRateSlider_, bitRateSlider_;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackAttachment_, decayAttachment_,
                                sustainAttachment_, releaseAttachment_, lowPassAttachment_, bandPassAttachment_,
                                highPassAttachment_, gainAttachment_, sarAttachment_, brAttachment_;

    Ap_samplerAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParamView)
};
