#include "chorus.h"
#include "delayLine.h"
#include <math.h>
#include <iostream>

#define PI_2 6.28318530717959

typedef unsigned int uint;

Chorus::Chorus(uint rate) : samplerate(rate) {
  std::cout << "chorus constructor check\n";
  for (int i = 0; i < 101; i++){
    sinus[i] = sin(PI_2/100.0*i);
  }
  del1.setDistance((int)(del1Dist/1000.0*samplerate));
  del2.setDistance((int)(del2Dist/1000.0*samplerate));
  del3.setDistance((int)(del3Dist/1000.0*samplerate));
}

Chorus::~Chorus(){

}

void Chorus::phaseIncrease(){
  phase1 += del1Rate/samplerate;
  while (phase1 >= 1.0){
    phase1 -= 1.0;
  }
  phase2 += del2Rate/samplerate;
  while (phase2 >= 1.0){
    phase2 -= 1.0;
  }
  phase3 += del3Rate/samplerate;
  while (phase3 >= 1.0){
    phase3 -= 1.0;
  }
}

void Chorus::sinusCalculation(){
  sinIndex = floor(phase1*100);
  interp = phase1 * 100 - sinIndex;
  sinusValue1 = sinus[sinIndex]*(1-interp/100) + sinus[sinIndex+1]*interp/100;
  
  sinIndex = floor(phase2*100);
  interp = phase2 * 100 - sinIndex;
  sinusValue2 = sinus[sinIndex]*(1-interp/100) + sinus[sinIndex+1]*interp/100;
  
  sinIndex = floor(phase3*100);
  interp = phase3 * 100 - sinIndex;
  sinusValue3 = sinus[sinIndex]*(1-interp/100) + sinus[sinIndex+1]*interp/100;
}

void Chorus::distanceCalculation(){
  del1Dist = del1ModDepth*(sinusValue1)+delAverageDist;
  del2Dist = del2ModDepth*(sinusValue2)+delAverageDist;
  del3Dist = del3ModDepth*(sinusValue3)+delAverageDist;
}

void Chorus::tick(){
  phaseIncrease();
  sinusCalculation();
  distanceCalculation();

  del1.tick();
  del2.tick();
  del3.tick();

  del1.setDistance((int)(del1Dist/1000*samplerate));
  del2.setDistance((int)(del2Dist/1000*samplerate));
  del3.setDistance((int)(del3Dist/1000*samplerate));
}

float Chorus::read(){
  return tap3;
}

void Chorus::write(float val_in){
  del1.write(val_in);
  tap1 = del1.read()*mix1+val_in*(1.0-mix1);
  del2.write(tap1);
  tap2 = del2.read()*mix2+tap1*(1.0-mix2);
  del3.write(tap2);
  tap3 = del3.read()*mix3+tap2*(1.0-mix3);
}
