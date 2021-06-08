/*
  ==============================================================================

    Phasor.h
    Created: 30 May 2021 4:59:32pm
    Author:  marks

  ==============================================================================
*/

#pragma once
class Phasor
{

public:

    Phasor();
    Phasor(double samplerate);
    ~Phasor();
    double getVal();
    void setFrequency(double freq);
    void setSamplerate(double sr_in);
    void tick();

private:

    double phase = 0.0;
    double frequency = 200.0;
    double samplerate = 44100.0;
    double phase_increment = 0.0;
};