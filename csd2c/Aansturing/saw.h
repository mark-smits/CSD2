//A wave to modulate the delay time
//To start I am going to test it with a Saw wave. AFterwards I will
//use a unipolar sawtoothwave
// Duplicate the delay heads and add windowing -- final step

#ifndef _SAW_H_
#define _SAW_H_

#include <iostream>


//Class
class Saw {
public:
  Saw(double frequency, double samplerate);
  ~Saw();

//methods:

//Frequency (Amplitude must be 100% at all times) Will add scaling after calculation
void setFrequency();
double getFrequency();
//getsample and tick
double getSample();
void tick();

//protected variables
protected:
double samplerate = 44100;
double frequency;
double phase;
double amplitude = 1.0;
double sampletje;

};

#endif
