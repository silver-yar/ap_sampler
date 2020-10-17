/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "views/InterfaceView.h"
#include "views/SampleView.h"
#include "views/ParamView.h"
#include "components/ScrollingBanner.h"

//==============================================================================
/**
*/
class Ap_samplerAudioProcessorEditor  : public AudioProcessorEditor,
                                        public FileDragAndDropTarget
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

    bool isInterestedInFileDrag (const StringArray& files) override;
    void filesDropped (const StringArray& files, int x, int y) override;

private:
    class SettingsButton : public Component {
    public:
        SettingsButton() {};
        ~SettingsButton() {};

        void paint (Graphics& g) override {
            auto bounds = getLocalBounds();
            auto top = bounds.removeFromTop(bounds.getHeight() * 0.15f);

            g.fillAll (Colours::grey);
            g.setColour (Colours::grey.darker(0.3f));
            g.fillRect (top);
        };
        void resized() override
        {

        };
        void mouseDown (const MouseEvent& e) override
        {

        };
    private:

    };
    // Objects
    Ap_samplerAudioProcessor& processor;
    ChangeBroadcaster broadcaster_;

    // Components
    ScrollingBanner banner_;
    SampleView sampleView_;
    InterfaceView interfaceView_;
    ParamView paramView_;
    SettingsButton settingsButton_;

    // Styling
    FlexBox iFlexBox_, oFlexBox_; // Inner and outer flex boxes (respectively)

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Ap_samplerAudioProcessorEditor)
};
