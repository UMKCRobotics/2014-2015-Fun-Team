#include <Arduino.h>
#include <RedBot.h>
#include <RedBotSoftwareSerial.h>
void setup();
void loop();
#line 1 "src/sketch.ino"
//#include <RedBot.h>
//#include <RedBotSoftwareSerial.h>

//RedBotSoftwareSerial mySerial = RedBotSoftwareSerial(A0, A1); // RX, TX
RedBotSoftwareSerial mySerial;
//Receiver Board - Just gets motor commands

int RED, YELLOW, GREEN;
RedBotMotors motor;


int speed;
int turnSpeed;
int reverseTurnSpeed;
void setup()  
{
  RED = A5;
  YELLOW = 10;
  GREEN = 11;
  // Open serial communications and wait for port to open:
  mySerial.begin(9600);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  speed = 80;
  turnSpeed = 80;
  reverseTurnSpeed = -100;
  motor.brake();
}

void loop() // run over and over
{

  //int incoming = mySerial.available();

  int sentValue = mySerial.read();
  if (sentValue > 0)
  {
      switch(sentValue) {
       case 1:
         //FullStop
         motor.brake();
         break;
       case 2:
         //RedOn
         digitalWrite(RED, HIGH);
         break;
       case 3:
         //YellowOn
         digitalWrite(YELLOW, HIGH);
         break;
       case 4:
         //GreenOn
         digitalWrite(GREEN, HIGH);
         break;
       case 5:
         //RedOff
         digitalWrite(RED, LOW);
         break;
       case 6:
         //YellowOff
         digitalWrite(YELLOW, LOW);
         break;
       case 7:
         //GreenOff
         digitalWrite(GREEN, LOW);
         break;
       case 8:
         //GoForward
         motor.drive(speed);
         break;
       case 9:
         //TurnRight
         motor.leftDrive(reverseTurnSpeed);
         motor.rightDrive(turnSpeed);
         break;
       case 10:
         //TurnLeft
         motor.leftDrive(turnSpeed);
         motor.rightDrive(reverseTurnSpeed);
         break;
      case 70:
	//Test case
	mySerial.write(0xF);
	break;
     }
  }
}
