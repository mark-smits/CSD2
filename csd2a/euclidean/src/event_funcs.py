import time
from seq_gen import *
# event maker

def make_event(stamp, inst, instname): # maakt een event aan mbv dictionaries
    event = {
        'timestamp': stamp,
        'instrument': inst,
        'instrumentname': instname
        }
    return event

def keygen(e): # bepaalt parameter om op te sorteren na het omzetten naar events
    return e['timestamp']

def list2event(triglist, stepsize, inst, instname): # zet de gegeven lijst met staplengtes om naar events
    event_list = [make_event(0, inst, instname)] # eerste item in de lijst op t=0
    for i, k in enumerate(triglist): # haalt voor alle staplengtes op en hun indices
        if k == sum(triglist):
            break
        else:
            if i < len(triglist) - 1: # maak events voor alle stappen behalve de laatste
                event_list.append(make_event(k*stepsize + event_list[i]['timestamp'], inst, instname)) # voeg de events toe aan de eventlijst
    return event_list

# zet heel de lijst met sequences om naar tijdgesoorteerde events

def global_event_generator(list, instrumenten, sixteenth, wave_objs):
    events = []
    index = 0
    for i in list:
        if instrumenten[index] == 'kick':
            test_events = list2event(i, sixteenth, wave_objs[0], instrumenten[index])
        elif instrumenten[index] == 'clap':
            test_events = list2event(i, sixteenth, wave_objs[1], instrumenten[index])
        elif instrumenten[index] == 'hhopen':
            test_events = list2event(i, sixteenth, wave_objs[3], instrumenten[index])
        elif instrumenten[index] == 'hhclosed':
            test_events = list2event(i, sixteenth, wave_objs[4], instrumenten[index])
        elif instrumenten[index] == 'snare':
            test_events = list2event(i, sixteenth, wave_objs[2], instrumenten[index])
        elif instrumenten[index] == 'chord':
            test_events = list2event(i, sixteenth, wave_objs[5], instrumenten[index])

        events.append(test_events)
        print('nr. of ' + instrumenten[index] + ' events : ' + str(len(test_events)))
        print("Steplengths: " + str(i))

        listprinter = seq_visualizer(i)
        print(listprinter)

        index = index + 1

    eventlijst = sum(events, [])
    eventlijst.sort(key=keygen)
    return eventlijst

# event handler

def handle_event(event, t0): # speelt sampes af gegeven een starttijd
    waiting = True # als de sample nog niet heeft gespeeld blijft het script wachten
    while waiting:
        t = time.time() # update de tijd
        if t - t0 >= event['timestamp']: # als de verstreken tijd langer is dan de timestamp -> speel de sample
            event['instrument'].play()
            waiting = False # while loop compleet, niet langer wachten op het afspelen van de sample
        else:
            time.sleep(0.001) # korte delay om de loop niet te vaak te herhalen
