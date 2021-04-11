#include "bqFilter.h"
#include <iostream>
#include <math.h>

#define PI 3.14159265358979323846

BQFilter::BQFilter(uint rate) : BQFilter(0,0,0,0,0,rate){}

BQFilter::BQFilter(float a0_in, float a1_in, float a2_in, float b1_in, float b2_in, uint rate) :
  a0(a0_in), a1(a1_in), a2(a2_in), b1(b1_in), b2(b2_in), Effect(rate){
    
}

BQFilter::~BQFilter(){

}

void BQFilter::setParameters(float a0_in, float a1_in, float a2_in, float b1_in, float b2_in){
  a0 = a0_in;
  a1 = a1_in;
  a2 = a2_in;
  b1 = b1_in;
  b2 = b2_in;
}

void BQFilter::setLPF(float freq, float q_val){
  float theta_val = 2*PI*freq/getSamplerate();
  float d_val = 1/q_val;
  float beta_val = ( 1-d_val/2*sin(theta_val) )/( 1+d_val/2*sin(theta_val) )*0.5;
  float gamma_val = (0.5 + beta_val)*cos(theta_val);
  a0 = ( 0.5+beta_val-gamma_val )/2.0;
  a1 = 0.5+beta_val-gamma_val;
  a2 = ( 0.5+beta_val-gamma_val )/2.0;
  b1 = -2.0*gamma_val;
  b2 = 2.0*beta_val;
}

void BQFilter::setHPF(float freq, float q_val){
  float theta_val = 2*PI*freq/getSamplerate();
  float d_val = 1/q_val;
  float beta_val = ( 1-d_val/2*sin(theta_val) )/( 1+d_val/2*sin(theta_val) )*0.5;
  float gamma_val = (0.5 + beta_val)*cos(theta_val);
  a0 = ( 0.5+beta_val+gamma_val )/2.0;
  a1 = (0.5+beta_val+gamma_val)*-1.0;
  a2 = ( 0.5+beta_val+gamma_val )/2.0;
  b1 = -2.0*gamma_val;
  b2 = 2.0*beta_val;
}

void BQFilter::setBPF(float freq, float q_val){
  float theta_val = 2*PI*freq/getSamplerate();
  float beta_val = ( 1-tan(theta_val/2.0/q_val) )/( 1+tan(theta_val/2.0/q_val) )*0.5;
  float gamma_val = (0.5*beta_val)*cos(theta_val);
  a0 = 0.5-beta_val;
  a1 = 0.0;
  a2 = (0.5-beta_val)*-1.0;
  b1 = -2.0*gamma_val;
  b2 = 2.0*beta_val;
}

void BQFilter::setBRF(float freq, float q_val){
  float theta_val = 2*PI*freq/getSamplerate();
  float beta_val = ( 1-tan(theta_val/2.0/q_val) )/( 1+tan(theta_val/2.0/q_val) )*0.5;
  float gamma_val = (0.5*beta_val)*cos(theta_val);
  a0 = 0.5+beta_val;
  a1 = -2.0*gamma_val;
  a2 = 0.5+beta_val;
  b1 = -2.0*gamma_val;
  b2 = 2.0*beta_val;
}

void BQFilter::setAPF(float freq, float q_val){
  float alpha_val = ( tan(PI*q_val/getSamplerate())-1.0 )/( tan(PI*q_val/getSamplerate())+1.0 );
  float theta_val = PI*freq/getSamplerate();
  float beta_val = cos(theta_val)*-1.0;
  a0 = alpha_val*-1.0;
  a1 = beta_val*( 1.0-alpha_val );
  a2 = 1.0;
  b1 = beta_val*( 1.0-alpha_val );
  b2 = alpha_val*-1.0;
}

void BQFilter::write(float val_in){
  xn2 = xn1;
  xn1 = xn;
  xn = val_in;
  yn2 = yn1;
  yn1 = yn;
  yn = a0*xn + a1*xn1 + a2*xn2 - b1*yn1 - b2*yn2;
}

float BQFilter::read(){
  return yn;
}

void BQFilter::printVals(){
  std::cout << "a0: " << a0 << '\n';
  std::cout << "a1: " << a1 << '\n';
  std::cout << "a2: " << a2 << '\n';
  std::cout << "b1: " << b1 << '\n';
  std::cout << "b2: " << b2 << '\n';
}
