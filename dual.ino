char input;
void forward()
{
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
}
void backward()
{
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
}
void right()
{
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
}
void left()
{
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
}
void stop1()
{
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
}
void setup() 
{
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
}

void loop() 
{
  int i,j;
  i=analogRead(A0);
  j=analogRead(A1);
  Serial.println("LPG DETECTION:");
  Serial.println(i);
  Serial.println("LIGHT:");
  Serial.println(j);
        delay(500);
if(Serial.available()>0)  
  {  
    input= Serial.read();  
    if(input=='m')  
    {  
        forward();
       
    }  
    else if(input=='n')  
    {  
       backward();
       
    }    
    else if(input=='o')  
    {  
       left();
       
    }    
    else if(input=='p')  
    {  
       right();
       
    }    
    else if(input=='x')  
    {  
       stop1();
      
    }    
    
}
}
