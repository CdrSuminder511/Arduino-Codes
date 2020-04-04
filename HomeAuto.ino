int D0=0; //Data pins 0 of DTMF Decoder
int D1=1; //Data pins 1 of DTMF Decoder
int D2=2; //Data pins 2 of DTMF Decoder
int D3=3; //Data pins 3 of DTMF Decoder
int Relay1=10;
int Relay2=11;
int Relay3=12;
int Relay4=13;
void setup()
{
 pinMode(Relay1,OUTPUT);
 pinMode(Relay2,OUTPUT);
 pinMode(Relay3,OUTPUT);
 pinMode(Relay4,OUTPUT);
 digitalWrite(Relay1,HIGH);
 digitalWrite(Relay2,HIGH);
 digitalWrite(Relay3,HIGH);
 digitalWrite(Relay4,HIGH);
}
void loop() 
{
  
        // When 0 pressed : 0 0 0 0 (Turning all the relays to off state
  if (digitalRead(D3)==0 && digitalRead(D2)==0 && digitalRead(D1)==0 && digitalRead(D0)==0 )  
  {
     digitalWrite(Relay1,HIGH);
     digitalWrite(Relay2,HIGH);
     delay(200);
  }
      // When 1 pressed : 0 0 0 1
  if (digitalRead(D3)==0 && digitalRead(D2)==0 && digitalRead(D1)==0 && digitalRead(D0)==1 )  
  {
     digitalWrite(Relay1,LOW); // Turning the Relay1 ON state
     delay(200);
  }
      // When 2 pressed : 0 0 1 0
  if (digitalRead(D3)==0 && digitalRead(D2)==0 && digitalRead(D1)==1 && digitalRead(D0)==0 )  
  {
     digitalWrite(Relay2,LOW); // Turning the Relay2 ON state
     delay(200);
  }
      // When 3 pressed : 0 0 1 1
  if (digitalRead(D3)==0 && digitalRead(D2)==0 && digitalRead(D1)==1 && digitalRead(D0)==1 )  
  {
     digitalWrite(Relay3,LOW); // Turning the Relay3 ON state
     delay(200);
  }
       // When 4 pressed : 0 1 0 0
  if (digitalRead(D3)==0 && digitalRead(D2)==1 && digitalRead(D1)==0 && digitalRead(D0)==0 )  
  {
     digitalWrite(Relay4,LOW); // Turning the Relay4 ON state
     delay(200);
  }
       // When 5 pressed : 0 1 0 1
  if (digitalRead(D3)==0 && digitalRead(D2)==1 && digitalRead(D1)==0 && digitalRead(D0)==1 )  
  {
     digitalWrite(Relay1,HIGH); // Turning the Relay1 OFF state
     delay(200);
  }
      // When 6 pressed : 0 1 1 0
  if (digitalRead(D3)==0 && digitalRead(D2)==1 && digitalRead(D1)==1 && digitalRead(D0)==0 )  
  {
     digitalWrite(Relay2,HIGH); // Turning the Relay2 OFF state
     delay(200);
  }
      // When 7 pressed : 0 1 1 1
  if (digitalRead(D3)==0 && digitalRead(D2)==1 && digitalRead(D1)==1 && digitalRead(D0)==1 )  
  {
     digitalWrite(Relay3,HIGH); // Turning the Relay3 OFF state
     delay(200);
  }
      // When 8 pressed : 1 0 0 0
  if (digitalRead(D3)==1 && digitalRead(D2)==0 && digitalRead(D1)==0 && digitalRead(D0)==0 )  
  {
     digitalWrite(Relay4,HIGH); // Turning the Relay4 OFF state
     delay(200);
  }
}
