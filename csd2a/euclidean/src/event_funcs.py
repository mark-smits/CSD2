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
            event_list.append(make_event(k*stepsize + event_list[i-1]['timestamp'], inst, instname))
    event_list.sort(key=keygen)
    return event_list

# event handler
