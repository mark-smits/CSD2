from seq_gen import *

    # kijken naar integers en floats voor afvangen foute input
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
    incorrect_data_type = True
    while incorrect_data_type == True:
        steps = input('nr steps? ')
        if isint(steps):
            steps = int(steps)
            if steps > 0 and steps < 1000:
                print('nr. steps: ' + str(steps))
                incorrect_data_type = False
                return steps
            else:
                print('steps must obey: 0 < steps < 1000')
        else:
            print('current type: ' + str(type(steps)))
            print('please input an integer')

    # input voor het aantal triggers
def input_trigs(steps):
    incorrect_data_type = True
    while incorrect_data_type == True:
        trigs = input('nr trigs? ')
        if isint(trigs):
            trigs = int(trigs)
            if trigs > 0 and trigs < 1000:
                if trigs > steps:
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
            if nr_in > 0 and nr_in <= 10:
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
    print('instrument choices:')
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
                print('instrument: ' + str(inst_in))
                incorrect_data_type = False
                return inst_in
            else:
                print('instrument must be an available choice')
        else:
            print('current type: ' + str(type(inst_in)))
            print('please input a string')

    # input voor meerdere sporen
def global_input(instr):
    test_nr = input_nr_seqs()
    test_list = []
    i = 0
    while i < test_nr:
        test_inst = input_instrument()
        instr.append(test_inst)
        test_steps = input_steps()
        test_trigs = input_trigs(test_steps)
        test_list.append(euclidean_sequence_definer(test_steps, test_trigs))
        i = i + 1
    return test_list
