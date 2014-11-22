#include <SoftwareSerial.h>

SoftwareSerial bbSerial(5, 6);  // 5 = RX, 6 = TX
void setup()
{
    bbSerial.begin(9600);
}

void loop()
{
    for (int i = 1111; i < 9999; i++) {
        bbSerial.print(String(i));
        delay(100);
    }
}
