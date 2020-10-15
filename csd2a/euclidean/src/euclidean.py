import random
import time
from input_funcs import *
from seq_gen import *
from event_funcs import *

# input
test_steps = input_steps()
test_trigs = input_trigs(test_steps)
bpm = input_bpm()

# instruments

kick = "kick" # dit zou een WaveObject zijn

# calculations

sixteenth = 15/bpm
test_list = euclidean_sequence_definer(test_steps, test_trigs)

print("Steplengths: " + str(test_list))
print("Total nr. of steps: " + str(sum(test_list)))

listvisualizer = []
for i in test_list:
    listvisualizer.append('o')
    while i > 1:
        listvisualizer.append('-')
        i = i - 1
listprinter = ''.join(listvisualizer)
print(listprinter)
print("sixteenth: " + str(sixteenth))

test_events = list2event(test_list, sixteenth, kick, "kick")
print('nr. of events: ' + str(len(test_events)))
print("eventlist: " + str(test_events))
