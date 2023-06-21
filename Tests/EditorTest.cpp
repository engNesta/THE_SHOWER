//
// Created by Nesta on 2023-06-20.
//
#define CATCH_CONFIG_MAIN
#include "../Source/MainComponent.h"
#include <juce_core/juce_core.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include "Catch2/src/catch2/catch_test_macros.hpp"

TEST_CASE("Plugin Editor GUI Display Test", "[plugin_editor]")
{
    juce::AudioPluginFormatManager formatManager;
    // ... Initialize the format manager and load plugins if needed
    formatManager.addDefaultFormats();

    juce::String errorMessage;

    std::unique_ptr<juce::AudioPluginInstance> pluginInstance = formatManager.createPluginInstance(/* Plugin parameters */);
    REQUIRE(pluginInstance != nullptr);

    juce::AudioProcessorEditor* editor = pluginInstance->createEditor();
    REQUIRE(editor != nullptr);

    // Add assertions to check if the editor is properly displayed
    REQUIRE(editor->getWidth() == 300);
    REQUIRE(editor->getHeight() == 200);


}