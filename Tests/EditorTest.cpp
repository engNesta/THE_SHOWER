//
// Created by Nesta on 2023-06-20.
//
#define CATCH_CONFIG_MAIN
#include "../Source/MainComponent.h"
#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include "Catch2/src/catch2/catch_test_macros.hpp"
//REMEMBER TO CALL THE JUCE NAMESPACE WHEN USING JUCE CLASSES

TEST_CASE("Plugin Editor GUI Display Test")
{

    MainComponent mainComponent;

    SECTION("Vst3 data retrieval Test")
    {
        juce::File file = juce::File("/Users/nesta99/Desktop/Degree Thesis/ShowerTest.vst3");
        mainComponent.retrieveVST3data(file);
        REQUIRE(mainComponent.infoLabel.getText() == file.getFileNameWithoutExtension() + "\n" +
                                                     file.getFileExtension() + "\n" +
                                                     file.getFullPathName());
    }

    SECTION("Vst3 Plugin Hosting Test")
    {
        juce::File file = juce::File("/Users/nesta99/Desktop/Degree Thesis/ShowerTest.vst3");

        juce::AudioPluginFormatManager formatManager;
        formatManager.addDefaultFormats();

        PluginDescription vst3Description;
        vst3Description.fileOrIdentifier = file.getFullPathName();
        vst3Description.uniqueId = 0;
        vst3Description.name = file.getFileNameWithoutExtension();
        vst3Description.pluginFormatName = file.getFileExtension();

        OwnedArray<PluginDescription> typesFound;
        AudioPluginFormat * format = formatManager.getFormat(0);

        KnownPluginList pluginList;
        pluginList.scanAndAddFile(vst3Description.fileOrIdentifier, true, typesFound, *format);

        juce::String errorMessage;
        mainComponent.vst3Instance = formatManager.createPluginInstance(*typesFound[0], 44100.0, 512, errorMessage);

        REQUIRE(mainComponent.vst3Instance != nullptr);

    }

    SECTION("Test Editor")
    {
        juce::File file = juce::File("/Users/nesta99/Desktop/Degree Thesis/ShowerTest.vst3");

        juce::AudioPluginFormatManager formatManager;
        formatManager.addDefaultFormats();

        PluginDescription vst3Description;
        vst3Description.fileOrIdentifier = file.getFullPathName();
        vst3Description.uniqueId = 0;
        vst3Description.name = file.getFileNameWithoutExtension();
        vst3Description.pluginFormatName = file.getFileExtension();

        OwnedArray<PluginDescription> typesFound;
        AudioPluginFormat * format = formatManager.getFormat(0);

        KnownPluginList pluginList;
        pluginList.scanAndAddFile(vst3Description.fileOrIdentifier, true, typesFound, *format);

        juce::String errorMessage;
        mainComponent.vst3Instance = formatManager.createPluginInstance(*typesFound[0], 44100.0, 512, errorMessage);

        juce::AudioProcessor * vst3Processor = mainComponent.vst3Instance.get();

        juce::AudioProcessorEditor * vstEditor = vst3Processor->createEditor();

        REQUIRE(vstEditor != nullptr);
        REQUIRE(vstEditor->getWidth() == 300);
        REQUIRE(vstEditor->getHeight() == 200);

    }


}