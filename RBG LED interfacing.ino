int redLed      = 12;
int greenLed    = 11;
int blueLed     = 10;
int delayPeriod = 6000;
void setup() {
  // put your setup code here, to run once:
pinMode(redLed,OUTPUT);
pinMode(greenLed,OUTPUT);
pinMode(blueLed,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(redLed,100);
analogWrite(greenLed,0);
analogWrite(blueLed,0);
delay(delayPeriod);

analogWrite(redLed,0);
analogWrite(greenLed,100);
analogWrite(blueLed,0);
delay(delayPeriod);

analogWrite(redLed,0);
analogWrite(greenLed,0);
analogWrite(blueLed,100);
delay(delayPeriod);

analogWrite(redLed,100);
analogWrite(greenLed,20);
analogWrite(blueLed,60);
delay(delayPeriod);

analogWrite(redLed,50);
analogWrite(greenLed,60);
analogWrite(blueLed,0);
delay(delayPeriod);

analogWrite(redLed,100);
analogWrite(greenLed,80);
analogWrite(blueLed,50);
delay(delayPeriod);

analogWrite(redLed,50);
analogWrite(greenLed,60);
analogWrite(blueLed,70);
delay(delayPeriod);

analogWrite(redLed,14);
analogWrite(greenLed,5);
analogWrite(blueLed,20);
delay(delayPeriod);

}
