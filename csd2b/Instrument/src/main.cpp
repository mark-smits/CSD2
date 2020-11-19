#include <string>
#include "instrument.h"

main()
{
  Instrument fluit("Fluit", "Fuuuuuut");
  Instrument kick("Kick Drum", "Boem");
  fluit.play();
  kick.play();
}
