//*********Some Notes********
//Ping time is the duration for the wave to travel from SONAR and reflect back
#include <Servo.h> 
#include <SoftwareSerial.h>
int sensor1State=0;
String apiKey = "T5YMSXA8M5K0BNX0";
int i=1;
boolean No_IP=false;
bool s_loop=false;
String IP="";
SoftwareSerial ser(2, 3 ); // RX, TX
int trigPin=10;            //Triggr pin for Ultasonic
int echoPin=11;            //Echo Pin of Ultrasonic
int servoControlPin=9;     //Pin for servo control
float pingTime;            //Variables from now ping time
float distance;      // to acquire target distance
float speedOfSound=340.29; //Speed of sound in meters per second 
float servoAngle;          //to control the servo anle
int ledPin = 13;           //Pin for led
long duration;
Servo myServo;           //name of servo
 
void setup() {             //initialisations
 
  Serial.begin(9600);      //Setting up serial com and baud rate 
  ser.begin(9600);  //Server baud rate settingṀ
  pinMode(servoControlPin, OUTPUT); //set servo pin as poutput
  pinMode(trigPin, OUTPUT);         //set trigger pin as output  
  pinMode(echoPin, INPUT);          //set echopin as input 
  pinMode(ledPin, OUTPUT);          //set led pin as output
  myServo.attach(servoControlPin);  //servo pin attached to Pin D6
  ser.println("AT+RST");
  wifi_init();                       //Function to connect to wifi
}
void check4IP(int t1){int t2=millis();while(t2+t1>millis()){while(ser.available()>0){if(ser.find("WIFI GOT IP")){No_IP=true;}}}}
void connect_wifi(String cmd, int t)
{
  int temp=0,i=0;
  while(1)
  { ser.println(cmd); 
    while(ser.available()){if(ser.find("OK")){i=8;}}
    delay(t);
    if(i>5)
    break;
    i++;
  }
  if(i==8){Serial.println(cmd+" OK");}else{connect_wifi(cmd,t);}
}
void get_ip()
{ 
    IP="";char ch=0;while(1){ser.println("AT+CIFSR");
    while(ser.available()>0)
    {
      if(ser.find("STAIP,")){delay(1000); Serial.print("IP Address:");while(ser.available()>0){ch=ser.read();if(ch=='+')break;IP+=ch;}}
      if(ch=='+')
      break;
    }
    if(ch=='+')
    break;
    delay(1000);
  }Serial.print(IP);Serial.print("Port:");Serial.println(80);
}

void wifi_init()
{   connect_wifi("AT+RST",100);connect_wifi("AT",100);
    while(ser.available())
    Serial.write(ser.read());// connect_wifi("AT+CIPMUX=1",1000);  
    connect_wifi("AT+GMR",100); connect_wifi("AT+CWMODE=3",100);check4IP(5000);
    if(!No_IP)
    {
    connect_wifi("AT+CWJAP=\"JioFi_154HOME\",\"S@a7bbc2cb57\"",7000);}if(ser.find("OK")) //{lcd.clear(); lcd.println("Connected!");
    Serial.println("Connected!");
    s_loop=true;get_ip();
    }
      
 
void loop() {
  String state1=String(sensor1State);
  int i=analogRead(0);
  sensor1State = i; 
//****************Sending Pulses to SONAR************************************

  
//**************LED Blinking************************************************
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(1000);
  
  digitalWrite(ledPin, HIGH);
  delay(250);
  digitalWrite(ledPin, LOW);
  delay(250);
  digitalWrite(ledPin, HIGH);  
  delay(250);
  
  digitalWrite(ledPin, LOW);
  delay(500);

  // rotates the servo motor from 15 to 165 degrees
  for(int j=0;j<=180;j++){  
  myServo.write(j);
  delay(30);
  distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  
  Serial.print(j); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }
  // Repeats the previous lines from 165 to 15 degrees
  for(int j=180;j>=0;j--){  
  myServo.write(j);
  delay(30);
  distance = calculateDistance();
  Serial.print(j);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  }


  
    // TCP connection
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  ser.println(cmd);
  Serial.println(cmd);
   
  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }
  
  // prepare GET string
  String getStr = "GET /update?api_key=";
  getStr += apiKey;

  getStr +="&field1=";
  getStr += String(state1);
  getStr += "\r\n\r\n";

  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);
  Serial.println(cmd);

  if(ser.find(">")){
    ser.print(getStr);
    Serial.print(getStr);
  }
  else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }
  delay(100);
}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}


