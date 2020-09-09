import time
import simpleaudio as sa
bpm = 125

wave_obj = sa.WaveObject.from_wave_file(r"..\audio\Chord.wav")

i = 0
sequencer = [0]
numNotes = int(input("Amount of notes?"))

while (numNotes > i):
    sequencer.append(sequencer[i] + int(input("Interval?")))
    i += 1
#sequencer = [0, 3, 6, 8, 12]

bpm = int(input("BPM?"))

while True:
    for index, t in enumerate(sequencer):
        print(f"index: {index} t: {t}")
        if index == len(sequencer)-1:
            interval = (16 - sequencer[index])/bpm*15
        else:
            interval = (sequencer[index + 1] - sequencer[index])/bpm*15
        wave_obj.play()
        time.sleep(interval)
