/*
  ==============================================================================

    AdditiveVoice.cpp
    Created: 30 May 2021 5:05:23pm
    Author:  marks

  ==============================================================================
*/

#include "AdditiveVoice.h"
#include <math.h>

AdditiveVoice::AdditiveVoice()
{
    for (int i = 0; i < 20; i++)
    {
        oddStackPointer[i] = &oddStack[i];
        evenStackPointer[i] = &evenStack[i];
        regAmpSet[(2 * i)] = 1.0 / ((2.0 * i) + 1.0);
        regAmpSet[(2 * i) + 1] = 1.0 / (2.0 * (i + 1.0));
    }
    for (int i = 0; i < 10; i++)
    {
        cluster1StackPointer[i] = &cluster1Stack[i];
        cluster2StackPointer[i] = &cluster2Stack[i];
        cluster3StackPointer[i] = &cluster3Stack[i];
        cluster1AmpSet[i] = 1 / (i + 1.0);
        cluster2AmpSet[i] = 1 / (i + 1.0);
        cluster3AmpSet[i] = 1 / (i + 1.0);
    }
    ampEnvADSR.attack = 0.1;
    ampEnvADSR.decay = 0.1;
    ampEnvADSR.sustain = 0.5;
    ampEnvADSR.release = 0.1;
    setEnvParams();
}

AdditiveVoice::~AdditiveVoice()
{

}

void AdditiveVoice::tick()
{
    for (int i = 0; i < numOddPartials; i++)
    {
        oddStackPointer[i]->tick();
    }
    for (int i = 0; i < numEvenPartials; i++)
    {
        evenStackPointer[i]->tick();
    }
    for (int i = 0; i < numCluster1Partials; i++)
    {
        cluster1StackPointer[i]->tick();
    }
    for (int i = 0; i < numCluster2Partials; i++)
    {
        cluster2StackPointer[i]->tick();
    }
    for (int i = 0; i < numCluster3Partials; i++)
    {
        cluster3StackPointer[i]->tick();
    }
    ampEnvVal = ampEnv.getNextSample();
}

double AdditiveVoice::getVal(SineTable* table)
{
    sample = 0.0;
    double valStack = 0.0;

    for (int i = 0; i < numEvenPartials; i++)
    {
        valStack += table->getVal(evenStackPointer[i]->getVal()) * regAmpSet[2*(i+1)-1];
    }
    sample += valStack * evenAmp;

    valStack = 0.0;
    for (int i = 0; i < numOddPartials; i++)
    {
        valStack += table->getVal(oddStackPointer[i]->getVal()) * regAmpSet[2 * i];
    }
    sample += valStack * oddAmp;

    valStack = 0.0;
    for (int i = 0; i < numCluster1Partials; i++)
    {
        valStack += table->getVal(cluster1StackPointer[i]->getVal()) * cluster1AmpSet[i];
    }
    sample += valStack * cluster1Amp;

    valStack = 0.0;
    for (int i = 0; i < numCluster2Partials; i++)
    {
        valStack += table->getVal(cluster2StackPointer[i]->getVal()) * cluster2AmpSet[i];
    }
    sample += valStack * cluster2Amp;

    valStack = 0.0;
    for (int i = 0; i < numCluster3Partials; i++)
    {
        valStack += table->getVal(cluster3StackPointer[i]->getVal()) * cluster3AmpSet[i];
    }
    sample += valStack * cluster3Amp;

    return sample * amp * ampEnvVal;
}

void AdditiveVoice::setSamplerate(double sr_in)
{
    for (int i = 0; i < 20; i++)
    {
        oddStackPointer[i]->setSamplerate(sr_in);
        evenStackPointer[i]->setSamplerate(sr_in);
    }
    for (int i = 0; i < 10; i++)
    {
        cluster1StackPointer[i]->setSamplerate(sr_in);
        cluster2StackPointer[i]->setSamplerate(sr_in);
        cluster3StackPointer[i]->setSamplerate(sr_in);
    }
    ampEnv.setSampleRate(sr_in);
}

void AdditiveVoice::setFreq(double freq_in)
{
    frequency = freq_in;
    for (int i = 0; i < 20; i++)
    {
        oddStackPointer[i]->setFrequency(frequency * (2.0 * (i + 1.0) - 1.0));
        evenStackPointer[i]->setFrequency(frequency * 2.0 * (i + 1.0));
        if (frequency * (double)i >= 0.25 * samplerate)
        {
            regAmpSet[(2 * i)] = 0.0;
            regAmpSet[(2 * i) + 1] = 0.0;
        }
        else
        {
            regAmpSet[(2 * i)] = 1.0 / ((2.0 * i) + 1.0);
            regAmpSet[(2 * i) + 1] = 1.0 / (2.0 * (i + 1.0));
        }
    }
    setCluster1Freq();
    setCluster2Freq();
    setCluster3Freq();
}

void AdditiveVoice::prepareToPlay(double sr_in)
{
    setSamplerate(sr_in);
}

void AdditiveVoice::setNoteOn(int midiNoteNr)
{
    setFreq(440.0 * pow(2.0, (midiNoteNr - 69.0) / 12.0));
    ampEnv.noteOn();
}

void AdditiveVoice::setNoteOff()
{
    ampEnv.noteOff();
}

bool AdditiveVoice::isActive()
{
    return ampEnv.isActive();
}

void AdditiveVoice::resetEnv()
{
    ampEnv.reset();
}

void AdditiveVoice::setCluster1Freq()
{
    for (int i = 9; i >= 0; i--)
    {
        double clusterMult = cluster1FrequencyMult * pow(i + 1, cluster1Ratio);
        double clusterFreq = frequency * clusterMult;
        cluster1StackPointer[i]->setFrequency(clusterFreq);
        if (clusterFreq >= samplerate * 0.5) {
            maxPartialsCluster1 = i + 1;
        }
        cluster1AmpSet[i] = 1.0 / clusterMult;
    }
}

void AdditiveVoice::setCluster2Freq()
{
    for (int i = 9; i >= 0; i--)
    {
        double clusterMult = cluster2FrequencyMult * pow(i + 1, cluster2Ratio);
        double clusterFreq = frequency * clusterMult;
        cluster2StackPointer[i]->setFrequency(clusterFreq);
        if (clusterFreq >= samplerate * 0.5) {
            maxPartialsCluster2 = i + 1;
        }
        cluster2AmpSet[i] = 1.0 / clusterMult;
    }
}

void AdditiveVoice::setCluster3Freq()
{
    for (int i = 9; i >= 0; i--)
    {
        double clusterMult = cluster3FrequencyMult * pow(i + 1, cluster3Ratio);
        double clusterFreq = frequency * clusterMult;
        cluster3StackPointer[i]->setFrequency(clusterFreq);
        if (clusterFreq >= samplerate * 0.5) {
            maxPartialsCluster3 = i + 1;
        }
        cluster3AmpSet[i] = 1.0 / clusterMult;
    }
}

void AdditiveVoice::setCluster1Ratio(float clrat_in)
{
    cluster1Ratio = clrat_in;
    setCluster1Freq();
}

float AdditiveVoice::getCluster1Ratio()
{
    return cluster1Ratio;
}

void AdditiveVoice::setCluster1FreqMult(float clfreq_in)
{
    cluster1FrequencyMult = clfreq_in;
    setCluster1Freq();
}

float AdditiveVoice::getCluster1FreqMult()
{
    return cluster1FrequencyMult;
}

void AdditiveVoice::setCluster2Ratio(float clrat_in)
{
    cluster2Ratio = clrat_in;
    setCluster2Freq();
}

float AdditiveVoice::getCluster2Ratio()
{
    return cluster2Ratio;
}

void AdditiveVoice::setCluster2FreqMult(float clfreq_in)
{
    cluster2FrequencyMult = clfreq_in;
    setCluster2Freq();
}

float AdditiveVoice::getCluster2FreqMult()
{
    return cluster2FrequencyMult;
}

void AdditiveVoice::setCluster3Ratio(float clrat_in)
{
    cluster3Ratio = clrat_in;
    setCluster3Freq();
}

float AdditiveVoice::getCluster3Ratio()
{
    return cluster3Ratio;
}

void AdditiveVoice::setCluster3FreqMult(float clfreq_in)
{
    cluster3FrequencyMult = clfreq_in;
    setCluster3Freq();
}

float AdditiveVoice::getCluster3FreqMult()
{
    return cluster3FrequencyMult;
}

void AdditiveVoice::setEnvParams()
{
    ampEnv.setParameters(ampEnvADSR);
}

void AdditiveVoice::setAmp(double amp_in)
{
    amp = amp_in;
}

void AdditiveVoice::setAttack(float attack)
{
    ampEnvADSR.attack = attack;
    setEnvParams();
}
void AdditiveVoice::setDecay(float decay)
{
    ampEnvADSR.decay = decay;
    setEnvParams();
}
void AdditiveVoice::setSustain(float sustain)
{
    ampEnvADSR.sustain = sustain;
    setEnvParams();
}
void AdditiveVoice::setRelease(float release)
{
    ampEnvADSR.release = release;
    setEnvParams();
}

void AdditiveVoice::setEvenAmp(double amp_in)
{
    evenAmp = amp_in;
}
void AdditiveVoice::setEvenPartials(int num_in)
{
    numEvenPartials = num_in;
}
void AdditiveVoice::setOddAmp(double amp_in)
{
    oddAmp = amp_in;
}
void AdditiveVoice::setOddPartials(int num_in)
{
    numOddPartials = num_in;
}

void AdditiveVoice::setCluster1Amp(double amp_in)
{
    cluster1Amp = amp_in;
}
void AdditiveVoice::setCluster1Partials(int num_in)
{
    numCluster1Partials = num_in;
}

void AdditiveVoice::setCluster2Amp(double amp_in)
{
    cluster2Amp = amp_in;
}
void AdditiveVoice::setCluster2Partials(int num_in)
{
    numCluster2Partials = num_in;
}

void AdditiveVoice::setCluster3Amp(double amp_in)
{
    cluster3Amp = amp_in;
}
void AdditiveVoice::setCluster3Partials(int num_in)
{
    numCluster3Partials = num_in;
}