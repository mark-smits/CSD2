#include <iostream>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "delayLine.h"
#include "allPassFilter.h"
#include "reverb.h"
#include "bqFilter.h"
#include "chorus.h"

/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */

/*
 * biquad values lpf, cof ~1000hz; (0.003643, 0.007285, 0.003643, -1.81624, 0.83328)
 * biquad values lpf, cof ~500hz; (0.001043, 0.002085, 0.001043, -1.903954, 0.908831)
 * biquad values lpf, cof ~3000hz; (0.030008, 0.060016, 0.030008, -1.43764, 0.573078)
 */

// 10 seconds if samplerate = 44100
#define MAX_DELAY_SIZE 441000
#define DELAY_TIME_SEC 0.5f

#define PI_2 6.28318530717959

// Run program and set delaytime as argument (in seconds)

int main(int argc,char **argv)
{
  // create a JackModule instance
  JackModule jack;

  // init the jack, use program name as JACK client name
  jack.init(argv[0]);
  float samplerate = jack.getSamplerate();

  // retrieve either default or console line argument delaytime
  float delayTimeSec = DELAY_TIME_SEC;
  if(argc >= 2) delayTimeSec = (float) atof(argv[1]);
  //std::cout <<  "\nDelay time in seconds: " << delayTimeSec << "\n";

  int numAPFSamplesDelay = samplerate * 10.0/1000.0;
  std::cout << "\ninput is delay by " << numAPFSamplesDelay << " number of samples\n";

  Reverb verb(samplerate);
  BQFilter lpFilter(0.003643, 0.007285, 0.003643, -1.81624, 0.83328, samplerate);
  Chorus chor(samplerate);

  //assign a function to the JackModule::onProces
  jack.onProcess = [&verb, &lpFilter](jack_default_audio_sample_t *inBuf,
     jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {

    for(unsigned int i = 0; i < nframes; i++) {
      // write input to delay
      verb.write(inBuf[i]);
      // read delayed output
      lpFilter.write(verb.read(inBuf[i]));
      outBuf[i] = verb.read(inBuf[i]) * 0.5;
      // update delay --> next sample
      verb.tick();
    }
    return 0;
  };

  jack.autoConnect();

  //keep the program running and listen for user input, q = quit
  std::cout << "\n\nPress 'q' when you want to quit the program.\n";
  bool running = true;
  while (running)
  {
    switch (std::cin.get())
    {
      case 'q':
        running = false;
        jack.end();
        break;
    }
  }

  //end the program
  return 0;
} // main()
