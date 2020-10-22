Dit script is gemaakt als eindopdracht voor CSD2a

Het geeft de gebruiker de mogelijkheid om een poliritmische sequence te laten genereren door meerdere euclidische sequences tov elkaar te laten verschuiven.
De gebruiker geeft het BPM op en daarna het aantal sequence (het aantal instrumenten).
Voor elke sequence geeft de gebruiker een aantal stapjes op en een aantal triggers wat verdeeld moet worden over de stapjes.
Het script verdeeld de triggers evenredig over de stapjes, bv zoals:

steps: 16
trigs: 7
sequence: o--o-o-o--o-o-o-

Waarbij 'o' een trigger is en '-' een rust.

Het script vraagt voor elke sequence een sample om af te spelen, deze bestaan uit een aantal drum samples en een akkoord.
Na het genereren van de sequences en een hele loop te hebben berekend (ofwel alle mogelijke verschuivingen hebben plaatsgevonden) maakt het een MIDIfile.
De eerste sequence word op MIDI-noot 36 gemaakt, elke opvolgende sequence zit een pitch waarde boven de vorige.
Als de MIDIfile is gegenereerd speelt het script de sequence terug voor de gebruiker.

benodigde packages:
simpleaudio
midiutils