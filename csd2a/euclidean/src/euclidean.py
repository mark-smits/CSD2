import random
import time
import simpleaudio as sa
from input_funcs import *
from seq_gen import *
from event_funcs import *

# input
test_nr = input_nr_seqs()
test_steps = input_steps()
test_trigs = input_trigs(test_steps)
bpm = input_bpm()

# instruments
kick = sa.WaveObject.from_wave_file(r"..\audio\Kick.wav")
clap = sa.WaveObject.from_wave_file(r"..\audio\Clap.wav")
snare = sa.WaveObject.from_wave_file(r"..\audio\Snare.wav")
hhopen = sa.WaveObject.from_wave_file(r"..\audio\HHOpen.wav")
hhclosed = sa.WaveObject.from_wave_file(r"..\audio\HHClosed.wav")
chord = sa.WaveObject.from_wave_file(r"..\audio\Chord.wav")

# calculations
sixteenth = 15/bpm
test_list = euclidean_sequence_definer(test_steps, test_trigs)

print("Steplengths: " + str(test_list))
print("Total nr. of steps: " + str(sum(test_list)))

listprinter = seq_visualizer(test_list)
print(listprinter)
print("sixteenth: " + str(sixteenth))

test_events = list2event(test_list, sixteenth, kick, "kick")
print('nr. of events: ' + str(len(test_events)))
print("eventlist: " + str(test_events))
