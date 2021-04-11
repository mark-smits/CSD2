#include "reverb.h"
#include "allPassFilter.h"
#include "delayLine.h"
#include "bqFilter.h"
#include <iostream>
#include <cstring>
#include <math.h>

typedef unsigned int uint;

Reverb::Reverb(uint rate) : Effect(rate) {
    del.setDistance(samplerateMillisec*100.0);
    setdw(drywet);
    lpf.setLPF(lpf_freq, resonance);
    hpf.setHPF(hpf_freq, resonance);
    apf1.setLPF(apf1_freq, resonance);
    apf2.setLPF(apf2_freq, resonance);
    apf3.setLPF(apf3_freq, resonance);
    apf4.setLPF(apf4_freq, resonance);
    apf5.setLPF(apf5_freq, resonance);
    apf6.setLPF(apf6_freq, resonance);
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
  chor.write(val_in + feedback*tap6*0.8);
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
  wet_output = early_reflections_amp*(tap1+tap2+tap3+tap4) + late_reflections_amp*(tap5+tap6);
  return wet_output*wlvl + val_in*dlvl;
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
  dlvl = pow((1.0-drywet), drywet_exponent);
  std::cout << "dlvl: " << dlvl << '\n';
  wlvl = pow((drywet), drywet_exponent);
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
  lpf.setLPF(lpf_freq * pow( 1.5, (val_in-5.0) * 0.8 ) , resonance);
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
  delay_mult = 1.0 + (val_in-5.0)*0.1;
  apf1.setDelTime(samplerateMillisec*apf1_default_delay_time_ms * delay_mult);
  apf2.setDelTime(samplerateMillisec*apf2_default_delay_time_ms * delay_mult);
  apf3.setDelTime(samplerateMillisec*apf3_default_delay_time_ms * delay_mult);
  apf4.setDelTime(samplerateMillisec*apf4_default_delay_time_ms * delay_mult);
  apf5.setDelTime(samplerateMillisec*apf5_default_delay_time_ms * delay_mult);
  apf6.setDelTime(samplerateMillisec*apf6_default_delay_time_ms * delay_mult);
}
