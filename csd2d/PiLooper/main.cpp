#include <iostream>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "delayLine.h"
#include "encoder.h" 
#include "looper.h"
#include "button.h"
#include <stdio.h>
#include <wiringPi.h>
#include <thread>

int main(int argc,char **argv)
{
  wiringPiSetup();
  
  JackModule jack;
  jack.init(argv[0]);
  float samplerate = jack.getSamplerate();
  
  Looper looper(samplerate);
  
  jack.onProcess = [&looper](jack_default_audio_sample_t *inBuf,
     jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {

    for(unsigned int i = 0; i < nframes; i++) {
      looper.write(inBuf[i]);
      outBuf[i] = looper.read() * 0.5;
      looper.tick();
    }
    return 0;
  };

  jack.autoConnect();

  //keep the program running and listen for user input, q = quit
  std::cout << "\n\nPress 'q' when you want to quit the program.\n";
  std::cout << "\nPress 'c' when you want to clear the looper buffer.\n";
  bool running = true;
  while (running)
  {
    switch (std::cin.get())
    {
      case 'q':
        running = false;
        jack.end();
        break;
      case 'c':
        looper.erase();
    }
  }

  return 0;
}
