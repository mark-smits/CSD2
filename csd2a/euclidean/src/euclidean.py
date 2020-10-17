import random
import time
import simpleaudio as sa
from input_funcs import *
from seq_gen import *
from event_funcs import *

# instruments
kick = sa.WaveObject.from_wave_file(r"..\audio\Kick.wav")
clap = sa.WaveObject.from_wave_file(r"..\audio\Clap.wav")
snare = sa.WaveObject.from_wave_file(r"..\audio\Snare.wav")
hhopen = sa.WaveObject.from_wave_file(r"..\audio\HHOpen.wav")
hhclosed = sa.WaveObject.from_wave_file(r"..\audio\HHClosed.wav")
chord = sa.WaveObject.from_wave_file(r"..\audio\Chord.wav")

# input
instruments = []
bpm = input_bpm()
sixteenth = 15/bpm

lijstje = global_input(instruments)
print('instrumenten: ' + str(instruments))
print('lijstje: ' + str(lijstje))
product = min_verm(lijstje)
print('laagste gemene deler: ' + str(product))
events = []
index = 0
for i in lijstje:
    print("Steplengths: " + str(i))
    print("Total nr. of steps: " + str(sum(i)))

    listprinter = seq_visualizer(i)
    print(listprinter)
    # print("sixteenth: " + str(sixteenth))

    if instruments[index] == 'kick':
        test_events = list2event(i, sixteenth, kick, instruments[index])
    elif instruments[index] == 'clap':
        test_events = list2event(i, sixteenth, clap, instruments[index])
    elif instruments[index] == 'hhopen':
        test_events = list2event(i, sixteenth, hhopen, instruments[index])
    elif instruments[index] == 'hhclosed':
        test_events = list2event(i, sixteenth, hhclosed, instruments[index])
    elif instruments[index] == 'snare':
        test_events = list2event(i, sixteenth, snare, instruments[index])
    elif instruments[index] == 'chord':
        test_events = list2event(i, sixteenth, chord, instruments[index])

    events.append(test_events)
    print('nr. of events: ' + str(len(test_events)))
    print("eventlist: " + str(test_events))
    index = index + 1

#print(events)
eventlijst = sum(events, [])
eventlijst.sort(key=keygen)
#print(eventlijst)
