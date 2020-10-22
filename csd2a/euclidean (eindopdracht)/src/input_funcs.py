from seq_gen import *

    # kijken naar integers, floats en strings voor afvangen foute input
def isfloat(value):
  try:
    float(value)
    return True
  except ValueError:
    return False

def isint(value):
  try:
    int(value)
    return True
  except ValueError:
    return False

def isstring(value):
  try:
    str(value)
    return True
  except ValueError:
    return False

    # input voor het aantal stappen
def input_steps():
    incorrect_data_type = True # gaat vanaf het begin uit van foute input en blijft loopen totdat verwachte input gegeven word
    while incorrect_data_type == True:
        steps = input('nr steps? ')
        if isint(steps): # als de input een integer zet deze om naar een integer en check of deze binnen de juiste waarden valt
            steps = int(steps)
            if steps > 0 and steps < 1000: # check of er bruikbare waarden opgegeven worden
                print('nr. steps: ' + str(steps))
                incorrect_data_type = False # input is nu correct -> breek de loop
                return steps
            else:
                print('steps must obey: 0 < steps < 1000') # communiceer naar de user hoe hij/zij zijn input aan moet passen
        else:
            print('current type: ' + str(type(steps))) # communiceer naar de user dat hij foute data types gebruikt
            print('please input an integer')

    # input voor het aantal triggers gegeven het aantal steps
def input_trigs(steps):
    incorrect_data_type = True
    while incorrect_data_type == True:
        trigs = input('nr trigs? ')
        if isint(trigs):
            trigs = int(trigs)
            if trigs > 0 and trigs < 1000:
                if trigs > steps: # check of je niet meer triggers dan steps opvraagt
                    print('please use less trigs than steps')
                    print('nr. steps: ' + str(steps))
                    print('nr. trigs: ' + str(trigs))
                else:
                    print('nr. trigs: ' + str(trigs))
                    incorrect_data_type = False
                    return trigs
            else:
                print('trigs must obey: 0 < trigs < 1000')
        else:
            print('current type: ' + str(type(trigs)))
            print('please input an integer')

    # input voor BPM
def input_bpm():
    incorrect_data_type = True
    while incorrect_data_type == True:
        bpm_in = input('BPM? ')
        if isfloat(bpm_in):
            bpm_in = float(bpm_in)
            if bpm_in > 0 and bpm_in < 300:
                print('bpm: ' + str(bpm_in))
                incorrect_data_type = False
                return bpm_in
            else:
                print('bpm must obey: 0 > bpm > 300')
        else:
            print('current type: ' + str(type(bpm_in)))
            print('please input a float')

    # input voor aantal kanalen
def input_nr_seqs():
    incorrect_data_type = True
    while incorrect_data_type == True:
        nr_in = input('nr. of sequences? ')
        if isint(nr_in):
            nr_in = int(nr_in)
            if nr_in > 0 and nr_in <= 10: # houd het aantal mogelijke sequences laag
                print('nr. of sequences: ' + str(nr_in))
                incorrect_data_type = False
                return nr_in
            else:
                print('nr of sequences must obey: 0 > n >= 10')
        else:
            print('current type: ' + str(type(nr_in)))
            print('please input an integer')

    # input voor instrumenten
def input_instrument():
    incorrect_data_type = True
    print('instrument choices:') # geeft de user alle mogelijke string inputs
    print('kick')
    print('clap')
    print('snare')
    print('hhopen')
    print('hhclosed')
    print('chord')
    while incorrect_data_type == True:
        inst_in = input('instrument? ')
        if isstring(inst_in):
            inst_in = str(inst_in)
            if inst_in == 'kick' or inst_in == 'clap' or inst_in == 'snare' or inst_in == 'hhopen' or inst_in == 'hhclosed' or inst_in == 'chord':
                print('instrument: ' + str(inst_in)) # als de input een van de mogelijke strings is, bevestig deze keuze met de user
                incorrect_data_type = False
                return inst_in
            else:
                print('instrument must be an available choice')
        else:
            print('current type: ' + str(type(inst_in)))
            print('please input a string')

    # input voor meerdere sporen
def global_input(instr):
    test_nr = input_nr_seqs() # user geeft aantal sequences op
    test_list = [] # initieer de lijst
    i = 0 # initieer de index
    while i < test_nr:
        test_inst = input_instrument() # user geeft aan welk instrument/sample
        instr.append(test_inst) # voeg deze input toe aan de instrumenten lijst
        test_steps = input_steps() # user geeft aantal stappen op
        test_trigs = input_trigs(test_steps) # user geeft aantal triggers op
        test_list.append(euclidean_sequence_definer(test_steps, test_trigs)) # maak een sequences gegeven het aantal stappen en triggers en voeg die toe aan de sequence lijst
        i = i + 1 # update index 
    return test_list
