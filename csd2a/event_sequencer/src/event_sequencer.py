import time
import simpleaudio as sa

# aanmaken van samples
kick = sa.WaveObject.from_wave_file("../audio/Kick.wav")
snare = sa.WaveObject.from_wave_file("../audio/Snare.wav")
clap = sa.WaveObject.from_wave_file("../audio/Clap.wav")
hhopen = sa.WaveObject.from_wave_file("../audio/HHOpen.wav")
hhclosed = sa.WaveObject.from_wave_file("../audio/HHClosed.wav")

# event maker
def make_event(stamp, inst, instname):
    event = {
        'timestamp': stamp,
        'instrument': inst,
        'instrumentname': instname
        }
    return event

# ritme genereren
bpm = int(input("BPM?"))
sixteenth = 15/bpm
ritme = []
    # claps
ritme.append(make_event(4*sixteenth, clap, "clap"))
ritme.append(make_event(12*sixteenth, clap, "clap"))
    # snare
ritme.append(make_event(15*sixteenth, snare, "snare"))
    # kick
for i in range(3):
    ritme.append(make_event(i*4*sixteenth, kick, "kick"))
    # hats
    ritme.append(make_event((i*4+2)*sixteenth, hhopen, "hhopen"))
for i in range(15):
    ritme.append(make_event(i*sixteenth, hhclosed, "hhclosed"))

def keygen(e):
    return e['timestamp']

print(ritme)
ritme.sort(key=keygen)
print(ritme)


# event handler
