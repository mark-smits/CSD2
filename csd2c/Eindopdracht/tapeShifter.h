#include "delayLine.h"
#include "saw.h"
#include "math.h"
#include "effect.h"

/*
* as a prerequisite of the methodology a couple things need to be defined
* We need PI as a part of the windowing function - using a cosine function
* Is it a part of <cmath> ? probably, but like this we know for sure.
*/

#define MAX_DELAY_SIZE 441000
#define DELAY_TIME_SEC 1.0f

#define PI_2 6.28318530717959
#define PI 3.14159265358979323846264338327950288419716939937510

#pragma once

/*
*   A pitchshifter that alters the pitch using a modulating delay
*   the delay is modulated by a saw wave
*   when the saw completes it wave it jumps back to zero
*   which results in a click, so for that we need to apply some windowing
*/

class TapeShifter : public Effect
{
public:
  TapeShifter(int numSamplesDelay, float rate);
  ~TapeShifter();

  void initializeShifter();
  void write(float inputFromInbuff);
  float read();
  void changeSawFrequency(float freq_in);
  void tick();

protected:
  float inputFromInbuff, sawFrequency;
  float outPutSample;
  int numSamplesDelay;
  
private:
  DelayLine del1{numSamplesDelay*2}, del2{numSamplesDelay*2};
  Saw saw1{1.0, getSamplerate()};
  float samplesPerMillisec = getSamplerate()/1000.0;
  float delTimeScaling = 5.0;
  float volumeScaling = 0.5;
  float getWindowingOutput();
  float getWindowingPhaseShiftedOutput();
  void delayDistanceCalc();
};
