//
// Created by Nesta on 2023-06-17.
//

#include "VstGuiEditor.h"
VstGuiEditor::VstGuiEditor(juce::AudioProcessor *processor) : juce::AudioProcessorEditor(processor) {}

VstGuiEditor::~VstGuiEditor() {}

void VstGuiEditor::paint(juce::Graphics &g) {
    g.fillAll(juce::Colours::black);
}

void VstGuiEditor::resized() {
    juce::Rectangle<int> area = getLocalBounds();

    if(juce::AudioProcessor* processor = getAudioProcessor()){
        if(juce::AudioProcessorEditor* editor = processor->createEditorIfNeeded()){
            addAndMakeVisible(editor);
            editor->setBounds(area);
        }
    }
    else{
        juce::Label* label = new juce::Label("no-plugin", "No Plugin Loaded");
        label->setBounds(area);
        addAndMakeVisible(label);
    }
}