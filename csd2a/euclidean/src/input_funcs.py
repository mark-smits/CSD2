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
