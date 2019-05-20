class AnalogReader {

protected:

    int PIN_SIG;   // Analog-PIN zum auslesen 
    int PIN_GND;   // Optional für GND
    int PIN_VCC;   // Optional für VCC
    int analog_in;
    int analog_merker;

public:

    AnalogReader(int SIG, int VCC = 0, int GND = 0) {
        PIN_SIG = SIG;
        PIN_VCC = VCC;
        PIN_GND = GND;
    }

    void setup() {

        if (PIN_GND) {
            pinMode(PIN_GND, OUTPUT);
            digitalWrite(PIN_GND, LOW);
        }
        if (PIN_VCC) {
            pinMode(PIN_VCC, OUTPUT);
            digitalWrite(PIN_VCC, HIGH);
        }
        update();
    }

    void update() {
        analog_in = analogRead(PIN_SIG);
    }

    int value(int min = 0, int max = 1023) {
        return map(analog_in, 0, 1023, min, max);
    }

    bool trim(int react = 1) {
        update();
        if (abs(analog_merker-analog_in) > react) { 
            analog_merker = analog_in;
            return true;
        }
        return false;
    }

};