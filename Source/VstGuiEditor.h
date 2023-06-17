//
// Created by Nesta on 2023-06-17.
//

#ifndef THE_SHOWER_VSTGUIEDITOR_H
#define THE_SHOWER_VSTGUIEDITOR_H
#include <JuceHeader.h>

class VstGuiEditor : public juce::AudioProcessorEditor{
public:
    VstGuiEditor(juce::AudioProcessor* processor);
    ~VstGuiEditor() override;

    void paint(juce::Graphics &g) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VstGuiEditor);
};


#endif //THE_SHOWER_VSTGUIEDITOR_H
