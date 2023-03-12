/*
*			AuxBezier : Quadratic Bezier Curve Implementation for JUCE
            "Shape it, play with it" - inpinseptipin
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

#include "AuxBezier.h"

AuxPort::Bezier::Bezier(uint32_t points)
{
    bezierVector.resize(points);
}

void AuxPort::Bezier::setNumberOfPoints(const uint32_t& points)
{
    bezierVector.resize(points);
}

void AuxPort::Bezier::calcPoints(const juce::Point<float>& p1, const juce::Point<float>& p2, const juce::Point<float>& p3)
{
    for (uint32_t i = 0; i < bezierVector.size(); i++)
    {
        float ii = static_cast<float>(i / static_cast<float>(bezierVector.size()));
        bezierVector[i].x = powf(ii, 2) * p1.x + (2 * ii * (1 - ii)) * p2.x + powf(1 - ii, 2) * p3.x;
        bezierVector[i].y = powf(ii, 2) * p1.y + (2 * ii * (1 - ii)) * p2.y + powf(1 - ii, 2) * p3.y;
    }
}

juce::Point<float>* AuxPort::Bezier::getPoint(const uint32_t& index)
{
    return &bezierVector[index];
}
