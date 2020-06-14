/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PirateColors.h"

//==============================================================================
Ap_samplerAudioProcessorEditor::Ap_samplerAudioProcessorEditor (Ap_samplerAudioProcessor& p)
    : AudioProcessorEditor (&p),
      processor (p),
      sampleView_ (p),
      interfaceView_ (p)

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
    oFlexBox_.performLayout (getFlexBounds().reduced(15).toNearestInt());
}

void Ap_samplerAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (PirateColors::blue2);
    g.setColour (PirateColors::blue1);
    g.fillRect(getFlexBounds());
//    g.setColour (Colours::white);
//    g.setFont(40);
//    g.drawText ("audio pirate", Rectangle<int>(getWidth(), getHeight() * .15f),
//            Justification::centred, true);
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
    addItem (iFlexBox_, sampleView_, 2, 5);
    addItem (iFlexBox_, interfaceView_, 1, 5);
    addFlex (oFlexBox_, iFlexBox_, 2);
    addItem (oFlexBox_, paramView_, 1, 5);
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

bool Ap_samplerAudioProcessorEditor::isInterestedInFileDrag (const StringArray& files)
{
    for (const auto& file : files)
    {
        if (file.contains(".wav") || file.contains(".mp3") || file.contains(".aif"))
        {
            return true;
        }
    }
    return false;
}
void Ap_samplerAudioProcessorEditor::filesDropped (const StringArray& files, int x, int y)
{
    for (const auto& file : files)
    {
        if (isInterestedInFileDrag(file))
        {
            processor.loadFile(file);
        }
    }
}


