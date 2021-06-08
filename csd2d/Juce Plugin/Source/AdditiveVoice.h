/*
  ==============================================================================

    AdditiveVoice.h
    Created: 30 May 2021 5:05:23pm
    Author:  marks

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SineTable.h"
#include "Phasor.h"

class AdditiveVoice {

public:

    AdditiveVoice();
    ~AdditiveVoice();

    void tick();
    double getVal(SineTable* table);
    void setSamplerate(double sr_in);
    void setFreq(double freq_in);
    void prepareToPlay(double sr_in);
    void setNoteOn(int midiNoteNr);
    void setNoteOff();
    bool isActive();
    void resetEnv();

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

    void setCluster1Ratio(float clrat_in);
    float getCluster1Ratio();
    void setCluster1FreqMult(float clfreq_in);
    float getCluster1FreqMult(); 

    void setCluster2Amp(double amp_in);
    void setCluster2Partials(int num_in);

    void setCluster2Ratio(float clrat_in);
    float getCluster2Ratio();
    void setCluster2FreqMult(float clfreq_in);
    float getCluster2FreqMult(); 

    void setCluster3Amp(double amp_in);
    void setCluster3Partials(int num_in);

    void setCluster3Ratio(float clrat_in);
    float getCluster3Ratio();
    void setCluster3FreqMult(float clfreq_in);
    float getCluster3FreqMult();

private:

    void setCluster1Freq();
    void setCluster2Freq();
    void setCluster3Freq();
    void setEnvParams();

    double frequency = 200.0;
    double amp = 1.0;
    double samplerate = 48000.0;
    double sample = 0.0;

    int numEvenPartials = 20;
    int numOddPartials = 20;
    int numCluster1Partials = 10;
    int numCluster2Partials = 10;
    int numCluster3Partials = 10;

    double evenAmp = 1.0;
    double oddAmp = 1.0;
    double cluster1Amp = 0.0;
    double cluster2Amp = 0.0;
    double cluster3Amp = 0.0;

    double regAmpSet[40];
    double cluster1AmpSet[10];
    double cluster2AmpSet[10];
    double cluster3AmpSet[10];
    
    float cluster1FrequencyMult = 1;
    float cluster2FrequencyMult = 1;
    float cluster3FrequencyMult = 1;
    float cluster1Ratio = 1;
    float cluster2Ratio = 1;
    float cluster3Ratio = 1;
    
    int maxPartialsCluster1 = 10;
    int maxPartialsCluster2 = 10;
    int maxPartialsCluster3 = 10;

    juce::ADSR ampEnv;
    juce::ADSR::Parameters ampEnvADSR;
    float ampEnvVal = 0.0;

    Phasor evenStack[20];
    Phasor oddStack[20];
    Phasor cluster1Stack[10];
    Phasor cluster2Stack[10];
    Phasor cluster3Stack[10];
    Phasor *evenStackPointer[20];
    Phasor *oddStackPointer[20];
    Phasor *cluster1StackPointer[10];
    Phasor *cluster2StackPointer[10];
    Phasor *cluster3StackPointer[10];

};