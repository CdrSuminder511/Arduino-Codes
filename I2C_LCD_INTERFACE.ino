/* This is code for interfacing I2C lCD with arduino done on 03-04-2020
   I2C LCD - LCM1602 IIC V1
   20x4
   Arduino SDA A4
   Arduino SCL A5
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int const c_i2c_lcd_address = 0x3F; //(Scanned from the i2c scanner code)

LiquidCrystal_I2C lcd(c_i2c_lcd_address, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd
  // Print a message to the LCD
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(2, 1);
  lcd.print("test i2c lcd");
  lcd.setCursor(0, 2);
  lcd.print("working good");
  lcd.setCursor(2, 3);
  lcd.print("ready to begin!!");
}


void loop()
{
}
