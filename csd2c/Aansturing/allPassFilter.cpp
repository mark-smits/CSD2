#include "allPassFilter.h"
#include "delayLine.h"
#include "bqFilter.h"
#include <iostream>
#include <cstring>

AllPassFilter::AllPassFilter(uint delTime_in, float g_in, uint samplerate) : del(delTime_in*4), delTime(delTime_in), val_g(g_in), val_a(0.95),
  lpf(samplerate), apf(samplerate), samplerate(samplerate){
  del.setDistance(delTime_in);
  std::cout << "APF constructor" << '\n';
  std::cout << "APF delayline: " << delTime_in << "\n";
  apf.setAPF(1500.0,0.7);
  lpf.setLPF(6000.0,0.7);
  lpf.printvals();
}

AllPassFilter::~AllPassFilter(){

}

float AllPassFilter::read(float val_in){
  lpf.write(del.read());
  apf.write(lpf.read() * val_a + val_in * val_g);
  return apf.read();
}

void AllPassFilter::setG(float g_in){
  if (g_in > 1) {
    g_in = 1;
  }
  else if (g_in < 0) {
    g_in = 0;
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
  std::cout << "delTime: " << (int)val_in << "\n";
  del.setDistance((unsigned int)val_in);
}
