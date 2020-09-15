import time
import simpleaudio as sa

#load samples
wave_obj_kick = sa.WaveObject.from_wave_file(r"..\audio\Kick.wav")
wave_obj_clap = sa.WaveObject.from_wave_file(r"..\audio\Clap.wav")
wave_obj_snare = sa.WaveObject.from_wave_file(r"..\audio\Snare.wav")
wave_obj_hhopen = sa.WaveObject.from_wave_file(r"..\audio\HHOpen.wav")
wave_obj_hhclosed = sa.WaveObject.from_wave_file(r"..\audio\HHClosed.wav")

#make all sequences
sequencer = [[], [], [], [], []]
seq = 0
lengte = [0,0,0,0,0]

#get starting time
time_0 = time.time()

while seq < 5: #maak vijf seqeunces in een lijst
    numNotes = int(input("Amount of notes?")) #aantal intervallen per sequence
    offset = int(input("Startpoint offset?")) #offset voor het startpunt
    i = 0
    sequencer[seq].append(offset)
    while (numNotes > i):
        if numNotes - 1 == i:
            if sequencer[seq][i]:
                lengte[seq] = sequencer[seq][i] + int(input("Interval?")) #geeft lengte op van elke sequence als laatste input en plaatst in losse lijst achter alle sequences
            else:
                lengte[seq] = int(input("Interval?"))
        else:
            sequencer[seq].append(sequencer[seq][i] + int(input("Interval?"))) #zet intervallen om in 'triggerpunten'
        i += 1
    seq += 1

bpm = int(input("BPM?"))
index = 0
interval = 15/bpm
swing = 0.2 #swing: voor positief 0-1, voor negatief -1-0

def play_files(nr):
    if nr == 0:
        wave_obj_kick.play()
    elif nr == 1:
        wave_obj_clap.play()
    elif nr == 2:
        wave_obj_snare.play()
    elif nr == 3:
        wave_obj_hhopen.play()
    elif nr == 4:
        wave_obj_hhclosed.play()

def sequencers():
    for i, k in enumerate(sequencer):
        for t in k:
            if index % lengte[i] == t:
                play_files(i)

while True:
    if index % 2 == 0:
        if time.time() > time_0 + interval * (index - swing):
            sequencers()
            index += 1
    else:
        if time.time() > time_0 + interval * (index + swing):
            sequencers()
            index += 1
