/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================
AuxParamAudioProcessorEditor::AuxParamAudioProcessorEditor (AuxParamAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    addAndMakeVisible(gainSlider);
    auto gainParameter = audioProcessor.parameterMap->getFloatParameter("Gain");
    gainSlider.setRange(gainParameter->range.start, gainParameter->range.end, 0.01);
    gainSlider.setValue(*gainParameter);

    gainSlider.onValueChange = [this, gainParameter]
    {
        *gainParameter = gainSlider.getValue();
        gainSlider.setValue(*gainParameter);
    };
}

AuxParamAudioProcessorEditor::~AuxParamAudioProcessorEditor()
{
}

//==============================================================================
void AuxParamAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

   
}

void AuxParamAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto x = getBounds().getWidth()/10;
    auto y = getBounds().getHeight()/10;
    

    gainSlider.setBounds(2.5 * x, 2.5 * y, 5 * x, 5 * y);
}
