#include "chorus.h"
#include "delayLine.h"
#include <math.h>
#include <iostream>

#define PI_2 6.28318530717959

Chorus::Chorus(int samplerate) : del1(10*samplerate/1000), del2(10*samplerate/1000), del3(10*samplerate/1000),
  mix1(0.6), mix2(0.6), mix3(0.6),
  del1Rate(0.41), del2Rate(0.59), del3Rate(7.9),
  del1Dist(3.5), del2Dist(3.5), del3Dist(3.5),
  phase1(0), phase2(0), phase3(0), samplerate(samplerate),
  tap1(0), tap2(0), tap3(0) {
  for (int i = 0; i < 101; i++){
    sinus[i] = sin(PI_2/100*i);
    //std::cout << "sin " << i << ": " << sinus[i] << '\n';
  }
  del1.setDistance((int)(del1Dist/1000*samplerate));
  del2.setDistance((int)(del2Dist/1000*samplerate));
  del3.setDistance((int)(del3Dist/1000*samplerate));
  std::cout << "Chorus constructor" << '\n';
}

Chorus::~Chorus(){

}

void Chorus::tick(){
  // TODO: maak hier een functie van die dit doet voor alle phases
  phase1 += del1Rate/samplerate;
  while (phase1 > 1){
    phase1 -= 1;
  }
  sinIndex = floor(phase1*100);
  interp = phase1 * 100 - sinIndex;
  if (phase1 > 100){
    phase1 = 100;
    std::cout << "phase1 error" << '\n';
  }
  del1Dist = 1.84*(sinus[sinIndex]*(1-interp/100) + sinus[sinIndex+1]*interp/100)+3.5;

  phase2 += del2Rate/samplerate;
  while (phase2 > 1){
    phase2 -= 1;
  }
  sinIndex = floor(phase2*100);
  interp = phase2 * 100 - sinIndex;
  if (phase2 > 100){
    phase2 = 100;
    std::cout << "phase2 error" << '\n';
  }
  del2Dist = 1.84*(sinus[sinIndex]*(1-interp/100) + sinus[sinIndex+1]*interp/100)+3.5;

  phase3 += del3Rate/samplerate;
  while (phase3 > 1){
    phase3 -= 1;
  }
  sinIndex = floor(phase3*100);
  interp = phase3 * 100 - sinIndex;
  if (phase3 > 100){
    phase3 = 100;
    std::cout << "phase3 error" << '\n';
  }
  del3Dist = 0.25*(sinus[sinIndex]*(1-interp/100) + sinus[sinIndex+1]*interp/100)+3.5;

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
