#include <SoftwareSerial.h>

SoftwareSerial bbSerial(5, 6);  // 5 = RX, 6 = TX
void setup()
{
    bbSerial.begin(9600);
}

void loop()
{
    for (int i = 0; i < 255; i++) {
        bbSerial.write(i);
        if (i % 4 == 0) bbSerial.write('\n');
        delay(100);
    }
}
