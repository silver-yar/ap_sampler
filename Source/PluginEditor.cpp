/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Ap_samplerAudioProcessorEditor::Ap_samplerAudioProcessorEditor (Ap_samplerAudioProcessor& p)
    : AudioProcessorEditor (&p), interface_(p), processor (p)
{
    addAndMakeVisible(interface_);

    // TODO: Make the top parent component resizable : DONE
    setResizable(true, true);
    // TODO: Set max width and height using monitor size
    setResizeLimits(800, 400, 1600, 800);


    setSize(800, 400);
}

Ap_samplerAudioProcessorEditor::~Ap_samplerAudioProcessorEditor()
{
}

//==============================================================================

void Ap_samplerAudioProcessorEditor::paint (Graphics& g)
{
    // Background Layout
    g.fillAll(main_blue_);
    g.setColour(sec_blue_);
    g.fillRect(shadow_bounds_);

    // TODO: USE Flexbox to create layout for containers
}

void Ap_samplerAudioProcessorEditor::resized()
{
    shadow_bounds_.setWidth(getWidth());
    FlexBox flexBox;

    flexBox.flexDirection = FlexBox::Direction::columnReverse;
    flexBox.alignContent = FlexBox::AlignContent::flexStart;
    Array<FlexItem> flex_items;
    flex_items.add(FlexItem(getWidth() * 0.625f, getHeight() * 0.25f, interface_));
    //flex_items.add(FlexItem(getWidth(), getHeight() * 0.1f));
    flexBox.items.addArray(flex_items);

    flexBox.performLayout(getLocalBounds().reduced(10.0f));
}
