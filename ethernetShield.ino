#include<UIPEthernet.h>
byte mac[] = { 0x54, 0x34, 0x41, 0x30, 0x30, 0x31 };  
EthernetClient client; 
char server[] = "gurwinder.bugs3.com"; // IP Adres (or name) of server to dump data to
int  interval = 5000; // Wait between dumps 
void setup() {   
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  Serial.begin(9600); 
  Ethernet.begin(mac); 
  Serial.println("Tweaking4All.com - Temperature Drone - v2.0"); 
  Serial.println("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
  Serial.print("IP Address        : "); 
  Serial.println(Ethernet.localIP());   
  Serial.print("Subnet Mask       : "); 
  Serial.println(Ethernet.subnetMask());  
  Serial.print("Default Gateway IP: "); 
  Serial.println(Ethernet.gatewayIP());   
  Serial.print("DNS Server IP     : ");
  Serial.println(Ethernet.dnsServerIP());
  }
//  http://gurwinder.bugs3.com/index1.php?txt_send=suminder&txt_send1=singh
void loop()
{
  // if you get a connection, report back via serial: 
  if (client.connect(server, 80))
  { 
    Serial.println("-> Connected"); 
    // Make a HTTP request:
    digitalWrite(3,HIGH);
    digitalWrite(5,LOW);
    client.print( "GET /index1.php?"); 
    client.print("txt_send=");   
    client.print( "1" );   
    client.print("&&");   
    client.print("txt_send1=");   
    client.print( "1" );   
    client.println( " HTTP/1.1");    
    client.print( "Host: " );  
    client.println(server);  
    client.println( "Connection: close" );  
    client.println();  
    client.println();   
    client.stop();  
  }  
  else
  {    
    // you didn't get a connection to the server: 
    Serial.println("--> connection failed/n"); 
     digitalWrite(5,HIGH);
       digitalWrite(3,LOW);
    
    }  
    delay(interval);
  }
  



