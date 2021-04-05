#include <cmath>
#include "tapeShifter.h"


#define MAX_DELAY_SIZE 441000
#define DELAY_TIME_SEC 1.0f

#define PI_2 6.28318530717959
#define PI 3.14159265358979323846264338327950288419716939937510

TapeShifter::TapeShifter(int numSamplesDelay) : del1(numSamplesDelay * 2), del2(numSamplesDelay * 2), saw1(1, samplerate)
{
  //put this before the buffer loop in the main.cpp
    del1.setDistance(numSamplesDelay);
    del2.setDistance(numSamplesDelay);
}

TapeShifter::~TapeShifter()
{}

void TapeShifter::signalToBeShifted(double inputFromInbuff)
{
//Put this in the buffer loop where inputFromIbuff = inbuf[i]
  del1.write(inputFromInbuff);
  del2.write(inputFromInbuff);
}

double TapeShifter::pitchshiftedSignal()
{
  /*
  * Put this in the buffer loop
  * below is a windowing calculation: So you don't have to read it I will describe it here
  * Output = X1 * (SawWave_Output * cos)
  * Output = X2 * (SawWave_Output -- Phaseshifted -- * cos)
  */

    outPutSample = ((del1.read() * 0.5) * cos((saw1.getSample() -0.5) * PI)) + ((del2.read() * 0.5) * cos((std::fmod((saw1.getSample() + 0.5), 1.0) -0.5) * PI));
    

    return outPutSample;
}

void TapeShifter::tick()
{
	del1.tick();
    del2.tick();
    del1.setDistance(((saw1.getSample() * 100.0) + 5.0) * 44.1);  //Delay time modulation
    del2.setDistance(((std::fmod((saw1.getSample() + 0.5), 1.0 ) * 100.0) + 5.0) * 44.1);  //second buffer modulation at half a wavelength difference
    saw1.tick();
}

void TapeShifter::changeSawFrequency()
{
  saw1.setFrequency();
  saw1.getFrequency();
}
