/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "InterfaceView.h"
#include "SampleView.h"
#include "ParamView.h"

//==============================================================================
/**
*/
class Ap_samplerAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Ap_samplerAudioProcessorEditor (Ap_samplerAudioProcessor&);
    ~Ap_samplerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    //==============================================================================
    Rectangle<float> getFlexBounds() const;
    void setupFlexBoxes(); // Setup for the inner and outer flex boxes
    void setupFlexItems(); // Setup for the inner and outer flex items
    void addItem(FlexBox& flexBox, Component& item, float grow, float margin); // Add a component to a flex box
    static void addFlex(FlexBox& parentFlexBox, FlexBox& childFlexBox, float grow); // Add a flex box to a flex box

private:
//    Rectangle<float> shadow_bounds_ {0.0f, 0.0f, (float)getWidth(), 50.0f};
//    Rectangle<float> front_bounds_ {0.0f, 50.0f, (float)getWidth(), 350};
//    Rectangle<float> frontFace_;
//    Rectangle<float> topFace_;

    // Colour Palette
    Colour main_blue_{ 0xff3056bf };
    Colour sec_blue_{0xff203980};

    //FlexBoxes
    FlexBox iFlexBox_, oFlexBox_;

    // Child Components
    InterfaceView interfaceView_;
    SampleView sampleView_;
    ParamView paramView_;

    Ap_samplerAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Ap_samplerAudioProcessorEditor)
};
