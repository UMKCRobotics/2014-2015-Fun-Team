#include <SoftwareSerial.h>

#define SYNC_PIN 4
SoftwareSerial bbSerial(5, 6);  // 5 = RX, 6 = TX

void setup()
{
    bbSerial.begin(9600);
    pinMode(SYNC_PIN, OUTPUT);
    digitalWrite(SYNC_PIN, LOW);
}

void loop()
{
    static int value = 0;

    digitalWrite(SYNC_PIN, HIGH);
    delay(10);
    digitalWrite(SYNC_PIN, LOW);

    for (int i = 0; i < 4; i++) {
        bbSerial.write(highByte(value));
        bbSerial.write(lowByte(value));
        value++;
        if (value > 1023) value = 0;
    }
    delay(100);
}
