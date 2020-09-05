import simpleaudio as sa

wave_obj = sa.WaveObject.from_wave_file(r"..\audio\Chord.wav")
num_plays = int(input(r"Aantal keren afspelen?"))

def play_my_file():
    play_obj = wave_obj.play()
    play_obj.wait_done()

while num_plays >  0:
    play_my_file()
    num_plays -= 1
