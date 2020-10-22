import random
import time
import simpleaudio as sa
from input_funcs import *
from seq_gen import *
from event_funcs import *
from midi_funcs import *

# instruments

kick = sa.WaveObject.from_wave_file(r"..\audio\Kick.wav")
clap = sa.WaveObject.from_wave_file(r"..\audio\Clap.wav")
snare = sa.WaveObject.from_wave_file(r"..\audio\Snare.wav")
hhopen = sa.WaveObject.from_wave_file(r"..\audio\HHOpen.wav")
hhclosed = sa.WaveObject.from_wave_file(r"..\audio\HHClosed.wav")
chord = sa.WaveObject.from_wave_file(r"..\audio\Chord.wav")
inst_wav_objs = [kick, clap, snare, hhopen, hhclosed, chord]

# input

instruments = []
bpm = input_bpm()
sixteenth = 15/bpm

lijstje = global_input(instruments) # haal alle input voor de sequences binnen en bouw een lijst met sequences
print('instrumenten: ' + str(instruments))
print('sequences: ' + str(lijstje))

# zoek de laagste gemeenschappelijke vermenigvuldiger

product = min_verm(lijstje)
print('laagste gemene deler: ' + str(product))

# egaliseer het lijstje/maak alle sequences even lang dmv laagste gemeenschappelijke vermenigvuldiger

for i, k in enumerate(lijstje):
    herhalingen = int(product/sum(k))
    temp_list = []
    for j in range(herhalingen):
        temp_list.append(k)
    lijstje[i] = sum(temp_list, [])

# maak MIDI-file

make_midi_file(bpm, lijstje)

# zet lijstje om naar events

eventlijstje = global_event_generator(lijstje, instruments, sixteenth, inst_wav_objs)

t0 = time.time()
for i in eventlijstje:
    handle_event(i, t0)
time.sleep(1) # laatste sample laten uitklinken
