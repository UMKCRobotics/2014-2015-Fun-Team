#include <QTRSensors.h>

<<<<<<< HEAD
/*
 * PINS:
 * Lines: D7 (left), A0 (center), D6 (right)
 * Distance: A2 (front), A3 (front left), A1 (front right),
 * A5 (back left), A4 (back right).
 */
unsigned char linePins[] = {7, 14, 6};
=======
// SYNC_PIN and serial tx are used for communication with Beaglebone PRU.
// Important: serial rx is not physically connected since communication is one
// way, but it is still reserved for the SoftwareSerial instance.
#define SYNC_PIN 9
SoftwareSerial bbSerial(7, 8);

// 14 = left, 15 = center, 16 = right.
unsigned char linePins[] = {16, 15, 15};
>>>>>>> 8f630a97749f623c7d314c52cacdc63f105dc63b
QTRSensorsRC lineSensors(linePins, 3);

void setup()
{
    Serial.begin(115200);
}

void loop() {
<<<<<<< HEAD
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
	    distanceValues[3] = analogRead(A5);
	    distanceValues[4] = analogRead(A4);

	    // Send
	    //for (int i = 0; i < 5; i++) {
		//Serial.print(distanceValues[i]);
		//Serial.print(' ');
	    //}
	    Serial.write((uint8_t *)distanceValues, 2*5);
	}
=======
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
    // Because left sensor constantly reads too high.
    lineValues[0] /= 3.15;

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
>>>>>>> 8f630a97749f623c7d314c52cacdc63f105dc63b
    }
}

// Temporary code to help with determining line sensor calibration values.
void average() {
    const int average_times = 100;
    unsigned int values[average_times][3];

    for (int i = 0; i < average_times; i++) {
        lineSensors.read(values[i]);
    }

    unsigned long sum[3] = {0};
    for (int i = 0; i < average_times; i++) {
        sum[0] += values[i][0];
        sum[1] += values[i][1];
        sum[2] += values[i][2];
    }
    Serial.print("Averages: ");
    Serial.print(sum[0] / average_times);
    Serial.print(" ");
    Serial.print(sum[1] / average_times);
    Serial.print(" ");
    Serial.print(sum[2] / average_times);
    Serial.print(" ");
    Serial.println("");
}
