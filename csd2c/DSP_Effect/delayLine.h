#pragma once

typedef unsigned int uint;

class DelayLine {

public:

  // constructor & destructor
  DelayLine(uint size_in);
  ~DelayLine();

  // setters & getters
  void setDistance(uint dist_in);
  uint getDistance();
  void setFB(float fb_in);
  float getFB();

  // delay line read & write
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
  float feedback;
  uint size;
  uint writeHead;
  uint readHead;
  uint distance;
};
