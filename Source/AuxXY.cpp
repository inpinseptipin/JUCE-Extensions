/*
  ==============================================================================

    AuxXY.cpp
    Created: 23 Feb 2023 12:50:37pm
    Author:  satya

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AuxXY.h"

//==============================================================================
AuxXY::AuxXY(juce::AudioParameterFloat* x, juce::AudioParameterFloat* y) : p1(x,y)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    p1.setColour(juce::Colours::blue);
    addChildAndSetID(&p1, "p1");
    p1.setVisible(true);
    bezier.setNumberOfPoints(50);
}

AuxXY::~AuxXY()
{
}



void AuxXY::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGBA(11, 12, 13, 180));

    g.drawLine(getWidth() / 2, 0, getWidth() / 2, getHeight());
    g.drawLine(0, getHeight() / 2, getWidth(), getHeight() / 2);
    
    start.x = 0;
    start.y = getHeight();

    end.x = getWidth();
    end.y = 0;

    mid.x = p1.coordinate.x;
    mid.y = p1.coordinate.y;

    juce::Path path1;

    bezier.setNormalizationFactors(getWidth(), getHeight());
    bezier.calcPoints(end, mid, start);
    
    g.setColour(juce::Colours::blue);
    for (uint32_t i = 1; i < 50; i++)
    {
        g.drawLine(bezier.getPoint(i - 1)->x, bezier.getPoint(i - 1)->y, bezier.getPoint(i)->x, bezier.getPoint(i)->y);
    }

}

void AuxXY::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
   
    if (init)
    {
        p1.coordinate.setX(getWidth()/2);
        p1.coordinate.setY(getHeight()/2);
        p1._width = getBounds().getWidth() / 20;
        p1._height = getBounds().getHeight() / 20;
        init = false;
    }
    


    p1.setBounds(p1.coordinate.getX(), p1.coordinate.getY(),p1._width, p1._height);
   
}





