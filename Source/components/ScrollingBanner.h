/*
  ==============================================================================

    ScrollingBanner.h
    Created: 10 Oct 2020 7:47:43pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "../styling/PirateStyle.h"

//==============================================================================
/*
*/
class ScrollingBanner  : public Component,
                         public Timer,
                         public ChangeListener
{
public:
    explicit ScrollingBanner(Ap_samplerAudioProcessor&);
    ~ScrollingBanner() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void changeListenerCallback (ChangeBroadcaster *source) override;

private:
    Ap_samplerAudioProcessor& processor;

    Bezel bezel_;
    Glare glare_;

    int index_ = 0;
    int x_, y_ = 0;
    int textWidth_ = 150;
    String filename_ { "loading..."};
    std::vector<String> bannerMessages_ {filename_, "audio_pirate", "ap_sampler"};
    DrawableText scrollText_;
    std::unique_ptr<Font> myFont_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScrollingBanner)
};
