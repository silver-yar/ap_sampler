/*
  ==============================================================================

    SpectrumAnalyser.cpp
    Created: 8 Oct 2020 1:50:13pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SpectrumAnalyser.h"
#include "../styling/PirateColors.h"

//==============================================================================
SpectrumAnalyser::SpectrumAnalyser(Ap_samplerAudioProcessor& p) : processor (p),
                                                                  forwardFFT_ (processor.fftOrder),
                                                                  window_ (processor.fftSize,
                                                                           dsp::WindowingFunction<float>::hann)
{
}

SpectrumAnalyser::~SpectrumAnalyser()
{
}

void SpectrumAnalyser::paint (juce::Graphics& g)
{
   if (processor.isFFTBlockReady()) {
       drawNextFrameOfSpectrum();
       processor.setFFTBlockReady (false);
       drawFrame (g);
   }
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

    for (int i = 0; i < scopeSize; ++i)
    {
        auto skewedProportionX = 1.0f - std::exp (std::log (1.0f - (float) i / (float) scopeSize) * 0.2f);
        auto fftDataIndex = jlimit (0, processor.fftSize / 2,
                                          (int) (skewedProportionX * (float) processor.fftSize * 0.5f));
        auto level = jmap (jlimit (mindB, maxdB,
                                               juce::Decibels::gainToDecibels (fftData[fftDataIndex])
                                                             - juce::Decibels::gainToDecibels ((float) processor.fftSize)),
                                 mindB, maxdB, 0.0f, 1.0f);

        scopeData_[i] = level;
    }

}

void SpectrumAnalyser::drawFrame(Graphics& g)
{
    auto lineThickness = 2.0f;
    g.setColour (PirateColors::green2);
    for (int i = 1; i < scopeSize; ++i)
    {
        auto width  = getLocalBounds().getWidth();
        auto height = getLocalBounds().getHeight();

        g.drawLine ({ (float) juce::jmap (i - 1, 0, scopeSize - 1, 16, width - 16),
                      juce::jmap (scopeData_[i - 1], 0.0f, 1.0f, (float) height, 0.0f),
                      (float) juce::jmap (i,     0, scopeSize - 1, 16, width - 16),
                      juce::jmap (scopeData_[i],     0.0f, 1.0f, (float) height, 0.0f) },
                        lineThickness
                    );
    }
}
