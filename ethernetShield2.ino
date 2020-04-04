#include <NewPing.h>

//Interfacingn the ultrasonic sensor 
//Basic
#define TRIGGER_PIN 8; //pin 8 connect to trigger
#define ECHO_PIN 9; //pin 9 connect to echo
#define MAX_DISTANCE 200;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//defining basically
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
delay(50); 
unsigned int uS = sonar.ping();
Serial.print("Ping: ");
Serial.print(uS / US_ROUNDTRIP_CM); 
Serial.println("cm");
}
