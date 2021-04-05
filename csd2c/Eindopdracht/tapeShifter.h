#include "delayLine.h"
#include "saw.h"
#include "math.h"

/*
* as a prerequisite of the methodology a couple things need to be defined
* We need PI as a part of the windowing function - using a cosine function
* Is it a part of <cmath> ? probably, but like this we know for sure.
* As a part of Ciska Vrezenga's circbuffer which I stole
* the max delay size and delay time sec are pre-defined. we probably won't
* be needing a max size of 10 seconds, but I see no reason currently to
* lower that.
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

class TapeShifter
{
public:
  TapeShifter(int numSamplesDelay);
  ~TapeShifter();


void initializeShifter();

  //input
void signalToBeShifted(double inputFromInbuff);

  //output
double pitchshiftedSignal();

  //pitchshift amount
void changeSawFrequency();

  //tick function
void tick();

protected:
  double inputFromInbuff, sawFrequency;
  double outPutSample;

  double samplerate = 44100;
  float delayTimeSec = DELAY_TIME_SEC;
  int numSamplesDelay = samplerate * delayTimeSec;
private:
DelayLine del1, del2;
Saw saw1;

};
