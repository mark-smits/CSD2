/*
  ==============================================================================

    SineTable.cpp
    Created: 30 May 2021 4:59:02pm
    Author:  marks

  ==============================================================================
*/

#include <iostream>
#include <math.h>
#include "SineTable.h"
#include <JuceHeader.h>
#include <cstdlib>

SineTable::SineTable()
{
    allocateTable();
}

SineTable::~SineTable()
{
    releaseTable();
}

void SineTable::allocateTable()
{
    sineTable = (double*)malloc(numSineSamples * sizeof(double));
    memset(sineTable, 0, numSineSamples * sizeof(double));
    for (int i = 0; i < numSineSamples; i++)
    {
        sineTable[i] = sin((double)i * 6.283185307179586476925286766559 / ((double)numSineSamples));
    }
}

void SineTable::releaseTable()
{
    free(sineTable);
}

double SineTable::getVal(double phase)
{
    int sinIndex = (int)(floor(phase*numSineSamples));
    return sineTable[sinIndex];
}

void SineTable::interpolate(double phase)
{

}
