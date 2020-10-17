import time
# event maker

def make_event(stamp, inst, instname):
    event = {
        'timestamp': stamp,
        'instrument': inst,
        'instrumentname': instname
        }
    return event

def keygen(e):
    return e['timestamp']

def list2event(triglist, stepsize, inst, instname):
    event_list = [make_event(0, inst, instname)]
    for i, k in enumerate(triglist):
        if k == sum(triglist):
            break
        else:
            if i < len(triglist) - 1:
                event_list.append(make_event(k*stepsize + event_list[i]['timestamp'], inst, instname))
    # event_list.sort(key=keygen)
    return event_list

# event handler

def handle_event(event, t0):
    waiting = True
    while waiting:
        t = time.time()
        if t - t0 >= event['timestamp']:
            event['instrument'].play()
            waiting = False
        else:
            time.sleep(0.001)
