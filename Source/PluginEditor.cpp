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
    : AudioProcessorEditor (&p), processor (p)
{
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
    g.fillAll(Colour(0x3056bf));
    // TODO: USE Flexbox to create layout for containers
}

void Ap_samplerAudioProcessorEditor::resized()
{
//    FlexBox flexBox;
//
//    flexBox.flexDirection = FlexBox::Direction::column;
//    Array<FlexItem> flex_items;
//    flex_items.add(FlexItem(getWidth(), getHeight() * 0.1f));
//    flex_items.add(FlexItem(getWidth(), getHeight() * 0.1f));
//    flexBox.items.addArray(flex_items);
//
//    flexBox.performLayout(getLocalBounds());
}
