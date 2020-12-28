#include <iostream>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "sine.h"
#include "square.h"
#include "saw.h"
#include "oscillator.h"
#include "envelope.h"
#include "synthvoice.h"

/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */

#define PI_2 6.28318530717959

int main(int argc,char **argv)
{
  // create a JackModule instance
  JackModule jack;

  // init the jack, use program name as JACK client name
  jack.init("example.exe");
  double samplerate = jack.getSamplerate();
  Synthvoice voice1(220, samplerate);
  voice1.setIndivivualAmp(1,0,0);
  voice1.setShaper(0.33,1);
  voice1.noteOn(69,63);
  float millis = 0;
  int sample = 0;

  //assign a function to the JackModule::onProces
  jack.onProcess = [&voice1,&sample,&millis,&samplerate](jack_default_audio_sample_t *inBuf,
     jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {

    static float amplitude = 0.15;

    for(unsigned int i = 0; i < nframes; i++) {
      outBuf[i] = voice1.getSample() * amplitude;// * env1.getValue();
      voice1.tick();
      sample++;
      while ( sample > (samplerate/1000) )
      {
        sample -= samplerate/1000;
        millis++;
        //std::cout << "milliseconds: " << millis << '\n';
      }
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
