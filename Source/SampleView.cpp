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
#include "PirateStyle.h"
#include "PirateColors.h"

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
    g.fillAll (PirateColors::green1);
    g.setFont (14.0f);

    drawWaveform (g);
    drawFileName (g);
    if (processor.getWaveForm().getNumSamples() > 0 && !processor.hideAdsr)
        drawADSR (g);


    PirateStyle::drawBezel (g, getWidth(), getHeight(), 16);
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

        g.setColour (PirateColors::green2);
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
        g.drawLine (playHeadPosition, 0, playHeadPosition, getHeight(), 4.0f);
        g.setColour (Colour(0xffffc000).withAlpha(0.2f));
        g.fillRect (0, 0, playHeadPosition, getHeight());

    } else {
        g.setColour (PirateColors::green2);
        g.drawLine (0, getHeight() / 2, getWidth(), getHeight() / 2);
    }
}

void SampleView::drawFileName(Graphics& g)
{
    // Draw File Name
    auto fileName = processor.getFileName();
    g.setColour (PirateColors::green2);
    //g.setFont (def_f_size);
    auto textBounds = getLocalBounds().reduced (20, 10);
    g.drawFittedText (fileName.isNotEmpty() ? fileName : "Drag a sample here to load...",
                      textBounds, Justification::bottomRight, 1);
}

void SampleView::timerCallback()
{
    repaint();
}

void SampleView::drawADSR(Graphics& g) {
    auto params = processor.adsrParams;
    auto pointSize = 8.0f;
    auto width = getWidth();
    auto height = getHeight();
    auto startWidth = 16;
    auto startHeight = height - startWidth;
    auto envHeight = height / 2 - (height * 0.2f);
    auto firstStop = width / 3;
    auto secondStop = (width * 2) / 3 ;

    // Push adsr param values to vector
    adsrPoints_.clear();
    adsrPoints_.emplace_back (params.attack);
    adsrPoints_.emplace_back (params.decay);
    adsrPoints_.emplace_back (params.sustain);
    adsrPoints_.emplace_back (params.release);

    // Draw ADSR Envelope
    Path p;

    auto start = Point<float> (startWidth, startHeight);
    auto attack = jmap<float> (adsrPoints_[0], 0.0f, 5.0f, startWidth, firstStop);
    auto decay = jmap<float> (adsrPoints_[1], 0.0f, 5.0f, startWidth, firstStop);
    auto sustain = jmap<float> (adsrPoints_[2], -60.0f, 0.0f, startHeight, envHeight);
    auto release = jmap<float> (adsrPoints_[3], 0.0f, 5.0f, secondStop, width - 16.0f);
    auto control = jmap<float> (adsrPoints_[3], 0.0f, 5.0f, 20.0f, 5.0f);


    g.setColour (Colours::red.withAlpha(0.5f));

    p.startNewSubPath (start);
    p.lineTo (Point<float> (attack, envHeight));
    p.lineTo (Point<float> (attack + 5, sustain));
    p.lineTo (Point<float> (decay + attack, sustain));
    p.lineTo (Point<float> (secondStop, sustain));
    p.quadraticTo(Point<float> (release == secondStop ? release : release - (release / control), startHeight - 32.0f),
            Point<float> (release, startHeight));
    // Draw Attack Point
    p.addRoundedRectangle (attack - (pointSize / 2), sustain - (pointSize / 2),
                           pointSize, pointSize, 2.0f);
    // Draw Decay Point
    p.addRoundedRectangle (decay + attack - (pointSize / 2), sustain - (pointSize / 2),
                           pointSize, pointSize, 2.0f);
    // Draw Sustain Point
    p.addRoundedRectangle (secondStop - (pointSize / 2), sustain - (pointSize / 2),
                           pointSize, pointSize, 2.0f);
    // Draw Control Point
    p.addEllipse (release == secondStop ? release - (pointSize / 2) : release - (release / control) - (pointSize / 2),
            startHeight - 32.0f, pointSize, pointSize);
    // Draw Release Point
    p.addRoundedRectangle (release - (pointSize / 2), startHeight - (pointSize / 2), pointSize, pointSize, 2.0f);
    p.closeSubPath();

    g.strokePath (p, PathStrokeType (2));
}
