#include <Arduino.h>
#include <SoftwareSerial.h>
#include <QTRSensors.h>
void setup();
void loop();
#line 1 "src/sketch.ino"
//#include <SoftwareSerial.h>
//#include <QTRSensors.h>

// SYNC_PIN and serial tx are used for communication with Beaglebone PRU.
// Important: serial rx is not physically connected since communication is one
// way, but it is still reserved for the SoftwareSerial instance.
#define SYNC_PIN 9
SoftwareSerial bbSerial(7, 8);

// 14 = left, 15 = center, 16 = right.
unsigned char linePins[] = {14, 15, 16};
QTRSensorsRC lineSensors(linePins, 3);

void setup()
{
    Serial.begin(115200);

    bbSerial.begin(115200);
    pinMode(SYNC_PIN, OUTPUT);
    digitalWrite(SYNC_PIN, LOW);
}

void loop() {
    uint16_t distanceValues[5];
    // Read infrared/distance sensors (front = A3, back right = A7)
    distanceValues[0] = analogRead(A3);
    distanceValues[1] = analogRead(A4);
    distanceValues[2] = analogRead(A5);
    distanceValues[3] = analogRead(A6);
    distanceValues[4] = analogRead(A7);

    // Read line sensors.
    uint16_t lineValues[3];
    lineSensors.read(lineValues);

    // Signal to PRU that next slice of readings are about to be transmitted.
    digitalWrite(SYNC_PIN, HIGH);
    digitalWrite(SYNC_PIN, LOW);

    // Send values.
    for (int i = 0; i < 5; i++) {
        bbSerial.write(highByte(distanceValues[i]));
        bbSerial.write(lowByte(distanceValues[i]));
    }
    for (int i = 0; i < 3; i++) {
        bbSerial.write(highByte(lineValues[i]));
        bbSerial.write(lowByte(lineValues[i]));
    }
}
