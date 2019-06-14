# P-I-R Modul 

## Beschreibung

Der Bewegungsmelder erkennt menschliche Bewegungen bis zu einem Abstand von 7m bei ca. 
120 Grad Erfassungswinkel.  

## PIN Layout

Modell: HC-SR501

PIN   | Beschreibung   |UNO  |NANO
------|----------------|-----|-----
VCC   | +5V            |+5V  |+5V
SIG   | Signal Out     |PIN4 |PIN4
GND   | Ground         |GND  |GND

Am Produkt selbst können über die Potenziometer T (time) und S (sensibility) 
die Signaldauer und Empfindlichkeit eingestellt werden.

## Einbinden der Klasse `PIRMotionSensor_C`

```cpp
#include "PIRMotionSensor.h"

PIRMotionSensor_C pir(PIN4);

```
