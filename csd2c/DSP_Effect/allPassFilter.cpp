#include "allPassFilter.h"
#include "delayLine.h"
#include "bqFilter.h"
#include <iostream>
#include <cstring>

AllPassFilter::AllPassFilter(uint delTime_in, float g_in, uint samplerate) : del(delTime_in*2), delTime(delTime_in), val_g(g_in), val_a(1.0),
  lpf(0.003643, 0.007285, 0.003643, -1.81624, 0.83328, samplerate), apf(0,0,0,0,0,samplerate), samplerate(samplerate){
  del.setDistance(delTime_in);
  std::cout << "APF constructor" << '\n';
  apf.setAPF(1000,1.0);
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
