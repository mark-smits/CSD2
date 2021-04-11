#include "reverb.h"
#include "allPassFilter.h"
#include "delayLine.h"
#include "bqFilter.h"
#include <iostream>
#include <cstring>
#include <math.h>

typedef unsigned int uint;

Reverb::Reverb(uint rate) : samplerate(rate) {
    del.setDistance(samplerate*100.0/1000.0);
    std::cout << "Reverb constructor" << '\n';
    setdw(drywet);
    lpf.setLPF(3000.0,0.707);
    hpf.setHPF(100.0,0.5);
    apf1.setLPF(4814.0,0.7);
    apf2.setLPF(6065.0,0.7);
    apf3.setLPF(3178.0,0.7);
    apf4.setLPF(3789.0,0.7);
    apf5.setLPF(2313.0,0.7);
    apf6.setLPF(2108.0,0.7);
    //this->samplerate = samplerate;
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
  chor.write(val_in + feedback*hpf.read());
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
  hpf.write(tap6);
  return ( 0.4*(tap1+tap2+tap3+tap4) + 0.3*(tap5+tap6) )*wlvl + val_in*dlvl;
}

void Reverb::setdw(float val_in){
  drywet = val_in;
  if (drywet > 1.0)
  {
    drywet = 1.0;
  }
  else if (drywet < 0.0)
  {
    drywet = 0.0;
  }
  dlvl = pow((1.0-drywet), 0.65);
  std::cout << "dlvl: " << dlvl << '\n';
  wlvl = pow((drywet), 0.65);
  std::cout << "wlvl: " << wlvl << '\n';
}

void Reverb::setTone(float val_in){
  if (val_in > 10.0)
  {
    val_in = 10.0;
  }
  else if (val_in < 0.0)
  {
    val_in = 0.0;
  }
  lpf.setLPF(3000.0 * pow( 1.5, (val_in-5.0) * 0.8 ) , 0.707);
}

void Reverb::setSize(float val_in){
  if (val_in > 10.0)
  {
    val_in = 10.0;
  }
  else if (val_in < 0.0)
  {
    val_in = 0.0;
  }
  apf1.setDelTime(samplerate*4.1/1000.0 * ( 1 + (val_in-5.0)*0.04 ) );
  apf2.setDelTime(samplerate*8.0/1000.0 * ( 1 + (val_in-5.0)*0.04 ) );
  apf3.setDelTime(samplerate*11.7/1000.0 * ( 1 + (val_in-5.0)*0.04 ) );
  apf4.setDelTime(samplerate*15.7/1000.0 * ( 1 + (val_in-5.0)*0.04 ) );
  apf5.setDelTime(samplerate*61.3/1000.0 * ( 1 + (val_in-5.0)*0.04 ) );
  apf6.setDelTime(samplerate*88.9/1000.0 * ( 1 + (val_in-5.0)*0.04 ) );
}
