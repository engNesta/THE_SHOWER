#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component, public juce::Button::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    juce::TextButton loadButton;
    juce::Label infoLabel;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button *button) override;
    void loadFile();
    void retrieveVST3data(juce::File &file);
    void hostVST3(juce::File &file);

private:
    //==============================================================================
    // Your private member variables go here...
    std::unique_ptr<juce::FileChooser> fileChooser;
    juce::AudioPluginFormatManager formatManager;
    PluginDescription vst3Description;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
