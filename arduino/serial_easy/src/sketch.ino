#define LINE_LEFT 14
#define LINE_RIGHT 16
#define LINE_CENTER 15

#define FRONT A3
#define FRONT_LEFT A4
#define FRONT_RIGHT A5
#define BACK_LEFT A6
#define BACK_RIGHT A7

unsigned char linePins[] = {LINE_LEFT,LINE_CENTER,LINE_RIGHT};

QTRSensorsRC lineSensors(linePins,3);

int lineLeftValue;
int lineRightValue;
int lineCenterValue;

int frontValue;
int frontLeftValue;
int frontRightValue;
int backLeftValue;
int backRightValue;

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	char readValue = Serial.read();
	lineSensors.read
	if(readValue = 'l'){
		Serial.write
		
}
