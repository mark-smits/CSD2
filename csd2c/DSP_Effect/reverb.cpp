#include "reverb.h"
#include "allPassFilter.h"
#include "delayLine.h"
#include "bqFilter.h"
#include <iostream>
#include <cstring>
#include <math.h>

Reverb::Reverb(uint samplerate) : feedback(0.99), drywet(0.5),
  apf1(samplerate*4.1/1000.0,0.36,samplerate), apf2(samplerate*8.0/1000.0,0.2,samplerate),
  apf3(samplerate*11.7/1000.0,0.41,samplerate), apf4(samplerate*15.7/1000.0,0.13,samplerate),
  apf5(samplerate*61.3/1000.0,0.27,samplerate), apf6(samplerate*88.9/1000.0,0.58,samplerate),
  del(samplerate*200.0/1000.0), tapc(0), tap1(0), tap2(0), tap3(0), tap4(0), tapd(0), tap5(0), tap6(0),
  lpf(0.030008, 0.060016, 0.030008, -1.43764, 0.573078, samplerate), chor(samplerate) {
    del.setDistance(samplerate*100.0/1000.0);
    std::cout << "Reverb constructor" << '\n';
    setdw(drywet);
}

Reverb::~Reverb(){

}

void Reverb::tick(){
  apf1.tick();
  apf2.tick();
  apf3.tick();
  apf4.tick();
  apf5.tick();
  apf6.tick();
  del.tick();
  chor.tick();
}

void Reverb::write(float val_in){
  chor.write(val_in + feedback*tap6);
  apf1.write(tapc);
  apf2.write(tap1);
  apf3.write(tap2);
  apf4.write(tap3);
  del.write(tap4);
  apf5.write(tapd);
  apf6.write(tap5);
}

float Reverb::read(float val_in){
  tapc = chor.read();
  tap1 = apf1.read(tapc);
  tap2 = apf2.read(tap1);
  tap3 = apf3.read(tap2);
  tap4 = apf4.read(tap3);
  tapd = del.read();
  lpf.write(tapd);
  tapf = lpf.read();
  tap5 = apf5.read(tapf);
  tap6 = apf6.read(tap5);
  return ( 0.4*(tap1+tap2+tap3+tap4) + 0.3*(tap5+tap6) )*wlvl + val_in*dlvl;
}

void Reverb::setdw(float val_in){
  drywet = val_in;
  dlvl = pow((1.0-drywet), 0.25);
  std::cout << "dlvl: " << dlvl << '\n';
  wlvl = pow((drywet), 0.25);
  std::cout << "wlvl: " << wlvl << '\n';
}
