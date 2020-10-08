import random
import time
from seq_gen import *
from even_funcs import *

# input

test_steps = int(input("nr steps?"))
test_trigs = int(input("nr trigs?"))
bpm = int(input("BPM?"))

# calculations

sixteenth = 15/bpm

test_list = euclidean_sequence_definer(test_steps, test_trigs)

print("Steplengths: " + str(test_list))
print("Total nr. of steps: " + str(sum(test_list)))
