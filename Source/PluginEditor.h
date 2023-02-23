/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class AuxParamAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    AuxParamAudioProcessorEditor (AuxParamAudioProcessor&);
    ~AuxParamAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AuxParamAudioProcessor& audioProcessor;
    juce::Slider gainSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AuxParamAudioProcessorEditor)
};
