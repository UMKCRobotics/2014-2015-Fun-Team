#include <Arduino.h>
#include <RedBot.h>
#include <RedBotSoftwareSerial.h>
void setup();
void loop();
#line 1 "src/sketch.ino"
//#include <RedBot.h>
//#include <RedBotSoftwareSerial.h>

RedBotSoftwareSerial mySerial;

//pin designations
const int lswitch=3;
const int rswitch=9;
const int buttonPin = 11;
const int frsensor = A4;
const int brsensor = A6;
const int ffsensor = A5;

RedBotSensor rlinesensor = RedBotSensor(A7);
RedBotSensor clinesensor = RedBotSensor(A3);
RedBotSensor tlinesensor = RedBotSensor(A2);

// range sensor values
int fr = 0;
int br = 0;
int ff = 0;

// line sensor values
int rline = 0; //Right
int cline = 0; //Center
int tline = 0; //lefT

int rswitchState = 0;
int lswitchState = 0;

int buttonState = 0;
int buttonVal = 0;
int incoming = 0;

void setup() {
pinMode(buttonPin, INPUT_PULLUP);
pinMode(rswitch, INPUT_PULLUP);
pinMode(lswitch, INPUT_PULLUP);
mySerial.begin(38400);
Serial.begin(9600);
}

void loop() {
//

lswitchState = digitalRead(lswitch);
rswitchState = digitalRead(rswitch);


buttonState = digitalRead(buttonPin);
if (buttonState == HIGH) {
buttonVal = 1;
delay(5);
Serial.print("Button Val: ");
Serial.println(buttonVal);
}
else {
delay(5);
Serial.print("Button Val: ");
buttonVal = 0;
Serial.println(buttonVal);

}

Serial.print("Rswitch: ");
Serial.println(rswitchState);

Serial.print("Lswitch: ");
Serial.println(lswitchState);

// Sensor Reads and serial prints
fr = analogRead(frsensor);
delay(5);
ff = analogRead(ffsensor);
delay(5);
br = analogRead(brsensor);
delay(5);
Serial.print("Front sensor: ");
Serial.println(ff);
Serial.print("Forward R Sensor: ");
Serial.println(fr);
Serial.print("Back R Sensor: ");
Serial.println(br);

// Line Sensor Values and Prints

rline = rlinesensor.read();
delay(5);
cline = rlinesensor.read();
delay(5);
tline = rlinesensor.read();
delay(5);


Serial.print("Right Line : ");
Serial.println(rline);
Serial.print("Center Line : ");
Serial.println(cline);
Serial.print("Left Line: ");
Serial.println(tline);

// space.. the final frontier
Serial.println(" ");
delay(200);
//delay(25);
}
