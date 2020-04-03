#include <Wire.h>

#define eeprom 0xA0 //defines the base address of the EEPROM

void setup() 
{
  Wire1.begin(); //creates a Wire1 object
  Serial1.begin(9600);

  unsigned int address = 0; //first address of the EEPROM
  Serial1.println("We write the zip code 22222, a zip code");
  for (address = 0; address < 5; address++)
    writeEEPROM(eeprom, address, '2'); // Writes 22222 to the EEPROM

  for (address = 0; address < 5; address++)
  {
    Serial1.print(readEEPROM(eeprom, address), DEC);
  }
}

void loop() {
  /*there's nothing in the loop() function because we don't want the arduino to
    repeatedly write the same thing to the EEPROM over and over.
    We just want a one-time write, so the loop() function is avoided with EEPROMs.*/
}

//defines the writeEEPROM function
void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data )
{
  Wire1.beginTransmission(deviceaddress);
  Wire1.write((int)(eeaddress >> 8));      //writes the MSB
  Wire1.write((int)(eeaddress & 0xFF));    //writes the LSB
  Wire1.write(data);
  Wire1.endTransmission();
}

//defines the readEEPROM function
byte readEEPROM(int deviceaddress, unsigned int eeaddress )
{
  byte rdata = 0xFF;
  Wire1.beginTransmission(deviceaddress);
  Wire1.write((int)(eeaddress >> 8));      //writes the MSB
  Wire1.write((int)(eeaddress & 0xFF));    //writes the LSB
  Wire1.endTransmission();
  Wire1.requestFrom(deviceaddress, 1);
  if (Wire1.available())
  {
  rdata = Wire1.read();
  }
  return rdata;
}
