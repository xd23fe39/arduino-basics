# Arduino Project

Signale einer IR-Fernbedienung empfangen und auswerten. 

- https://github.com/z3t0/Arduino-IRremote
- https://arduino-info.wikispaces.com/IR-RemoteControl
- https://www.arduino.cc/

## Voraussetzungen

Installieren der Bibliothek zur Einbindung von IR-Receiver.

1. Starten von ArduinoIDE und öffnen von `Sketch|Bibliothek einbinden'
1. Bibliotheken verwalten: IRremote selektieren und installieren
1. IDE beenden und neu starten

## Coding

```cpp
// Include library
#include <IRremote.h>

// Create irrecv-Object
IRrecv* irrecv = new IRrecv(pin);

// Enable IR receiver
irrecv->enableIRIn();

// and so on ...
```

