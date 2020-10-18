from midiutil import MIDIFile

def make_midi_file(tempo, list):
    # list een lijst met sequences voor elk spoor (stapjes zijn 16e noten)
    midi_seq = MIDIFile(1) # maakt een track
    track = 0 # eertse track
    midi_time = 0 # begin aan het begin
    midi_seq.addTrackName(track, midi_time, 'Euclidean Sequence') # geef naam
    midi_seq.addTempo(track, midi_time, tempo) # geef tempo
    channel = 9 # zet alles op midi channel 10
    volume = 100 # alle vel. waardes op 100
    pitch = 36 # starting pitch op 36
    for i in list: # pak een sequence uit de lijst
        midi_time = 0 # reset time
        for j in i: # ga elk stapje in de sequence af
            midi_seq.addNote(track, channel, pitch, midi_time/4, j/4, volume)
            midi_time = midi_time + j
        pitch = pitch + 1
    with open('Euclidean Sequence.mid', 'wb') as output:
        midi_seq.writeFile(output)
