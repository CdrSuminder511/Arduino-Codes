char val;
#define led1 2
#define led2 3
#define led3 4
#define led4 5
#define led5 6
#define led6 7
#define led7 8
#define led8 9
#define led9 13
void setup() 
{
 
Serial.begin(9600);
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);
pinMode(led4,OUTPUT);
pinMode(led5,OUTPUT);
pinMode(led6,OUTPUT);
pinMode(led7,OUTPUT);
pinMode(led8,OUTPUT);
pinMode(led9,OUTPUT);
}

void loop() 
{
 
if (Serial.available())
{
  val = Serial.read();
  Serial.println(val);
  if(val == 'A')
  digitalWrite(led1,HIGH);
  else if(val == 'a')
  digitalWrite(led1,LOW);
  else if(val == 'B')
  digitalWrite(led2,HIGH);
  else if(val == 'b')
  digitalWrite(led2,LOW);
  else if(val == 'C')
  digitalWrite(led3,HIGH);
  else if(val == 'c')
  digitalWrite(led3,LOW);
  else if(val == 'D')
  digitalWrite(led4,HIGH);
  else if(val == 'd')
  digitalWrite(led4,LOW);
  else if(val == 'E')
  digitalWrite(led5,HIGH);
  else if(val == 'e')
  digitalWrite(led5,LOW);
  else if(val == 'F')
  digitalWrite(led6,HIGH);
  else if(val == 'f')
  digitalWrite(led6,LOW);
  else if(val == 'G')
  digitalWrite(led7,HIGH);
  else if(val == 'g')
  digitalWrite(led7,LOW);
  else if(val == 'H')
  digitalWrite(led8,HIGH);
  else if(val == 'h')
  digitalWrite(led8,LOW);
  else if(val == 'I')
  digitalWrite(led9,HIGH);
  else if(val == 'i')
  digitalWrite(led9,LOW);
  }

}
