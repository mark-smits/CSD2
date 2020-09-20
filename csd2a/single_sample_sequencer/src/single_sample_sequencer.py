# import packages
import simpleaudio as sa
import time
import random

# geef bpm
bpm = 120
print("bpm = " + str(bpm))
userbpm = int(input("change bpm?"))
# check user bpm input
if userbpm <= 0:
    print("bpm too low")
else:
    bpm = userbpm
    print("using bpm: " + str(bpm))

# functie die kwartnootintervallen omzet naar 16e timestamps
noteDurations = [0.25, 0.5, 1]
timestamps16th = [0]
def durationsToTimestamps16th(noteDurs):
    for i, n in enumerate(noteDurs):
        if i == len(noteDurs) - 1:
            print("check")
        else:
            timestamps16th.append(timestamps16th[i] + n * 4)

durationsToTimestamps16th(noteDurations)
print(timestamps16th)

# functie die zestiende timestamps omzet naar secondes
timestampssecs = []
def timestamps16thToTimestampssecs(ts16th, tempo):
    for n in ts16th:
        timestampssecs.append(n * 15/tempo)

timestamps16thToTimestampssecs(timestamps16th, bpm)
finalsleep = noteDurations[len(noteDurations)-1]*60/bpm
print(timestampssecs)

# laad audio in
wave_obj = sa.WaveObject.from_wave_file(r"..\audio\Chord.wav")

# functie die samples in een sequences afspeelt
t0 = time.time()
timestamp = timestampssecs.pop(0)
while True:
    if time.time() >= t0 + timestamp:
        wave_obj.play()
        if timestampssecs:
            timestamp = timestampssecs.pop(0)
        else:
            time.sleep(finalsleep)
            break
