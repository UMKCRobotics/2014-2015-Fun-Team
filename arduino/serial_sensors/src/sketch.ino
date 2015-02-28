#include <QTRSensors.h>

/*
 * PINS:
 * Lines: D7 (left), A0 (center), D6 (right)
 * Distance: A2 (front), A3 (front left), A1 (front right),
 * A4 (back left), A5 (back right).
 */
unsigned char linePins[] = {7, 14, 6};
QTRSensorsRC lineSensors(linePins, 3);

void setup()
{
    Serial.begin(115200);
}

void loop() {
    if (Serial.available() > 0) {
	char cmd = Serial.read();
        if (cmd == 'l') {
	    // Read line sensors.
	    uint16_t lineValues[3];
	    lineSensors.read(lineValues);

	    // Send
	    Serial.write((uint8_t *)lineValues, 2*3);
	    //for (int i = 0; i < 3; i++) {
		//Serial.print(lineValues[i]);
		//Serial.print(' ');
	    //}
        } else if (cmd == 'd') {
	    // Read infrared/distance sensors
	    uint16_t distanceValues[5];
	    distanceValues[0] = analogRead(A2);
	    distanceValues[1] = analogRead(A3);
	    distanceValues[2] = analogRead(A1);
	    distanceValues[3] = analogRead(A4);
	    distanceValues[4] = analogRead(A5);

	    // Send
	    //for (int i = 0; i < 5; i++) {
		//Serial.print(distanceValues[i]);
		//Serial.print(' ');
	    //}
	    Serial.write((uint8_t *)distanceValues, 2*5);
	}
    }
}
