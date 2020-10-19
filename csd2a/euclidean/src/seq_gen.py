# euclidean sequence calculator

def euclidean_sequence_definer(steps, trigs):
    stepsize = int(steps/trigs) # kleinste stapgrootte (grootste stapgrootte is kleinste + 1)
    remainder = steps % trigs # modulo voor het bepalen van het aantal grote stappen
    numlarge = remainder # aantal grote stappen
    numsmall = trigs - remainder # aantal kleine stappen
    i = 0 # initieer indices
    j = 0
    largecheck = [] # maakt twee lists om tov elkaar te vergelijken
    smallcheck = []
    while i < numlarge: # maak twee lijsten met oplopende breuken gegeven het aantal stappen
        largecheck.append(i/numlarge)
        i = i + 1
    while j < numsmall:
        smallcheck.append(j/numsmall)
        j = j + 1
    triglist = [] # initieer de lijst met triggers
    while (largecheck or smallcheck): # zolang een van beide lijsten nog waardes heeft blijf triggers toevoegen
        if largecheck and smallcheck: # ga kijken welke lijst de laagste breuk heeft om zo de kleine en grote stappen evenredig te verdelen over de trigger lijst en verwijder dan deze breuk uit de lijst
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

# visualizer voor de sequence

def seq_visualizer(list): # bouw een lijst met o voor triggers en - rusten
    listvisualizer = []
    for i in list:
        listvisualizer.append('o')
        while i > 1:
            listvisualizer.append('-')
            i = i - 1
    visual = ''.join(listvisualizer) # maak de lijst tot een string
    return visual

# laagste gemeenschappelijke vermenigvuldiger berekenen

def min_verm(list): # ga op zoek naar de laagste waarde waardoor de lengtes voor alle sequences gedeeld kan worden door te controleren of de modulo voor alle sequences 0 is gegeven een product
    incompleet = True
    product = 1
    while incompleet:
        check = 0
        for i in list:
            check = check + (product % sum(i))
        if check == 0:
            incompleet = False
            return product
        else:
            product = product + 1
