#include <SoftwareSerial.h>
#include <QTRSensors.h>

// SYNC_PIN and serial tx are used for communication with Beaglebone PRU.
// Important: serial rx is not physically connected since communication is one
// way, but it is still reserved for the SoftwareSerial instance.
#define SYNC_PIN 9
SoftwareSerial bbSerial(7, 8);

unsigned char linePins[] = {6};
QTRSensorsRC lineSensors(linePins, 1);

void setup()
{
    Serial.begin(115200);

    bbSerial.begin(115200);
    pinMode(SYNC_PIN, OUTPUT);
    digitalWrite(SYNC_PIN, LOW);
}

void loop() {
    // FIXME: rewrite so that all sensors are read before sending over serial.
    // Otherwise serial timing could get screwed up on PRU side.

    // Signal to PRU that next slice of readings are about to be transmitted.
    digitalWrite(SYNC_PIN, HIGH);
    digitalWrite(SYNC_PIN, LOW);

    // Read infrared (distance) sensors (on pins A0-A4) and send to beaglebone.
    for (int i = 0; i < 5; i++) {
        // FIXME: this should be a uint16_t, not int.
        int value = analogRead(i);
        bbSerial.write(highByte(value));
        bbSerial.write(lowByte(value));
    }
    // Read line sensors and send to beaglebone.
    unsigned int values[1] = {0};
    lineSensors.read(values);
    bbSerial.write(highByte(values[0]));
    bbSerial.write(lowByte(values[0]));
    // Placeholder.
    for (int i = 0; i < 2; i++) {
        bbSerial.write(highByte(0));
        bbSerial.write(lowByte(0));
    }

    // TODO: remove eventually. This slows everything down for debugging.
    delay(100);
}
