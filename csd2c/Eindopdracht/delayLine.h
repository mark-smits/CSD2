#pragma once
#include "effect.h"

typedef unsigned int uint;

class DelayLine : public Effect {

public:
  DelayLine(uint size_in);
  ~DelayLine();
  
  void setDistance(uint dist_in);
  uint getDistance();
  void setFB(float fb_in);
  float getFB();
  
  inline void write(float val){ bufferMemory[writeHead] = val + (feedback * bufferMemory[readHead]); }
  inline float read(){ return bufferMemory[readHead]; }

  inline void tick(){
    writeHead++;
    wrapHead(writeHead);
    readHead++;
    wrapHead(readHead);
  }

private:

  inline void wrapHead(uint& head){
    if (head >= size) head -= size;
  }

  void allocateBuffer();
  void releaseBuffer();

  float* bufferMemory;
  float feedback = 0;
  uint size;
  uint writeHead = 0;
  uint readHead = 0;
  uint distance;
};
