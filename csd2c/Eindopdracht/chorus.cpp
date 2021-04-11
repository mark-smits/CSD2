#include "chorus.h"
#include "delayLine.h"
#include <math.h>
#include <iostream>

#define PI_2 6.28318530717959

Chorus::Chorus(int rate) : samplerate(rate) {
  for (int i = 0; i < 101; i++){
    sinus[i] = sin(PI_2/100*i);
  }
  del1.setDistance((int)(del1Dist/1000*samplerate));
  del2.setDistance((int)(del2Dist/1000*samplerate));
  del3.setDistance((int)(del3Dist/1000*samplerate));
}

Chorus::~Chorus(){

}

void Chorus::phaseIncrease(){
  phase1 += del1Rate/samplerate;
  while (phase1 > 1){
    phase1 -= 1;
  }
  phase2 += del2Rate/samplerate;
  while (phase2 > 1){
    phase2 -= 1;
  }
  phase3 += del3Rate/samplerate;
  while (phase3 > 1){
    phase3 -= 1;
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
  del1Dist = 1.84*(sinusValue1)+3.5;
  del2Dist = 1.84*(sinusValue2)+3.5;
  del3Dist = 0.25*(sinusValue3)+3.5;
}

void Chorus::tick(){
  // TODO: maak hier een functie van die dit doet voor alle phases
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
  tap1 = del1.read()*mix1+val_in*(1-mix1);
  del2.write(tap1);
  tap2 = del2.read()*mix2+tap1*(1-mix2);
  del3.write(tap2);
  tap3 = del3.read()*mix3+tap2*(1-mix3);
}
