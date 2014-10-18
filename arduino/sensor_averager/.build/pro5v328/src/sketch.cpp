#include <Arduino.h>

void setup();
void loop();
#line 1 "src/sketch.ino"

void setup()
{
	Serial.begin(9600);
	pinMode(A0,OUTPUT);
	pinMode(A1,OUTPUT);
}

void loop()
{
	int leftSensor1 = analogRead(A5);
	int leftSensor2 = analogRead(A4);
	analogWrite(A0,(leftSensor1 + leftSensor2)/2);
	
	int rightSensor1 = analogRead(A6);
	int rightSensor2 = analogRead(A7);
	analogWrite(A1,(rightSensor1+rightSensor2)/2);
	
}
