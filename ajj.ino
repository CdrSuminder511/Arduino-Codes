#include <SoftwareSerial.h>
#include <stdlib.h>
int i=0,k=0,x=0;
boolean No_IP=false;
String IP="";
String apiKey = "C4RATE5RES4844UF";
String ssid ="MyFi_154-HOME";
char tmpResp;
String password="jasw@121271";
// connect 10 to TX of Serial USB
// connect 11 to RX of serial USB
SoftwareSerial ser(2, 3); // RX, TX
String inData;
void setup() 
{                
    Serial.begin(9600); 
    ser.begin(9600);
    ser.println("AT+RST"); 
    wifi_init();
}


void check4IP(int t1)
{
  int t2=millis();
  while(t2+t1>millis())
  {
    while(ser.available()>0)
    {
      if(ser.find("WIFI GOT IP"))
      {
        No_IP=true;
      }
    }
  }
}
void get_ip()
{
  IP="";
  char ch=0;
  while(1)
  {
    ser.println("AT+CIFSR");
    while(ser.available()>0)
    {
      if(ser.find("STAIP,"))
      {
        delay(1000);
        Serial.print("IP Address:");
        while(ser.available()>0)
        {
          ch=ser.read();
          if(ch=='+')
          break;
          IP+=ch;
        }
      }
      if(ch=='+')
      break;
    }
    if(ch=='+')
    break;
    delay(1000);
  }
  Serial.print(IP);
  Serial.print("Port:");
  Serial.println(80);
 
}
void connect_wifi(String cmd, int t)
{
  int temp=0,i=0;
  while(1)
  {
    Serial.println(cmd);
    ser.println(cmd); 
    while(ser.available())
    {
      if(ser.find("OK"))
      {
      i=8;
      }
     
    }
    delay(t);
    if(i>5)
    break;
    i++;
  }
  if(i==8){
  Serial.println("OK");}
  else{
  Serial.println("Error");
  connect_wifi(cmd,t);}
}
void wifi_init()
{
      connect_wifi("AT",100);
	  while(ser.available())

	  Serial.write(ser.read());
      connect_wifi("AT+GMR",100);
      connect_wifi("AT+CWMODE=3",100);
      
      
      check4IP(5000);
      if(!No_IP)
      {
        Serial.println("Connecting Wifi....");
        connect_wifi("AT+CWJAP=\"MyFi_154-HOME\",\"jasw@121271\"",7000);         //provide your WiFi username and password here
     // connect_wifi("AT+CWJAP=\"vpn address\",\"wireless network\"",7000);
      }
      else
        {
        }
      Serial.println("Wifi Connected"); 
    if(ser.find("OK")) {

      Serial.println("Connected!");
      get_ip();
    // connect_wifi("AT+CIPMUX=1",1000);
      }
      
}
void loop()
{
  read_data();
}

void read_data() {
  
  
  // TCP connection
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "192.168.43.136"; // api.thingspeak.com
  cmd += "\",80";
  ser.println(cmd);
   
  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }
  while(ser.available())

  delay(100);

  Serial.write(ser.read());

  delay(100);
  // prepare GET string
  String getStr = "GET /insert.php?user=guruji&pass=bin&id=gyan_kahan&timing=se&status=loun";
//  getStr +="&string=";
//  getStr += String("yeshe");
  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);
 // while(ser.available())

//  Serial.write(ser.read());

 // delay(1500);
  if(ser.find(">")){
    ser.print(getStr);
	delay(100);
  
  }
  
  ser.print("+IPD,12:");

  delay(1500);

  String inData = ser.readString();

  Serial.write(ser.read());

  /*.....................Fetching Data Needed..................*/
  int i = ':';   

  while (inData.charAt(i) != ':') // Character before required data starts.

     i++;

     inData = inData.substring(i);

 

     int j = 0;

  while (inData.charAt(j) != 'C') // Character after required data ends.

     j++;

     inData = inData.substring(0, j);

  Serial.print(inData);

    

  delay(3000);

  delay(4000);

 

  ser.println("AT+CIPCLOSE\r\n");

  while(ser.available())

  Serial.write(ser.read());

  delay(100); 
}
