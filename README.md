# Arduino-Basics 

*Von xd23fe39*

Alle Beispiele in Verzeichnis `/src` sind kompatibel zu Arduino Nano und Arduino UNO Boards.

## Voraussetzungen

### Zugriff auf `/dev/ttyUSB*` unter Linux

>Einige User haben in Foren erwähnt, dass nach einer Neuinstallation von ArduinoIDE das 
>Problem gefixed gewesen sein soll.

Terminal öffnen und folgende Befehle absetzen (root-Berechtigung erforderlich):

    sudo ls -laci /dev/ttyUSB*      # Gruppe dialout mit rw-Berechtigung prüfen

    id -a                           # ist der eigene Benutzer in der Gruppe dialout

Falls hier etwal nicht stimmen sollte, dann folgende Befehle verwenden:

```sh
# Eigenen User der Gruppe dialout zuordnen
sudo usermod -a -G dialout $USER
# Anpassen der Zugriffsrechte (nur, falls erforderlich)
sudo chmod g+rw /dev/ttyUSB0
``` 

