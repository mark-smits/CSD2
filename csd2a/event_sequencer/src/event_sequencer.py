import time
import simpleaudio as sa

# aanmaken van samples
kick = sa.WaveObject.from_wave_file("../audio/Kick.wav")
snare = sa.WaveObject.from_wave_file("../audio/Snare.wav")
clap = sa.WaveObject.from_wave_file("../audio/Clap.wav")
hhopen = sa.WaveObject.from_wave_file("../audio/HHOpen.wav")
hhclose = sa.WaveObject.from_wave_file("../audio/HHClosed.wav")

# event maker
def make_event(stamp, inst, instname, vel):
    event = {
        'timestamp': stamp,
        'instrument': inst,
        'instrumentname': instname,
        'velocity': vel,
        'duration': 200
        }
    return event

# test case
snare_event = make_event(100, snare, "snare", 100)
snare_event['instrument'].play()
time.sleep(1)
print(snare_event)
