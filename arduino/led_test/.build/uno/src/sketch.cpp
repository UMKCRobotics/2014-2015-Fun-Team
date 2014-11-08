#include <Arduino.h>

void setup();
void loop();
#line 1 "src/sketch.ino"

void setup()
{
	pinMode(3, OUTPUT);
}

void loop()
{
	digitalWrite(3,HIGH);
}
