#include <QTRSensors.h>

/*
 * PINS:
 * Lines: D7 (left), A0 (center), D6 (right)
 * Distance: A2 (front), A3 (front left), A1 (front right),
 * A5 (back left), A4 (back right).
 */
unsigned char linePins[] = {7, 14, 6};
QTRSensorsRC lineSensors(linePins, 3);

void setup();
void loop();

uint16_t lineValues[3];
uint16_t distanceValues[5];

void setup()
{
    Serial.begin(115200);
}

void loop() 
{
    if (Serial.available() > 0) {
	char cmd = Serial.read();
        if (cmd == 'l') {
	    // Read line sensors.
	    lineSensors.read(lineValues);

	    // Send
	    Serial.write((uint8_t *)lineValues, 2*3);
	} 
	else if (cmd == 'd') {
	    // Read infrared/distance sensors
	    distanceValues[0] = analogRead(A2);
	    distanceValues[1] = analogRead(A3);
	    distanceValues[2] = analogRead(A1);
	    distanceValues[3] = analogRead(A5);
	    distanceValues[4] = analogRead(A4);

	    // Send
	    Serial.write((uint8_t *) distanceValues, 2*5);
	}
    }
}
