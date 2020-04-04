
#include <ESP8266WiFi.h>                         //Including the esp library for node-mcu
#include <DHT.h>                                 // Including library for DHT11 Sensor


String apiKey = "IT0V4HJEVYNG1YHI";                       //  Enter your Write API key from ThingSpeak
 
const char *ssid =  "Shubham";  
const char *pass =  "1234567890";
const char* server = "api.thingspeak.com";
                                   //pin where the DHT11 is connected
#define DHTPIN D6  

DHT dht(DHTPIN, DHT11);

WiFiClient client;
 
void setup() 
{
         
       Serial.begin(9600);
       delay(10);
       dht.begin();
     
      
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
      WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
     Serial.println("WiFi connected");
   
}
 
void loop() 
{
  
      float h = dht.readHumidity();
      float t = dht.readTemperature();


Serial.println("Temp.:");
Serial.print(t);
  
Serial.println("Humd.:");
Serial.print(h);
delay(2000);      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }

                       if (client.connect(server,80))                                      //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                            client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                            Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(10000);

}
