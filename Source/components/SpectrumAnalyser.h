/*
  ==============================================================================

    SpectrumAnalyser.h
    Created: 8 Oct 2020 1:50:13pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

//==============================================================================
/*
*/
class SpectrumAnalyser  : public juce::Component
{
public:
    SpectrumAnalyser(Ap_samplerAudioProcessor&);
    ~SpectrumAnalyser() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void drawNextFrameOfSpectrum();
//    enum
//    {
//        fftOrder = 11,
//        fftSize = 1 << fftOrder,
//        scopeSize = 512
//    };

private:
    Ap_samplerAudioProcessor& processor;

    dsp::FFT forwardFFT_;
    dsp::WindowingFunction<float> window_;
    dsp::WindowingFunction<float>::WindowingMethod windowType_ = dsp::WindowingFunction<float>::hann;
//    float fifo_ [fftSize];
//    float fftData_ [2 * fftSize];
//    int fifoIndex_ { 0 };
//    bool nextFFTBlockReady_ { false };
//    float scopeData_ [scopeSize];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrumAnalyser)
};
