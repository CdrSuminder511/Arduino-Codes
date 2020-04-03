#include <Wire.h>

#define device_address 0x50
byte data = 0xAA;
byte rdata;
byte quantity = 1;
byte msb = 0x1A;
byte lsb = 0xAA;

byte f_write(byte wdata)
{
  Wire.beginTransmission(device_address);
  Wire.write(msb);                        //MSB of Memory Location
  Serial.println("write MSB");
  Wire.write(lsb);                        //LSB of Memory Location
  Serial.println("write LSB");
  Wire.write(wdata);
//  Serial.println(wdata, HEX);
  Wire.endTransmission();
  delay(10);
  return wdata;
}
byte f_read()
{
  Wire.beginTransmission(device_address);           //Start I2C communication
  Wire.write(msb);                             //queue MSB of Memory Location
  Serial.println("read MSB");
  Wire.write(lsb);                            //queue LSB of Memory Location
  Serial.println("read LSB");
  Wire.endTransmission();                      // End of I2C transmisssion

  Wire.requestFrom(device_address, quantity);  // Send conrol byte again to retrieve data
  if (Wire.available())
  {
    rdata = Wire.read();
  }
  Serial.println(rdata, HEX);
  delay(10);
  return rdata;
}
void setup()
{
  Serial.begin(9600);
  Wire.begin();
  //  Serial.println("\nI2C Scanner");
  f_write(data);
  delay(10);
  f_read();
  data =  rdata;
  Serial.println(data, HEX);
  Serial.println("");

}


void loop()
{
  /*empty loop press reset  to start again*/
  f_write(data);
  delay(10);
  f_read();
  delay(10);
// while(1) {}
}
