#include "allPassFilter.h"
#include "delayLine.h"
#include "bqFilter.h"
#include <iostream>
#include <cstring>

AllPassFilter::AllPassFilter(uint delTime_in, float g_in, uint rate) : Effect(rate), delTime(delTime_in), val_g(g_in) {
  del.setDistance(delTime_in);
  float apf_freq = 1500.0;
  float lpf_freq = 6000.0;
  float resonance = 0.5;
  apf.setAPF(apf_freq, resonance);
  lpf.setLPF(lpf_freq, resonance);
}

AllPassFilter::~AllPassFilter(){

}

float AllPassFilter::read(float val_in){
  lpf.write(del.read());
  apf.write(lpf.read() * val_a + val_in * val_g);
  return apf.read();
}

void AllPassFilter::setG(float g_in){
  if (g_in > 1.0) {
    g_in = 1.0;
  }
  else if (g_in < 0.0) {
    g_in = 0.0;
  }
  val_g = g_in;
}

float AllPassFilter::getG(){
  return val_g;
}

void AllPassFilter::setA(float a_in){
  if (a_in > 1) {
    a_in = 1;
  }
  else if (a_in < 0) {
    a_in = 0;
  }
  val_a = a_in;
}

float AllPassFilter::getA(){
  return val_a;
}

void AllPassFilter::setLPF(float freq, float q_val){
  lpf.setLPF(freq,q_val);
}

void AllPassFilter::setDelTime(float val_in){
  if (val_in < 0.0) {
    val_in = 0.0;
  }
  del.setDistance((unsigned int)val_in);
}
