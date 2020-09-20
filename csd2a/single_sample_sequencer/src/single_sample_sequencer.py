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
#elif userbpm == None:
#    print("using default bpm: " + str(bpm))
else:
    bpm = userbpm
    print("using bpm: " + str(bpm))

# functie die kwartnootintervallen omzet naar 16e timestamps
noteDurations = [0.25, 0.5, 1]
timestamps16th = [0]
sixteenthNoteDuration = 15/bpm
def durationsToTimestamps16th(noteDurs):
    for i, n in enumerate(noteDurs):
        if i == len(noteDurs) - 1:
            print("check")
        else:
            timestamps16th.append(timestamps16th[i] + n * 4)

durationsToTimestamps16th(noteDurations)
print(timestamps16th)

timestampssecs = []
def timestamps16thToTimestampssecs(ts16th):
    for n in ts16th:
        timestampssecs.append(n * sixteenthNoteDuration)

timestamps16thToTimestampssecs(timestamps16th)
print(timestampssecs)
