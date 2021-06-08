/*
  ==============================================================================

    SineTable.h
    Created: 30 May 2021 4:59:02pm
    Author:  marks

  ==============================================================================
*/

#pragma once
class SineTable {

public:

    SineTable();
    ~SineTable();

    double getVal(double phase);

private:

    void allocateTable();
    void releaseTable();
    void interpolate(double phase);

    double* sineTable;
    int numSineSamples = 50000;

};