# event maker

def make_event(stamp, inst, instname):
    event = {
        'timestamp': stamp,
        'instrument': inst,
        'instrumentname': instname
        }
    return event

# event handler
