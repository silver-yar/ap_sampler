/*
  ==============================================================================

    MainWindow.h
    Created: 1 Jun 2020 6:20:07pm
    Author:  Johnathan Handy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class MainWindow : public DocumentWindow
{
public:
    MainWindow() : DocumentWindow("test", Colours::snow, DocumentWindow::allButtons)
    {
        setFullScreen(true);
    }

    ~MainWindow()
    {
    }

    void paint (Graphics& g) override
    {

    }

    void resized() override
    {
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};
