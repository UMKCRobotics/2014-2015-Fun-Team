#include <SoftwareSerial.h>
#include <QTRSensors.h>

#define SYNC_PIN 9
SoftwareSerial bbSerial(7, 8);  // 7 = RX, 8 = TX

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
    // Signal to PRU that next slice of readings are about to be transmitted.
    digitalWrite(SYNC_PIN, HIGH);
    digitalWrite(SYNC_PIN, LOW);

    // Infrared (distance) sensors.
    for (int i = 0; i < 5; i++) {
        int value = analogRead(i);
        bbSerial.write(highByte(value));
        bbSerial.write(lowByte(value));
    }
    // Line sensors.
    unsigned int values[1] = {0};
    lineSensors.read(values);
    bbSerial.write(highByte(values[0]));
    bbSerial.write(lowByte(values[0]));
    // Placeholder.
    for (int i = 0; i < 2; i++) {
        bbSerial.write(highByte(0));
        bbSerial.write(lowByte(0));
    }

    delay(100);
}
