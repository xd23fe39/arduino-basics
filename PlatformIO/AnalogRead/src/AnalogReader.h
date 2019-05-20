class AnalogReader {

protected:

    int PIN_SIG = A2;   // Analog-PIN zum auslesen
    int PIN_GND = A0;   // Optional für GND
    int PIN_VCC = A4;   // Optional für VCC
    int analog_in;
    int analog_merker;

public:

    void setup(int SIG, int VCC = 0, int GND = 0) {

        PIN_SIG = SIG;
        PIN_VCC = VCC;
        PIN_GND = GND;
        if (GND) {
            pinMode(PIN_GND, OUTPUT);
            digitalWrite(PIN_GND, LOW);
        }
        if (VCC) {
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