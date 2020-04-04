void setup() {
Serial.begin(9600);
}

void loop() {
float ldr = analogRead(A0);
float smokeSensor = analogRead(A1);
Serial.print("connected"); 
Serial.println("LDR value:-");
Serial.print(ldr);
Serial.print("Smoke Sensor value:-");
Serial.print(smokeSensor);
delay(1000);
}
