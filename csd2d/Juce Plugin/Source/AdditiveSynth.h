/*
  ==============================================================================

    AdditiveSynth.h
    Created: 30 May 2021 5:06:02pm
    Author:  marks

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <map>
#include "AdditiveVoice.h"
#include "SineTable.h"

class AdditiveSynth
{

public:

    AdditiveSynth();
    ~AdditiveSynth();
    void receiveNoteOn(int note_nr);
    void receiveNoteOff(int note_nr);
    void tick();
    double getVal();
    void killAll();
    void prepareToPlay(double sr_in);
    void setSamplerate(double sr_in);
    void setAmp(double amp_in);

    void setAttack(float attack);
    void setDecay(float decay);
    void setSustain(float sustain);
    void setRelease(float release);

    void setEvenAmp(double amp_in);
    void setEvenPartials(int num_in);
    void setOddAmp(double amp_in);
    void setOddPartials(int num_in);

    void setCluster1Amp(double amp_in);
    void setCluster1Partials(int num_in);
    void setCluster1Ratio(float rat_in);
    void setCluster1FreqMult(float freq_in);

    void setCluster2Amp(double amp_in);
    void setCluster2Partials(int num_in);
    void setCluster2Ratio(float rat_in);
    void setCluster2FreqMult(float freq_in);

    void setCluster3Amp(double amp_in);
    void setCluster3Partials(int num_in);
    void setCluster3Ratio(float rat_in);
    void setCluster3FreqMult(float freq_in);

private:

    void checkEnvelopeStatePerVoice();

    std::map<int, int> voiceHandler;
    std::map<int, int>::iterator voiceHandlerIterator;
    int numVoices = 16;

    AdditiveVoice *voiceStack = new AdditiveVoice[numVoices];
    SineTable sinus;
};