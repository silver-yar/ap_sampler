/*
  ==============================================================================

    SpectrumAnalyser.cpp
    Created: 8 Oct 2020 1:50:13pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SpectrumAnalyser.h"
#include "../PluginProcessor.h"

//==============================================================================
SpectrumAnalyser::SpectrumAnalyser(Ap_samplerAudioProcessor& p) : processor (p),
                                                                  forwardFFT_ (processor.fftOrder),
                                                                  window_ (processor.fftSize, windowType_),
                                                                  scopeData_ (scopeData_[processor.scopeSize])
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

SpectrumAnalyser::~SpectrumAnalyser()
{
}

void SpectrumAnalyser::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("SpectrumAnalyser", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void SpectrumAnalyser::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void SpectrumAnalyser::drawNextFrameOfSpectrum()
{
    auto fftData = processor.getFFTData();
    // Apply windowing function
    window_.multiplyWithWindowingTable (fftData, processor.fftSize);
    // render FFT data
    forwardFFT_.performFrequencyOnlyForwardTransform (fftData);

    auto mindB = -100.0f;
    auto maxdB = 0.0f;

    for (int i = 0; i < processor.scopeSize; ++i)
    {
        auto skewedProportionX = 1.0f - std::exp (std::log (1.0f - (float) i / (float) processor.scopeSize) * 0.2f);
        auto fftDataIndex = juce::jlimit (0, processorfftSize / 2, (int) (skewedProportionX * (float) fftSize * 0.5f));
        auto level = juce::jmap (juce::jlimit (mindB, maxdB, juce::Decibels::gainToDecibels (fftData[fftDataIndex])
                                                             - juce::Decibels::gainToDecibels ((float) fftSize)),
                                 mindB, maxdB, 0.0f, 1.0f);

        processor.scopeData[i] = level;
    }

}
