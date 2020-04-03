/*
   THIS CODE IS FOR TESTING THE I2C COMMUNICATION WITH 24C02

   SDA SET AT PIN A4
   SCL SET ST PIN A5

*/

#define i2c_sda A4
#define i2c_scl A5

#define c_device_address 0xA0     // NOTE: device address is 0x50 but since we are sending 7-bbit data so written 0xA0
#define c_memory_location_msb 0x08
#define c_memory_location_lsb 0x12
#define c_write_data 0x10
#define c_delay_6us 20

bool gv_ack;

void f_i2c_initialize()     // Initilize function sets i2c bus pins to high
{
  pinMode(i2c_sda, INPUT);
  pinMode(i2c_scl, INPUT);
  delayMicroseconds(c_delay_6us);
}

void f_start_communication()               // this function generates start sigal for i2c
{
  //  Serial.println("Sending start bbit");
  pinMode(i2c_scl, INPUT);
  delayMicroseconds(c_delay_6us);
  pinMode(i2c_sda, OUTPUT); digitalWrite(i2c_sda, LOW);
  delayMicroseconds(c_delay_6us);
  pinMode(i2c_scl, OUTPUT); digitalWrite(i2c_scl, LOW);
  delayMicroseconds(c_delay_6us);
}

void f_stop_command()
{
  delayMicroseconds(c_delay_6us);
  pinMode(i2c_scl, OUTPUT); digitalWrite(i2c_scl, LOW);
  delayMicroseconds(c_delay_6us);
  pinMode(i2c_sda, OUTPUT); digitalWrite(i2c_sda, LOW);
  delayMicroseconds(c_delay_6us);
  pinMode(i2c_scl, INPUT);
  delayMicroseconds(c_delay_6us);
  pinMode(i2c_sda, INPUT);
  delayMicroseconds(c_delay_6us);
}

void f_send_byte(byte p_data)
{
  //  Serial.println("Sending data bytes");
  for (int i = 8; i > 0; i--)       // sending 8 bbit data
  {
    delayMicroseconds(c_delay_6us);
    pinMode(i2c_scl, OUTPUT); digitalWrite(i2c_scl, LOW);
    delayMicroseconds(c_delay_6us);
    bool bbit = bitRead(p_data, i - 1); // reading the byte bbit by bbit
    pinMode(i2c_sda, OUTPUT); digitalWrite(i2c_sda, bbit);      // and changing the state of the sda line
    //    Serial.println(bbit, BIN);
    delayMicroseconds(c_delay_6us);

    pinMode(i2c_scl, INPUT);
  }
  delayMicroseconds(c_delay_6us);
  pinMode(i2c_scl, OUTPUT); digitalWrite(i2c_scl, LOW);
  delayMicroseconds(c_delay_6us);

  pinMode(i2c_sda, INPUT);
  pinMode(i2c_scl, INPUT);


  while (gv_ack)
  {
    gv_ack = digitalRead(i2c_sda);
  }
  delayMicroseconds(c_delay_6us);
  pinMode(i2c_scl, OUTPUT); digitalWrite(i2c_scl, LOW);
  delayMicroseconds(c_delay_6us);
}


void f_send_device_address()
{
  //Serial.println("Sending device address"); Serial.println(gv_data, HEX);
  f_send_byte(c_device_address);
}

void f_send_device_address_read_command()
{
  byte  lv_address = c_device_address | 0x01;
  //Serial.println("Sending device address"); Serial.println(gv_data, HEX);
  f_send_byte(lv_address);
}

void f_send_memory_location(byte p_location)      // this functions sends the memory location on which to write/read the data
{

  //  Serial.println("Sending Mem location"); Serial.println(gv_data, HEX);
  f_send_byte(p_location);
}

void f_send_data(byte p_data)                 // this function sends the data to write
{
  //  Serial.println(gv_data, HEX);
  //  Serial.println(gv_data);
  f_send_byte(p_data);
}

void f_ack()
{
  pinMode(i2c_sda , OUTPUT); digitalWrite(i2c_sda, LOW);
  delayMicroseconds(c_delay_6us);
  pinMode(i2c_scl, INPUT);
  delayMicroseconds(c_delay_6us);

  pinMode(i2c_scl, OUTPUT); digitalWrite(i2c_scl, LOW);
  delayMicroseconds(c_delay_6us);
  pinMode(i2c_sda, INPUT);
  delayMicroseconds(c_delay_6us);
}

void f_nack()
{
  pinMode(i2c_sda, INPUT);
  delayMicroseconds(c_delay_6us);
  pinMode(i2c_scl, INPUT);
  delayMicroseconds(c_delay_6us);

  pinMode(i2c_scl, OUTPUT); digitalWrite(i2c_scl, LOW);
  delayMicroseconds(c_delay_6us);
  pinMode(i2c_scl, INPUT);
}
byte f_recieve_data()
{
  byte lv_byte;
  for (int i = 8; i > 0; i--)
  {
    pinMode(i2c_scl, OUTPUT); digitalWrite(i2c_scl, LOW);
    delayMicroseconds(c_delay_6us);
    pinMode(i2c_scl, INPUT);
    delayMicroseconds(c_delay_6us);
    pinMode(i2c_sda, INPUT);
    bitWrite(lv_byte, i - 1, digitalRead(i2c_sda));
    delayMicroseconds(c_delay_6us);
  }
  pinMode(i2c_scl, OUTPUT); digitalWrite(i2c_scl, LOW);
  delayMicroseconds(c_delay_6us);
  pinMode(i2c_sda, INPUT);
  f_nack();
  return lv_byte;
}


void f_write_byte(byte p_location_msb, byte p_location_lsb, byte p_data)            // this function produces the write cycle of the i2c
{
  f_i2c_initialize();
  f_start_communication();
  f_send_device_address();
  f_send_memory_location(p_location_msb);
  f_send_memory_location(p_location_lsb);
  f_send_data(p_data);
  f_stop_command();
  delayMicroseconds(c_delay_6us);
}

byte f_read_byte(byte p_location_msb, byte p_location_lsb)            // this function produces the write cycle of the i2c
{
  byte lv_byte;
  f_i2c_initialize();
  f_start_communication();
  f_send_device_address();
  f_send_memory_location(p_location_msb);
  f_send_memory_location(p_location_lsb);

  f_start_communication();
  f_send_device_address_read_command();
  lv_byte = f_recieve_data();
  f_stop_command();
  return lv_byte;
}
void setup()
{
  Serial.begin(9600);
  //  Serial.println("Code Start");

}
void loop()
{
  f_write_byte(c_memory_location_msb, c_memory_location_lsb, c_write_data);
  delay(20);
  Serial.print("Read byte"); Serial.println(f_read_byte(c_memory_location_msb, c_memory_location_lsb), HEX);
  delay(20);
}
