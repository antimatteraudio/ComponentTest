/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Components.h"

//==============================================================================
/**
*/
class ComponentTestAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ComponentTestAudioProcessorEditor (ComponentTestAudioProcessor&);
    ~ComponentTestAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    SceneComponent scene;
    
    ComponentTestAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ComponentTestAudioProcessorEditor)
};
