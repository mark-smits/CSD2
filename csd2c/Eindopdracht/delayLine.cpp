#include "delayLine.h"
#include <iostream>
#include <cstring>

DelayLine::DelayLine(uint size_in) : Effect(), size(size_in) {
  allocateBuffer();
}

DelayLine::~DelayLine() {
  releaseBuffer();
}

void DelayLine::allocateBuffer(){
  bufferMemory = (float*)malloc(size * sizeof(float));
	memset(bufferMemory, 0, size * sizeof(float));
}

void DelayLine::releaseBuffer(){
  free(bufferMemory);
}

void DelayLine::setDistance(uint dist_in){
  distance = dist_in;
  readHead = writeHead - distance + size;
  if (readHead < 0) readHead += size;
  wrapHead(readHead);
}

uint DelayLine::getDistance(){
  return distance;
}

void DelayLine::setFB(float fb_in){
  if (fb_in > 1.0){
    fb_in = 1.0;
  }
  else if (fb_in < 0){
    fb_in = 0;
  }
  feedback = fb_in;
}

float DelayLine::getFB(){
  return feedback;
}
