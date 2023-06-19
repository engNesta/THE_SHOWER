#include "MainComponent.h"


//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 600);

    loadButton.setButtonText("LOAD VST3 PLUGIN");

    loadButton.setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(250, 249, 246));
    loadButton.setColour(juce::TextButton::textColourOnId, juce::Colour::fromRGB(18, 18, 18));
    loadButton.setColour(juce::TextButton::textColourOffId, juce::Colour::fromRGB(18, 18, 18));

    loadButton.addListener(this);

    infoLabel.setText("VST3 LOADER", juce::dontSendNotification);
    infoLabel.setColour(juce::Label::textColourId, juce::Colour::fromRGB(250, 249, 246));
    addAndMakeVisible(infoLabel);
    addAndMakeVisible(loadButton);




}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    juce::Colour offBlack = juce::Colour::fromRGB(18, 18, 18);
    juce::Colour offWhite = juce::Colour::fromRGB(250, 249, 246);

    g.fillAll (offBlack);

    g.setColour (offWhite);

    g.drawLine(150, 0, 155, 600);
    g.drawLine(450, 0, 455, 600);

}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    loadButton.setBounds(175 , 275, 240, 50);
    infoLabel.setBounds(170, 500, 400, 50);
}

void MainComponent::buttonClicked(juce::Button *button){
    if (button == &loadButton)
    {
        loadButton.setButtonText("LOADING...");
        loadFile();
        loadButton.setButtonText("LOAD VST3 PLUGIN");
    }
}

void MainComponent::loadFile()
{
    fileChooser = std::make_unique<FileChooser>("Select a VST3 Plugin", File::getSpecialLocation(File::userDesktopDirectory), "*.vst3");

    auto folderChooserFlags = FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles;

    fileChooser->launchAsync(folderChooserFlags, [this](const FileChooser& chooser) mutable
    {
        auto result = chooser.getResult();
        if (result.exists())
        {
            retrieveVST3data(result);
            hostVST3(result);

        }
    });
}

void MainComponent::retrieveVST3data(juce::File &file)
{


    vst3Description.fileOrIdentifier = file.getFullPathName();
    vst3Description.uniqueId = 0;
    vst3Description.name = file.getFileNameWithoutExtension();
    vst3Description.pluginFormatName = file.getFileExtension();

    infoLabel.setText(vst3Description.name + "\n" +
                      vst3Description.pluginFormatName + "\n" +
                      vst3Description.fileOrIdentifier,
                      juce::dontSendNotification);

}

void MainComponent::hostVST3(juce::File &file)
{
    formatManager.addDefaultFormats();

    OwnedArray<PluginDescription> typesFound;

    AudioPluginFormat* format = formatManager.getFormat(0);

    KnownPluginList pluginList;
    pluginList.scanAndAddFile(vst3Description.fileOrIdentifier, true, typesFound, *format);

    infoLabel.setText(typesFound[0]->name, juce::dontSendNotification);

    juce::String errorMessage;

    std::unique_ptr<AudioPluginInstance> vst3Instance = formatManager.createPluginInstance(*typesFound[0], 44100.0, 512, errorMessage);



    if(vst3Instance != nullptr)
    {
        createEditor(*vst3Instance);



    }
    else
    {
        infoLabel.setText("VST3 NOT LOADED", juce::dontSendNotification);
    }
}


void MainComponent::createEditor(AudioPluginInstance& pluginInstance)
{
    juce::AudioProcessorEditor * vstEditor = pluginInstance.createEditor();

    if (vstEditor != nullptr)
    {

        addAndMakeVisible(vstEditor);
        vstEditor->setBounds(70, 20, 300, 200);


    }
    else
    {
        infoLabel.setText("Failed to obtain AudioProcessor", juce::dontSendNotification);
    }
}


