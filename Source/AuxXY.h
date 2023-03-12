/*
  ==============================================================================

    AuxXY.h
    Created: 23 Feb 2023 12:50:37pm
    Author:  satya

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AuxXY_Point.h"
#include "BezierCurve.h"
//==============================================================================
/*
*/
class AuxXY  : public juce::Component
{
public:
    AuxXY(juce::AudioParameterFloat* x,juce::AudioParameterFloat* y);
    ~AuxXY() override;

    void paint (juce::Graphics&) override;
    void resized() override;


private:
    AuxXY_Point p1;
    bool init = true;
    AuxPort::Bezier bezier;

    juce::Point<float> start;
    juce::Point<float> end;
    juce::Point<float> mid;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AuxXY)
};
