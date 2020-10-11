/*
  ==============================================================================

    SampleView.cpp
    Created: 1 Jun 2020 8:47:27pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SampleView.h"
#include "../styling/PirateColors.h"

//==============================================================================
SampleView::SampleView(Ap_samplerAudioProcessor& p) : processor (p), spectrum_ (p), bezel_ (16), glare_ (8)
{
    addChildComponent (spectrum_, -10);
    addAndMakeVisible (bezel_);
    addAndMakeVisible (glare_);
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

    drawFileName (g);

    if (processor.getWaveForm().getNumSamples() > 0 && processor.curr_group == processor.adsr) {
        g.setColour (PirateColors::green2);
        g.drawText(String(processor.getSampleRate()) + " Hz", getLocalBounds().reduced (10),
                   Justification::centredTop, false);

        if (!processor.hideEnv) {
            spectrum_.setVisible (false);
            drawWaveform (g);
            drawADSR (g);
        } else {
            spectrum_.setVisible (false);
            drawWaveform(g);
        }
    }
    else if (processor.getWaveForm().getNumSamples() > 0 && processor.curr_group == processor.filter) {
        g.setColour (PirateColors::green2);
        g.drawText(String(processor.getSampleRate()) + " Hz", getLocalBounds().reduced (10),
                   Justification::centredTop, false);

        if (!processor.hideEnv) {
            drawFilter (g);
            drawAxis (g);
            spectrum_.setVisible (true);
        } else {
            drawAxis (g);
            spectrum_.setVisible (true);
        }
    }
    else if (processor.getWaveForm().getNumSamples() <= 0)
        drawWaveform (g);

    //PirateStyle::drawGlare (g, getWidth(), getHeight(), 8);

    //PirateStyle::drawBezel (g, getWidth(), getHeight(), 16);
}

void SampleView::resized()
{
    auto localBounds = getLocalBounds();
    spectrum_.setBounds (0,16, localBounds.getWidth(), localBounds.getHeight() - 16);
    bezel_.setBounds (localBounds);
    glare_.setBounds (localBounds);
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
                      textBounds,
                      fileName.isNotEmpty() ? Justification::topRight : Justification::bottomRight,
                      1);
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
    auto envHeight = jmap<float> (*processor.apvts.getRawParameterValue ("VOL"),
                                  -40.0f, 40.0f, startHeight, 16.0f);
    auto attack = jmap<float> (adsrPoints_[0], 0.0f, 5.0f, startWidth, firstStop);
    auto decay = jmap<float> (adsrPoints_[1], 0.0f, 5.0f, startWidth, firstStop);
    auto sustain = jmap<float> (adsrPoints_[2], -60.0f, 0.0f, startHeight, envHeight);
    auto release = jmap<float> (adsrPoints_[3], 0.0f, 5.0f, secondStop, width - 16.0f);
    auto control = jmap<float> (adsrPoints_[3], 0.0f, 5.0f, 20.0f, 5.0f);


    g.setColour (PirateColors::orange1.withAlpha(0.8f));

    p.startNewSubPath (start);
    p.lineTo (Point<float> (attack, envHeight));
    p.lineTo (Point<float> (attack + 5, sustain));
    p.lineTo (Point<float> (decay + attack, sustain));
    p.lineTo (Point<float> (secondStop, sustain));
    p.quadraticTo(Point<float> (release == secondStop ? release : release - (release / control), startHeight - 32.0f),
            Point<float> (release, startHeight));
    // Draw Attack Point
    p.addRoundedRectangle (attack - (pointSize / 2), envHeight - (pointSize / 2),
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
    g.setColour (PirateColors::orange1.withAlpha (0.3f));
    g.fillPath (p);
}

void SampleView::mouseDown(const MouseEvent &e) {
    // TODO: Only show file chooser in standalone / causes crash
//    auto bounds = getLocalBounds();
//
//    if (bounds.contains (e.getMouseDownPosition()) && processor.getWaveForm().getNumSamples() == 0) {
//        fileChooser_.browseForFileToOpen();
//        auto path = fileChooser_.getResult().getFullPathName();
//        processor.loadFile (path);
//    }
}

void SampleView::drawAxis (Graphics &g) {
    auto width = getWidth();
    auto height = getHeight();
    auto startWidth = 16;
    auto startHeight = height - startWidth;
    auto endWidth = width - 16;

    // Draw Freq X-Axis
    auto textWidth = 50.0f;
    auto m100 = mapFromLog10 (100.0f, 20.0f, 22000.0f);
    m100 = jmap<float> (m100, startWidth, endWidth);
    auto m1000 = mapFromLog10 (1000.0f, 20.0f, 22000.0f);
    m1000 = jmap<float> (m1000, startWidth, endWidth);
    auto m10000 = mapFromLog10 (10000.0f, 20.0f, 22000.0f);
    m10000 = jmap<float> (m10000, startWidth, endWidth);

    g.setColour (PirateColors::green2);

    Path axis;
    // 100
    axis.startNewSubPath (Point<float> (m100, startHeight - 16));
    axis.lineTo (Point<float> (m100, 32));
    axis.closeSubPath();
    g.strokePath (axis, PathStrokeType (1));

    // 1000
    axis.startNewSubPath (Point<float> (m1000, startHeight - 16));
    axis.lineTo (Point<float> (m1000, 32));
    axis.closeSubPath();
    g.strokePath (axis, PathStrokeType (1));

    // 10000
    axis.startNewSubPath (Point<float> (m10000, startHeight - 16));
    axis.lineTo (Point<float> (m10000, 32));
    axis.closeSubPath();
    g.strokePath (axis, PathStrokeType (1));

    g.setColour (PirateColors::green2);
    g.setFont (10.0f);
    g.drawText ("100",m100 - (textWidth / 2), startHeight - 8, textWidth,
                5, Justification::centred, false);
    g.drawText ("1000",m1000 - (textWidth / 2), startHeight - 8, textWidth,
                5, Justification::centred, false);
    g.drawText ("10000",m10000 - (textWidth / 2), startHeight - 8, textWidth,
                5, Justification::centred, false);
}

void SampleView::drawFilter(Graphics &g) {
    auto width = getWidth();
    auto height = getHeight();
    auto startWidth = 16;
    auto startHeight = height - startWidth;
    auto endWidth = width - 16;
    auto shift = 16;

    // TODO: Draw filter envelope with height being gain and with mapped to slider frequency
    float freq_val;
    float freq;
    float gain = jmap<float> (*processor.apvts.getRawParameterValue("VOL"),
                              -40.0f, 40.0f, startHeight, 16);
    auto start = Point<float> (startWidth, startHeight);
    Path p;

    switch (processor.getFilterType()) {
        case Ap_samplerAudioProcessor::FilterType::low_pass: // Low Pass
            g.setColour (Colours::red);
            freq_val = *processor.apvts.getRawParameterValue("LPF");
            // Draw Filter Envelope
            freq = mapFromLog10 (freq_val, 20.0f, 22000.0f);
            freq = jmap<float> (freq, startWidth, endWidth);

            p.startNewSubPath (start);
            p.lineTo (Point<float> (startWidth, gain));
            p.lineTo (Point<float> (freq - (shift * 2.0f), gain));
            p.quadraticTo(Point<float> (freq, gain),
                    Point<float> (freq, startHeight));
            p.closeSubPath();

            g.strokePath (p, PathStrokeType (2));
            g.setColour (Colours::red.withAlpha (0.3f));
            g.fillPath (p);
            break;
        case Ap_samplerAudioProcessor::FilterType::band_pass: // Band Pass
            g.setColour (Colours::yellow);
            freq_val = *processor.apvts.getRawParameterValue("BPF");
            // Draw Filter Envelope
            freq = mapFromLog10 (freq_val, 20.0f, 22000.0f);
            freq = jmap<float> (freq, startWidth, endWidth);

            p.startNewSubPath (Point<float> (freq - (3 * shift), startHeight));
            p.quadraticTo (Point<float> (freq - (3 * shift), gain),
                    Point<float> (freq, gain));
            //p.lineTo (Point<float> (freq - shift, gain));
            //p.lineTo (Point<float> (freq + shift, gain));
            p.quadraticTo (Point<float> (freq + (3 * shift), gain),
                    Point<float> (freq + (3 * shift), startHeight));
            p.closeSubPath();

            g.strokePath (p, PathStrokeType (2));
            g.setColour (Colours::yellow.withAlpha (0.3f));
            g.fillPath (p);
            break;
        case Ap_samplerAudioProcessor::FilterType::high_pass: // High Pass
            g.setColour (Colours::rebeccapurple);
            freq_val = *processor.apvts.getRawParameterValue("HPF");
            // Draw Filter Envelope
            freq = mapFromLog10 (freq_val, 20.0f, 22000.0f);
            freq = jmap<float> (freq, startWidth, endWidth);

            p.startNewSubPath (Point<float> (endWidth, startHeight));
            p.lineTo (Point<float> (endWidth, gain));
            p.lineTo (Point<float> (freq + (shift * 2.0f), gain));
            p.quadraticTo(Point<float> (freq, gain),
                          Point<float> (freq, startHeight));
            p.closeSubPath();

            g.strokePath (p, PathStrokeType (2));
            g.setColour (Colours::rebeccapurple.withAlpha (0.3f));
            g.fillPath (p);
            break;
        default:
            break;
    }
}
