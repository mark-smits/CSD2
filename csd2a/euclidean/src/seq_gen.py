# euclidean sequence calculator

def euclidean_sequence_definer(steps, trigs):
    stepsize = int(steps/trigs) # kleinste stapgrootte
    remainder = steps % trigs # modulo
    numlarge = remainder # aantal grote stappen
    numsmall = trigs - remainder # aantal kleine stappen
    i = 0
    j = 0
    largecheck = []
    smallcheck = []
    while i < numlarge:
        largecheck.append(i/numlarge)
        i = i + 1
    while j < numsmall:
        smallcheck.append(j/numsmall)
        j = j + 1
    triglist = []
    while (largecheck or smallcheck):
        if largecheck and smallcheck:
            if largecheck <= smallcheck:
                triglist.append(stepsize + 1)
                largecheck.pop(0)
            elif smallcheck < largecheck:
                triglist.append(stepsize)
                smallcheck.pop(0)
        else:
            if not largecheck and smallcheck:
                triglist.append(stepsize)
                smallcheck.pop(0)
            elif largecheck and not smallcheck:
                triglist.append(stepsize + 1)
                largecheck.pop(0)
            else:
                print(done)
                break
    return triglist


def seq_visualizer(list):
    listvisualizer = []
    for i in list:
        listvisualizer.append('o')
        while i > 1:
            listvisualizer.append('-')
            i = i - 1
    visual = ''.join(listvisualizer)
    return visual
