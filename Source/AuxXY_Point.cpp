/*
  ==============================================================================

    AuxXY_Point.cpp
    Created: 23 Feb 2023 1:27:52pm
    Author:  satya

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AuxXY_Point.h"

//==============================================================================
AuxXY_Point::AuxXY_Point(juce::AudioParameterFloat* x,juce::AudioParameterFloat* y)
{
    this->xCoordinate = x;
    this->yCoordinate = y;


}

AuxXY_Point::~AuxXY_Point()
{
}

void AuxXY_Point::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::transparentBlack);

    juce::Path path;
    path.addEllipse(0, 0, this->getWidth(), this->getHeight());
    
    g.strokePath(path, juce::PathStrokeType(1));
    g.setColour(pointColour);
    g.fillPath(path);

    
}




void AuxXY_Point::mouseDrag(const juce::MouseEvent& event)
{

    
    
    auto deltaX = event.getDistanceFromDragStartX();
    auto deltaY = event.getDistanceFromDragStartY();
    
    deltaX += origin.x;
    deltaY += origin.y;


    coordinate.x = deltaX;
    coordinate.y = deltaY;

    
    
    

    if (coordinate.x > getParentComponent()->getWidth())
        coordinate.x = getParentComponent()->getWidth() - _width/2;
    if (coordinate.y > getParentComponent()->getHeight())
        coordinate.y = getParentComponent()->getHeight() - _height/2;
    if (coordinate.x < getParentComponent()->getX())
        coordinate.x = getParentComponent()->getX();
    if (coordinate.y < getParentComponent()->getY())
        coordinate.y = getParentComponent()->getY();


    getParentComponent()->resized();
    getParentComponent()->repaint();

  
}

void AuxXY_Point::mouseUp(const juce::MouseEvent& event)
{
    if (origin.x != coordinate.x || origin.y != coordinate.y)
    {
        origin = coordinate;
        const std::lock_guard<std::mutex> lock(std::mutex);
        *xCoordinate = static_cast<float>(coordinate.x) / static_cast<float>(getParentComponent()->getWidth());
        *yCoordinate = static_cast<float>(coordinate.y) / static_cast<float>(getParentComponent()->getHeight());

    }
    
}


void AuxXY_Point::resized()
{

}


