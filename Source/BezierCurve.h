#ifndef AUXPORT_BEZIER_H
#define AUXPORT_BEZIER_H

/*
  ==============================================================================

    BezierCurve.h
    Created: 28 Feb 2023 5:49:28pm
    Author:  satya

  ==============================================================================
*/

#include <vector>
#include "JuceHeader.h"
namespace AuxPort
{
    class Bezier
    {
    public:
        Bezier() = default;
        ~Bezier() = default;
        Bezier(const Bezier& bezier) = default;
        void setNumberOfPoints(const uint32_t& points)
        {
            pointVector.resize(points);
        }

        void setNormalizationFactors(const uint32_t& width, const uint32_t& height)
        {
            norm.x = width;
            norm.y = height;
        }
        void calcPoints(const juce::Point<float>& p1, const juce::Point<float>& p2, const juce::Point<float>& p3)
        {
            this->p1.x = static_cast<float>((p1.x / norm.x));
            this->p1.y = static_cast<float>((p1.y / norm.y));

            this->p2.x = p2.x / norm.x;
            this->p2.y = p2.y / norm.y;

            this->p3.x = p3.x / norm.x;
            this->p3.y = p3.y / norm.y;

            for (uint32_t i = 0; i < pointVector.size(); i++)
            {
                float ii = static_cast<float>(i / static_cast<float>(pointVector.size()));
                pointVector[i].x = p3.x * powf(ii,2) + p2.x * 2 * ii * (1-ii) + p1.x * powf(1-ii,2);
                pointVector[i].y = p3.y * powf(ii, 2) + p2.y * 2 * ii * (1 - ii) + p1.y * powf(1 - i, 2);
            }

        }

        juce::Point<float>* getPoint(const uint32_t& index)
        {
            return &pointVector[index];
        }

    private:
        std::vector<juce::Point<float>> pointVector;
        juce::Point<float> p1;
        juce::Point<float> p2;
        juce::Point<float> p3;

        juce::Point<float> norm = { 0,0 };
    };

}



#endif


