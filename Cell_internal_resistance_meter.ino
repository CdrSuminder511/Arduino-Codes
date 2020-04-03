#include<LiquidCrystal.h>
int const c_rs = 2, c_en = 3, c_d4 = 4, d5 = 5, d6 = 6, d7 = 7; // Declaring the LCD pins

LiquidCrystal lcd(c_rs, c_en, c_d4, d5, d6, d7);

int const c_voltage_read = A5;    // A0 pin it will read the voltage v1 and v2
int const c_switch = 8;           // Switch connected to pin d2, when pressed it measures the internall resistance
int const c_pfet = 9;             // gate of the P fet is connected to pin D9(Pulled up High when Pfet is off)

int const c_measure_time = 10;

float gv_v1;       // Variable V1 which stores voltage value when the P-FET is OFF
float gv_v2;       // Variable V2 which stores voltage value when P-FET is ON
float gv_result;   // Variable Result which displays the calculated value on LCD

void f_display_lcd()      // this function diplays the result on LCD
{
  lcd.setCursor(0, 1);
  lcd.print("Int. res:- ");
  lcd.print(gv_result);
  Serial.println(gv_result);
}

float f_measure_v1()                     // This function measures the V1 voltage when PFET is off
{
  gv_v1 = analogRead(c_voltage_read);   // read the analog voltage at A0 pin and store in gv_v1
  return gv_v1;
}

void f_switch_on_PFET()            // this function switches on PFET and measures the cell vlotage when lload is connected
{
  digitalWrite(c_pfet, LOW);
  gv_v2 = analogRead(c_voltage_read);
  delay(c_measure_time);
  digitalWrite(c_pfet, HIGH); 
}

float f_calculate_internal_resistance(float lv_v1, float lv_v2)
{
  gv_result = (lv_v1 - lv_v2) / lv_v2;
  return lv_v1, lv_v2;
}

void f_measure_v2()
{
//  if (digitalRead(c_switch) == 0)
  
    f_switch_on_PFET();     // call function which will switch on the P-FET and measure voltage V2
  //}
}

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(c_switch, INPUT);
  pinMode(c_pfet, OUTPUT);
  
  digitalWrite(c_pfet, HIGH);
}

void loop()
{
  Serial.println(f_measure_v1());
  f_measure_v2();  // measures V2 only when switch is pressed
  f_calculate_internal_resistance(gv_v1, gv_v2);
  f_display_lcd();
  while(1){}
}
