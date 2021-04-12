#include <cmath>
#include "tapeShifter.h"


#define MAX_DELAY_SIZE 441000
#define DELAY_TIME_SEC 1.0f

#define PI_2 6.28318530717959
#define PI 3.14159265358979323846264338327950288419716939937510

TapeShifter::TapeShifter(int numSamplesDelay, float rate) : numSamplesDelay(numSamplesDelay), Effect(rate)
{
    del1.setDistance(numSamplesDelay);
    del2.setDistance(numSamplesDelay);
}

TapeShifter::~TapeShifter()
{}

void TapeShifter::write(float inputFromInbuff)
{
  del1.write(inputFromInbuff);
  del2.write(inputFromInbuff);
}

float TapeShifter::read()
{
  outPutSample = ( del1.read() * volumeScaling * getWindowingOutput() ) + ( del2.read() * volumeScaling * getWindowingPhaseShiftedOutput() );

  return outPutSample;
}

float TapeShifter::getWindowingOutput(){
  return cos((saw1.getSample() -0.5) * PI);
}

float TapeShifter::getWindowingPhaseShiftedOutput(){
  return cos((std::fmod((saw1.getSample() + 0.5), 1.0) -0.5) * PI);
}

void TapeShifter::tick()
{
	del1.tick();
  del2.tick();
  delayDistanceCalc();
  saw1.tick();
}

void TapeShifter::delayDistanceCalc()
{
  del1.setDistance(((saw1.getSample() * 100.0) + delTimeScaling) * samplesPerMillisec);
  del2.setDistance(((std::fmod((saw1.getSample() + 0.5), 1.0 ) * 100.0) + delTimeScaling) * samplesPerMillisec);  //second buffer modulation at half a wavelength difference
}

void TapeShifter::changeSawFrequency(float freq_in)
{
  saw1.setFrequency(freq_in);
}
