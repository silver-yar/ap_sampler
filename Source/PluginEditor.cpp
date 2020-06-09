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
    : AudioProcessorEditor (&p),
      interfaceView_(p),
      processor (p)
{
    setResizable(true, true);
    // TODO: Set max width and height using monitor size
    setResizeLimits(800, 400, 1600, 800);

    setupFlexBoxes();
    setupFlexItems();
    setSize(800, 450);
}

Ap_samplerAudioProcessorEditor::~Ap_samplerAudioProcessorEditor()
{
}

//==============================================================================

void Ap_samplerAudioProcessorEditor::resized() {
    oFlexBox_.performLayout (getFlexBounds().toNearestInt());
}

void Ap_samplerAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::dodgerblue.darker(0.5f));
    g.setColour (Colours::dodgerblue);
    g.fillRect(getFlexBounds());
}

Rectangle<float> Ap_samplerAudioProcessorEditor::getFlexBounds() const
{
    return getLocalBounds().withTrimmedTop (getHeight() * .15f).toFloat();
}

void Ap_samplerAudioProcessorEditor::setupFlexBoxes()
{
    iFlexBox_.flexDirection = FlexBox::Direction::column;
    iFlexBox_.justifyContent = FlexBox::JustifyContent::spaceAround;
    iFlexBox_.alignItems = FlexBox::AlignItems::center;
    oFlexBox_.flexDirection = FlexBox::Direction::row;
    oFlexBox_.justifyContent = FlexBox::JustifyContent::spaceAround;
    oFlexBox_.alignItems = FlexBox::AlignItems::stretch;
}

void Ap_samplerAudioProcessorEditor::setupFlexItems()
{
    addItem (iFlexBox_, sampleView_, 2, 10);
    addItem (iFlexBox_, interfaceView_, 1, 10);
    addFlex (oFlexBox_, iFlexBox_, 2);
    addItem (oFlexBox_, paramView_, 1, 10);
}

void Ap_samplerAudioProcessorEditor::addItem(FlexBox& flexBox, Component& item, float grow, float margin)
{
    flexBox.items.add (FlexItem (item).withFlex (grow, 0, 10).withMargin(FlexItem::Margin(margin)));
    auto& flexItem = flexBox.items.getReference (flexBox.items.size() - 1);
    flexItem.associatedComponent = &item;
    addAndMakeVisible (item);
}

void Ap_samplerAudioProcessorEditor::addFlex(FlexBox& parentFlexBox, FlexBox& childFlexBox, float grow)
{
    parentFlexBox.items.add (FlexItem (childFlexBox).withFlex (grow, 0, 10));
}


