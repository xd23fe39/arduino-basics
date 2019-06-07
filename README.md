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

## Download und Installation

Als IDE wird PlatformIO (Erweiterung in VSCode) und ArduinoIDE genutzt. 

Download:

    sudo mkdir -p /opt/arduino-ide/available
    sudo mv arduino-1.8.9-linux64.tar.xz /opt/arduino-ide/available
    sudo tar -xvf arduino-1.8.9-linux64.tar.xz 

Installation:

    cd /opt/arduino-ide/available/arduino-1.8.9
    sudo ./install.sh 

Installation prüfen:

    ls -la /usr/local/bin/arduino
 