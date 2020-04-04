int in = A0;

void setup() {
  Serial.begin(9600);   //Set the baud rate of the comunication
  pinMode(in,INPUT);    //Define the pin as input
}

void loop() {
  //Read the analog value
  float val = analogRead(in);
  
  //Divide by 205 to obtain a range from 0 to 5V
  float val2 = val/205;
  
  //Use serial.print to send the data in a "text" format
  Serial.print(val2);
  delay(400);//Small delay between each data send 
}
