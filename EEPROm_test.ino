#include <LiquidCrystal.h>
#include <EEPROM.h>
const int rs = 5, en = 6, d4 = 7, d5 = 8, d6 = 9, d7 = 10; //LCD pins configuration
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
float value1 = 256.05; //value to store in eeprom
float value2 = 0;
int address1 = 0;        //store eeprom address 
int address2 = 5;
float c_calibration_value = 1;
int const c_button_up = A3;              // BUTTON FOR INCREMENT MOISTURE VALUES
int const c_button_down = A4;            // BUTTON FOR DECREMENT MOISTURE VALUES
void setup()
{
 
lcd.begin(16,2);
lcd.clear();
//EEPROM.put(0, 56);
EEPROM.get(0, value1);
lcd.setCursor(0,0);
//lcd.print(address1);
}

void loop() 
{
  delay(100);
  lcd.clear();
  lcd.print(value1);
     if (digitalRead(c_button_up) == 0) 
   {
    value1 += c_calibration_value;
   }
   EEPROM.put(0, value1);
    
   
}
