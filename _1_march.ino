#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <stdlib.h>
//LCD INIT
LiquidCrystal lcd(9,8,7,6,5,4);
// for first button
int b1pin=A0;
// for second button
int b2pin=A1;
//For esp
boolean No_IP=false;
String IP="";
SoftwareSerial ser(2,3);//Rx, Tx
bool fine=false,pre_fine=false;
int hours = 1; // start hours
int minutes = 0; //start min
int seconds = 5; //start seconds
//initlize
String GET, URL,HTTP,getStr;
int r_id=0;
bool pre_insert=false;
bool s_loop=true;
// LED 
int ledState=LOW;
const int l1 =  11;
const int l2 =  12;  
const int ledPin =  13;         // the number of the LED pin
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 1000;           // interval at which to blink (milliseconds)
void misc(String id)
{
  GET ="GET ";
  URL ="/recieve.php?id="+id;
  URL+="\r\n\r\n";
  Serial.print(URL);
  HTTP ="/HTTP/1.1";
  getStr = "GET /insert.php?user=admin&pass=admin&id="+id+"&timing=&status=Active";
  getStr += "\r\n\r\n";
}
void setup() 
{  lcd.begin(16, 1);pinMode(ledPin, OUTPUT);pinMode(l1, OUTPUT);pinMode(l2, OUTPUT);
   pinMode(b1pin,INPUT);pinMode(b2pin,INPUT);Serial.begin(9600);ser.begin(9600);ser.println("AT+RST");wifi_init();
}
void blin(bool act)
{
  if(act)
  {
   unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
      lcd.println("Press Button for Online! Device");
    } else {
      ledState = LOW;
      lcd.clear();
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
  }
}
void check4IP(int t1){int t2=millis();while(t2+t1>millis()){while(ser.available()>0){if(ser.find("WIFI GOT IP")){No_IP=true;}}}}
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
  if(i==8){lcd.clear();lcd.print(cmd+" OK");Serial.println(cmd+" OK");}else{connect_wifi(cmd,t);}
}
void wifi_init()
{   connect_wifi("AT+RST",100);connect_wifi("AT",100);
    while(ser.available())
    Serial.write(ser.read());// connect_wifi("AT+CIPMUX=1",1000);  
    connect_wifi("AT+GMR",100); connect_wifi("AT+CWMODE=3",100);check4IP(5000);if(!No_IP){ connect_wifi("AT+CWJAP=\"GNDU_JLD1\",\"a7bbc2cb57\"",7000);}if(ser.find("OK")) {lcd.clear(); lcd.println("Connected!");Serial.println("Connected!");s_loop=true;get_ip();}
}       
void loop()
{
if(s_loop)
{  
blin(true);
int  b1state=digitalRead(b1pin);
int  b2state=digitalRead(b2pin);
//Serial.print(b1state);
//Serial.print(b2state);
  if(b2state==HIGH){misc("s11"); insert_data();}
  if(b1state==HIGH)
  {  
    if(pre_fine)
    {
    lcd.clear();
    lcd.println("Online client!!!");
    delay(1000);
    lcd.clear();
    lcd.println("Wait for triger!!!");
    fine=true;
    }
    else
    {
    lcd.clear();
    lcd.print("Not Registed!!!!!!!");
    }
  }
  if(fine)
  {
  read_data();
  }
}
else
{
  lcd.clear();
  lcd.print("Connection problem!!!!");  
}
}
void insert_data(){ 
  if(pre_insert)
  {
  lcd.clear();
  lcd.print("Already Registerd!!!!");  
  }
  else
  {
  String cmd = "AT+CIPSTART=\"TCP\",\"";cmd += "192.168.43.136";cmd += "\",80";ser.println(cmd);
  if(ser.find("Error")){Serial.println("AT+CIPSTART error");return;}
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);
  if(ser.find(">")){ser.print(getStr);lcd.clear();lcd.println("Registerd device!");digitalWrite(l1,HIGH);pre_fine=true;pre_insert=true;ser.println("Registerd device!");}else{ser.println("AT+CIPCLOSE");Serial.println("AT+CIPCLOSE");}
  delay(1500);
  }
}
void read_data() {
  while(ser.available()){Serial.write(ser.read());}
  delay(2500);
  ser.println( "AT+CIPSTART=\"TCP\",\"192.168.43.136\",80\r\n");
  delay(3500);
  while(ser.available()){Serial.write(ser.read());}
  delay(3500);
  //..............................................
  ser.println("AT+CIPSEND="+String(GET.length()+URL.length()));
  delay(3500);
  while(ser.available()){Serial.write(ser.read());}
  delay(2500);
  ser.println(GET+URL);
  delay(2000);
  //..........................................
  ser.println(HTTP+"Host:192.168.43.136:80");
  String inData;
  while(ser.available())
  { 
     inData=ser.readString();
  }
  Serial.print(inData);
  delay(1500);
  ser.println("AT+CIPCLOSE");
  delay(4500);
  while(ser.available()){Serial.write(ser.read());}
  delay(4500);
  digitalWrite(l2,HIGH);
  math(inData);
}
void math(String s)
{
 // Serial.print(inData);
  Serial.println("Welcome in meth");
  Serial.println(s.length());
  for(int x=0;x<=s.length();x++)
  {
    Serial.println("Welcome in loop");
    if(s.charAt(x) == '>' && s.charAt(x+1)=='[' && s.charAt(x+10)==']')
    {
      Serial.println("Welcome in conditiion");
      s=s.substring(x+2,x+9);
      Serial.println(s);
      lcd.clear();
      lcd.print(s);
      fine=false;
      break;
     }
  } 
  if(fine==false)
  {
    timer(s);
  }
}
void timer(String times)
{
Serial.print(times);
hours =   times.substring(0,1).toInt(); // start hours
minutes = times.substring(3,4).toInt(); //start min
seconds = times.substring(6,7).toInt(); //start seconds
// lcd.begin(16, 2);
// lcd.scrollDisplayLeft();
delay(150);while (hours > 0 || minutes > 0 || seconds >= 0) {(hours < 10) ? Serial.print("0") : NULL;(minutes < 10) ? Serial.print("0") : NULL;(seconds < 10) ? Serial.print("0") : NULL;
Serial.println(String(hours)+":"+String(minutes)+":"+String(seconds)); stepDown(); lcd.setCursor(5, 1);lcd.clear();lcd.print(String(hours)+":"+String(minutes)+":"+String(seconds)); stepDown();delay(1000);delay(1000);}
}
void stepDown(){if (seconds > 0){seconds -= 1;}else{if (minutes > 0) {seconds = 59;minutes -= 1;} else {if (hours > 0) {seconds = 59;minutes = 59;hours -= 1;} else {trigger();}}}}
void trigger() {Serial.println("END "); delay(1000);}
