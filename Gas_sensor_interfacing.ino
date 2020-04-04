#define gasPin A0
#define tdelay 1000
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(gasPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(analogRead(gasPin));
delay(tdealy);
}
