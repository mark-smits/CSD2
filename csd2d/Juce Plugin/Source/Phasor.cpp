/*
  ==============================================================================

    Phasor.cpp
    Created: 30 May 2021 4:59:32pm
    Author:  marks

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Phasor.h"

Phasor::Phasor() 
{
    this->samplerate = 44100;
}

Phasor::Phasor(double samplerate) : samplerate(samplerate)
{
    phase_increment = frequency / samplerate;
}

Phasor::~Phasor()
{

}

double Phasor::getVal()
{
    return phase;
}

void Phasor::setFrequency(double freq)
{
    frequency = freq;
    phase_increment = frequency / samplerate;
}

void Phasor::setSamplerate(double sr_in) {
    samplerate = sr_in;
}

void Phasor::tick()
{
    phase += phase_increment;
    while (phase > 1.0)
    {
        phase -= 1.0;
    }
}