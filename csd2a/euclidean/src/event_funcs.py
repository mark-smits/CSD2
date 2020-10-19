import time
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
