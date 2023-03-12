/*
  ==============================================================================

    AuxXY_Point.h
    Created: 23 Feb 2023 1:27:52pm
    Author:  satya

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AuxXY_Point  : public juce::Component
{
public:
    AuxXY_Point(juce::AudioParameterFloat* xParam,juce::AudioParameterFloat* yParam);
    ~AuxXY_Point() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setColour(const juce::Colour& colour)
    {
        this->pointColour = colour;
        repaint();
    }
    juce::Point<int> origin = { 0,0 };
    juce::Point<int> coordinate;
    int32_t _width = 0;
    int32_t _height = 0;
    
    void mouseDrag(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;
private:
    juce::Colour pointColour;
    juce::AudioParameterFloat* xCoordinate;
    juce::AudioParameterFloat* yCoordinate;
    std::mutex mutex;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AuxXY_Point)
};
