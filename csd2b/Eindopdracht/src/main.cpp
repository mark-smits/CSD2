#include <iostream>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "sine.h"
#include "square.h"
#include "saw.h"
#include "oscillator.h"
#include "envelope.h"
#include "sandh.h"
#include "synthvoice.h"
#include "melodygenerator.h"
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <ctime>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

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

  // init melodie
  MelodyGenerator melodie(65,0);
  int nootjes[] = {0,2,4,5,7,9,11};
  melodie.setScale( nootjes );

  // init synthvoices
  Synthvoice voice1(220, samplerate);
  voice1.setIndivivualAmp(1,0,0);
  voice1.setShaper(0.33,1);
  voice1.noteOn(melodie.getNote(),63);
  SandH sh1(samplerate);
  sh1.generateTime();

  // init time functions
  auto millis_0 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  auto millis = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

  //assign a function to the JackModule::onProces
  jack.onProcess = [&voice1,&millis_0,&millis,&samplerate,&sh1,&melodie](jack_default_audio_sample_t *inBuf,
     jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {

    static float amplitude = 0.15;

    millis = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millis_0;
    while (millis > 1000)
    {
      millis -= 1000;
    }
    if (millis < 500)
    {
      if (!voice1.getNoteOn())
      {
        voice1.noteOn(melodie.getNote(),63);
      }
    }
    else
    {
      if (voice1.getNoteOn())
      {
        voice1.noteOff();
      }
    }

    for(unsigned int i = 0; i < nframes; i++) {
      outBuf[i] = voice1.getSample() * amplitude;
      voice1.tick();
      sh1.tick();
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
