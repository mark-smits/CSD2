/*
  ==============================================================================

    AdditiveSynth.cpp
    Created: 30 May 2021 5:06:02pm
    Author:  marks

  ==============================================================================
*/

#include "AdditiveSynth.h"
#include <JuceHeader.h>

AdditiveSynth::AdditiveSynth()
{
    for (int i = 0; i < numVoices; i++)
    {
        voiceHandler.insert(std::pair<int, int>(i, -2));
    }
}

AdditiveSynth::~AdditiveSynth()
{
    delete[] voiceStack;
}

void AdditiveSynth::checkEnvelopeStatePerVoice()
{
    // roep hier alle envelopestates terug voor elke voice voor de note on receive message
    voiceHandlerIterator = voiceHandler.begin();
    while (voiceHandlerIterator != voiceHandler.end())
    {
        if (!voiceStack[voiceHandlerIterator->first].isActive())
        {
            voiceHandlerIterator->second = -2;
        }
        voiceHandlerIterator++;
    }
}

void AdditiveSynth::receiveNoteOn(int note_nr) 
{
    int voiceToTrigger;
    checkEnvelopeStatePerVoice();
    if (note_nr < 0)
    {
        note_nr = 0;
    }
    voiceHandlerIterator = voiceHandler.begin();
    while (voiceHandlerIterator != voiceHandler.end())
    {
        if (voiceHandlerIterator->second == -2)
        {
            // vrije voice gevonden
            voiceToTrigger = voiceHandlerIterator->first;
            voiceHandlerIterator->second = note_nr;
            break;
        }
        voiceHandlerIterator++;
    }
    if (voiceHandlerIterator == voiceHandler.end())
    {
        // geen vrije voice gevonden, ga zoeken naar een voice met envlope in release stage
        voiceHandlerIterator = voiceHandler.begin();
        while (voiceHandlerIterator != voiceHandler.end())
        {
            if (voiceHandlerIterator->second == -1)
            {
                voiceToTrigger = voiceHandlerIterator->first;
                voiceHandlerIterator->second = note_nr;
                break;
            }
            voiceHandlerIterator++;
        }
        if (voiceHandlerIterator == voiceHandler.end())
        {
            // geen voice in release gevonden
            voiceToTrigger = 0;
        }
    }
    // trigger de voice met voiceToTrigger
    voiceStack[voiceToTrigger].setNoteOn(note_nr);
}

void AdditiveSynth::receiveNoteOff(int note_nr)
{
    int voiceToRelease;
    if (note_nr < 0)
    {
        note_nr = 0;
    }
    voiceHandlerIterator = voiceHandler.begin();
    while (voiceHandlerIterator != voiceHandler.end())
    {
        if (voiceHandlerIterator->second == note_nr)
        {
            voiceHandlerIterator->second = -1;
            voiceToRelease = voiceHandlerIterator->first;
            break;
        }
        voiceHandlerIterator++;
    }
    if (voiceHandlerIterator == voiceHandler.end())
    {
        DBG("no active voice found for note nr.: " << note_nr);
    }
    else
    {
        // release de voice met voiceToRelease
        voiceStack[voiceToRelease].setNoteOff();
    }
}

void AdditiveSynth::tick()
{
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].tick();
    }
}

double AdditiveSynth::getVal()
{
    double sample = 0.0;
    for (int i = 0; i < numVoices; i++)
    {
        sample += voiceStack[i].getVal(&sinus);
    }
    return sample;
}

void AdditiveSynth::killAll()
{
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].resetEnv();
    }
}

void AdditiveSynth::prepareToPlay(double sr_in)
{
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].prepareToPlay(sr_in);
    }
}

void AdditiveSynth::setSamplerate(double sr_in)
{
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].prepareToPlay(sr_in);
    }
}

void AdditiveSynth::setAmp(double amp_in)
{
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setAmp(amp_in);
    }
}

void AdditiveSynth::setAttack(float attack) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setAttack(attack);
    }
}

void AdditiveSynth::setDecay(float decay) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setDecay(decay);
    }
}

void AdditiveSynth::setSustain(float sustain) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setSustain(sustain);
    }
}

void AdditiveSynth::setRelease(float release) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setRelease(release);
    }
}


void AdditiveSynth::setEvenAmp(double amp_in) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setEvenAmp(amp_in);
    }
}

void AdditiveSynth::setEvenPartials(int num_in) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setEvenPartials(num_in);
    }
}

void AdditiveSynth::setOddAmp(double amp_in) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setOddAmp(amp_in);
    }
}

void AdditiveSynth::setOddPartials(int num_in) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setOddPartials(num_in);
    }
}


void AdditiveSynth::setCluster1Amp(double amp_in) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setCluster1Amp(amp_in);
    }
}

void AdditiveSynth::setCluster1Partials(int num_in) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setCluster1Partials(num_in);
    }
}

void AdditiveSynth::setCluster1Ratio(float rat_in) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setCluster1Ratio(rat_in);
    }
}

void AdditiveSynth::setCluster1FreqMult(float freq_in) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setCluster1FreqMult(freq_in);
    }
}


void AdditiveSynth::setCluster2Amp(double amp_in) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setCluster2Amp(amp_in);
    }
}

void AdditiveSynth::setCluster2Partials(int num_in) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setCluster2Partials(num_in);
    }
}

void AdditiveSynth::setCluster2Ratio(float rat_in) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setCluster2Ratio(rat_in);
    }
}

void AdditiveSynth::setCluster2FreqMult(float freq_in) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setCluster2FreqMult(freq_in);
    }
}


void AdditiveSynth::setCluster3Amp(double amp_in) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setCluster3Amp(amp_in);
    }
}

void AdditiveSynth::setCluster3Partials(int num_in) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setCluster3Partials(num_in);
    }
}

void AdditiveSynth::setCluster3Ratio(float rat_in) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setCluster3Ratio(rat_in);
    }
}

void AdditiveSynth::setCluster3FreqMult(float freq_in) {
    for (int i = 0; i < numVoices; i++)
    {
        voiceStack[i].setCluster3FreqMult(freq_in);
    }
}