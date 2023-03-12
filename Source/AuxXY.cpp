/*
*			AuxXY : Multipurpose XY pad for JUCE
            "2 Degrees of Freedom!! Les go" - inpinseptipin
            BSD 3-Clause License
            Copyright (c) 2023, Satyarth Arora
            All rights reserved.
            Redistribution and use in source and binary forms, with or without
            modification, are permitted provided that the following conditions are met:
            1. Redistributions of source code must retain the above copyright notice, this
               list of conditions and the following disclaimer.
            2. Redistributions in binary form must reproduce the above copyright notice,
               this list of conditions and the following disclaimer in the documentation
               and/or other materials provided with the distribution.
            3. Neither the name of the copyright holder nor the names of its
               contributors may be used to endorse or promote products derived from
               this software without specific prior written permission.
            THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
            AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
            IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
            DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
            FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
            DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
            SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
            CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
            OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
            OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <JuceHeader.h>
#include "AuxXY.h"



AuxPort::UI::AuxXY::AuxPoint::AuxPoint(juce::AudioParameterFloat* x, juce::AudioParameterFloat* y)
{
    this->x = x;
    this->y = y;
    this->pointColour = juce::Colours::green;
    drawingBool = false;
    origin = { 0,0 };
}

AuxPort::UI::AuxXY::AuxPoint::~AuxPoint()
{
}

void AuxPort::UI::AuxXY::AuxPoint::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::transparentBlack);
    if (drawingBool)
    {
        g.strokePath(ellipsePath, juce::PathStrokeType(2));
        g.setColour(pointColour);
        g.fillPath(ellipsePath);
    }
}

void AuxPort::UI::AuxXY::AuxPoint::resized()
{
    if (!drawingBool)
    {
        ellipsePath.addEllipse(0, 0, this->getWidth(), this->getHeight());
        xyCoordinate.x = getParentComponent()->getWidth() / 2;
        xyCoordinate.y = getParentComponent()->getHeight() / 2;
        drawingBool = true;
        origin = xyCoordinate;
        getParentComponent()->resized();
    }
}

void AuxPort::UI::AuxXY::AuxPoint::setColour(const juce::Colour& colour)
{
    pointColour = colour;
}

void AuxPort::UI::AuxXY::AuxPoint::mouseDrag(const juce::MouseEvent& e)
{
    auto deltaX = e.getDistanceFromDragStartX();
    auto deltaY = e.getDistanceFromDragStartY();
    deltaX += origin.x;
    deltaY += origin.y;

    xyCoordinate.x = deltaX;
    xyCoordinate.y = deltaY;


    if (xyCoordinate.x > getParentComponent()->getWidth())
        xyCoordinate.x = getParentComponent()->getWidth() - this->getWidth();
    if (xyCoordinate.y > getParentComponent()->getHeight())
        xyCoordinate.y = getParentComponent()->getHeight() - this->getHeight();
    if (xyCoordinate.x < getParentComponent()->getX())
        xyCoordinate.x = getParentComponent()->getX();
    if (xyCoordinate.y < getParentComponent()->getY())
        xyCoordinate.y = getParentComponent()->getY();

    getParentComponent()->resized();
    getParentComponent()->repaint();

}

void AuxPort::UI::AuxXY::AuxPoint::mouseUp(const juce::MouseEvent& e)
{
    const std::lock_guard<std::mutex> lock(pointMutex);
    origin = xyCoordinate;
    *x = static_cast<float>(xyCoordinate.x) / static_cast<float>(getParentComponent()->getWidth());
    *y = static_cast<float>(xyCoordinate.y) / static_cast<float>(getParentComponent()->getHeight());
    getParentComponent()->repaint();

}

juce::Point<int>* AuxPort::UI::AuxXY::AuxPoint::getCoordinate()
{
    return &xyCoordinate;
}

AuxPort::UI::AuxXY::AuxXY(juce::AudioParameterFloat* x, juce::AudioParameterFloat* y) : auxPoint(x,y)
{
    auxPoint.setColour(juce::Colours::green);
    addAndMakeVisible(auxPoint);
    this->x = x;
    this->y = y;
    bezier.setNumberOfPoints(50);
}

AuxPort::UI::AuxXY::~AuxXY()
{
}

void AuxPort::UI::AuxXY::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGBA(11, 12, 13, 180));
    g.drawLine(this->getWidth() / 2, 0, this->getWidth() / 2, this->getHeight());
    g.drawLine(0, this->getHeight() / 2, this->getWidth(), this->getHeight() / 2);

    bezier.calcPoints({ 0,1 }, { *x,*y }, { 1,0 });
    g.setColour(juce::Colours::black);
    for (uint32_t i = 1; i < 50; i++)
    {
        auto x1 = bezier.getPoint(i - 1)->x * getWidth();
        auto y1 = bezier.getPoint(i - 1)->y * getHeight();
        auto x2 = bezier.getPoint(i)->x * getWidth();
        auto y2 = bezier.getPoint(i)->y * getHeight();
        g.drawLine(x1, y1, x2, y2);
    }

}

void AuxPort::UI::AuxXY::resized()
{
    auto x = this->getWidth() / 10;
    auto y = this->getHeight() / 10;
    auxPoint.setBounds(auxPoint.getCoordinate()->x,auxPoint.getCoordinate()->y,0.5*x,0.5*y);
}
