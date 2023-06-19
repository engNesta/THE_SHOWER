//
// Created by Nesta on 2023-06-17.
//

#ifndef THE_SHOWER_VSTGUIEDITOR_H
#define THE_SHOWER_VSTGUIEDITOR_H
#include <JuceHeader.h>

class VstGuiEditor : public juce::AudioProcessor{
public:
    VstGuiEditor(juce::AudioProcessor* processor);
    ~VstGuiEditor() override;



private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VstGuiEditor);
    juce::ResizableWindow *resizableWindow;
};


#endif //THE_SHOWER_VSTGUIEDITOR_H
