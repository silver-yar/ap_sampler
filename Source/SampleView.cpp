/*
  ==============================================================================

    SampleView.cpp
    Created: 1 Jun 2020 8:47:27pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SampleView.h"
#include "PluginProcessor.h"

//==============================================================================
SampleView::SampleView(Ap_samplerAudioProcessor& p) : processor (p)
{
    startTimerHz(60);
}

SampleView::~SampleView()
{
    stopTimer();
}

void SampleView::paint (Graphics& g)
{
    g.fillAll (green1_);

    g.setColour (Colours::white);
    g.setFont (14.0f);

    drawWaveform(g);

//    if (fileLoaded_) {
//        drawWaveform(g);
//    } else {
//        g.drawText ("SampleView", getLocalBounds(),
//                    Justification::centred, true);   // draw some placeholder text
//    }

}

void SampleView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}

void SampleView::drawWaveform(Graphics& g)
{
    auto waveform = processor.getWaveForm();

    if (waveform.getNumSamples() > 0)
    {
        //g.fillAll (Colours::green);

        // Draw Waveform
        Path p;
        audioPoints_.clear();

        auto ratio = waveform.getNumSamples() / getWidth();
        auto buffer = waveform.getReadPointer (0);

        //scale audio file to window on x axis
        for (int sample = 0; sample < waveform.getNumSamples(); sample+=ratio)
        {
            audioPoints_.push_back (buffer[sample]);
        }

        g.setColour (green2_);
        p.startNewSubPath (0, getHeight() / 2);

        //scale on y axis
        for (auto sample = 0; sample < audioPoints_.size(); ++sample)
        {
            auto point = jmap<float> (audioPoints_[sample], -1.0f, 1.0f, getHeight(), 0);
            p.lineTo (sample, point);
        }

        g.strokePath(p, PathStrokeType (2));

        // Playhead
        auto playHeadPosition = jmap<int> (processor.getSampleCount(), 0,
                                           waveform.getNumSamples(), 0, getWidth());
        g.setColour (Colour(0xffffc000));
        g.drawLine (playHeadPosition, 0, playHeadPosition, getHeight(), 8.0f);
        g.setColour (Colour(0xffffc000).withAlpha(0.2f));
        g.fillRect (0, 0, playHeadPosition, getHeight());


        // Draw File Name
        g.setColour (green2_);
        //g.setFont (def_f_size);
        auto textBounds = getLocalBounds().reduced (20, 10);
        g.drawFittedText (processor.getFileName(), textBounds, Justification::bottomRight, 1);
    }
}

void SampleView::timerCallback()
{
    repaint();
}
