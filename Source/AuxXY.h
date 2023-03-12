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
#include "AuxBezier.h"

namespace AuxPort
{
    namespace UI
    {

        class AuxXY : public juce::Component
        {
        public:
            AuxXY(juce::AudioParameterFloat* x, juce::AudioParameterFloat* y);
            ~AuxXY() override;

            void paint(juce::Graphics&) override;
            void resized() override;


        private:
            class AuxPoint : public juce::Component
            {
            public:
                AuxPoint(juce::AudioParameterFloat* x,juce::AudioParameterFloat* y);
                ~AuxPoint() override;
                void paint(juce::Graphics&) override;
                void resized() override;
                void setColour(const juce::Colour& colour);
                void mouseDrag(const juce::MouseEvent& e) override;
                void mouseUp(const juce::MouseEvent& e) override;
                juce::Point<int>* getCoordinate();
            private:
                juce::Point<int> xyCoordinate;
                juce::Point<int> origin;
                juce::AudioParameterFloat* x;
                juce::AudioParameterFloat* y;
                juce::Colour pointColour;
                juce::Path ellipsePath;
                std::mutex pointMutex;
                bool drawingBool;
                JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AuxPoint)

            };
            AuxPoint auxPoint;
            AuxPort::Bezier bezier;
            juce::AudioParameterFloat* x;
            juce::AudioParameterFloat* y;
            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AuxXY)
        };
    }
}


