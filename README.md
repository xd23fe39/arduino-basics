# Arduino-Basics 

*Von xd23fe39*

Alle Beispiele in Verzeichnis `/src` sind kompatibel zu Arduino Nano und Arduino UNO Boards.

## Voraussetzungen

### Zugriff auf `/dev/ttyUSB*` unter Linux

Terminal öffnen und folgende Befehle absetzen (root-Berechtigung erforderlich):

```sh
# Aktuelle Gruppenmitgliedschaften anzeigen
id -a $USER
# Eigenen User der Gruppe dialout zuordnen
sudo usermod -a -G dialout $USER
# Gruppenmitgliedschaften nochmals anzeigen
id -a $USER
# Anzeigen der Zugriffsrechte auf ttyUSB*
ls -laci /dev/ttyUSB*
# Anpassen der zugriffsrechte (nur, falls erforderlich)
# sudo chmod a+rw /dev/ttyUSB0
``` 

>Einige User haben in Foren erwähnt, dass nach einer Neuinstallation von ArduinoIDE das 
>Problem gefixed gewesen sein soll.
