/*
   AIR FLOW METER
   This code includes taking values from mechanical sensors and using that values to calculate certain parameter.
   The Circuit:
     - Sensors used are
                      LM35- Temperature Sensor.(DATASHEET: http://www.ti.com/lit/ds/symlink/lm35.pdf )
                      Absolute Pressure Transducer.(DATASHEET & SPECIFICATIONS: https://www.baumer.com/ch/en/product-overview/process-sensors/pressure-measurement/for-industrial-applications/for-air-and-gas-applications/ctx/p/35469 )
                      Differential Pressure Transducer.( DATASHEET: http://www.autrol.com/wp-content/uploads/2017/10/catalogue_pressure-transmitter_APT3100.pdf.pdf)
     - APT and DPT are HART protocol operated device so they are having an output range from 4 mA to 20 mA.
     - LM35 is a analog temperature sensor with 10mV rise for 1°C change in temperature.
     - Controller used in this product is STM32 Maple Mini(DATASHEET & SPECIFICATIONS: https://wiki.stm32duino.com/index.php?title=Maple_Mini)
     - Maple mini is having a 12-bit ADC with voltage tolerance upto 3.3Volts.
     - To convert the output from APT and DPT into voltage levels a resistance combination of V=IR is used, with R = 165Ω. Generating voltage to range from 660 mV to 3300 mV.
     - 20x4 LCD is also used to display all the parameters which are: Ambient temperature(°C),Ambient Pressure(hectoPascal),Differential Pressure(hectoPascal) and Air Flow Rate in Kg/sec.
     - 12 bit ADC line is reduced to 10 bit ADC line for cutting out or errors and noise.
     - Mapping is done between ADC values and the output value levels.
                      Calculations:
                                      3.3 Volts or 3300 milliVolts at input = 1023 value of ADC (Step Scale)
                                                  for 1 milliVolts          =       1024/3300
                          for (minimum value of input range) 660 milliVolts =       (660*1024)/3300 = 204.8
                          {204.8} here comes out to be the lower level of  input range to ADC.
     - This above calculation is true for both DPT and APT for mapping the values.
     - Smoothning and averaging of the values is done precisely to get appropriate results.


    created 2019
    by Gagandeep Singh
       Kush Singla
    MONTECH INSTRUMENTS
*/
#include <LiquidCrystal.h>

const int lm35_pin = PA7;                                                                         // pin Assignment
const int AmbPressure_pin = PB0;                                                                  // pin Assignment
const int pitOutPressure_pin = PB1;                                                               // pin Assignment

const int en = PB8;
const int d4  = PB7;
const int d5  = PB6;
const int d6  = PB5;
const int d7  = PB4;
const int rs = PB3;

const int c_fullScale = 1023;
const int c_adc_wait = 1;
const byte numReadings_ambPressure = 20;                                                                       // number of times reading is taken
const byte numReadings_temp = 20;                                                                     // number of times reading is taken
const byte numReadings_pitout = 20;                                                                     // number of times reading is taken
unsigned int readings_ambPressure[numReadings_ambPressure];                                                                // readings from the analog input
unsigned int readings_temp[numReadings_temp];                                                              // readings from the analog input
unsigned int readings_pitout[numReadings_pitout];                                                              // readings from the analog input
byte readIndex_ambPressure = 0;                                                                                // index of the current reading
byte readIndex_temp = 0;                                                                              // index of the current reading
byte readIndex_pitout = 0;                                                                              // index of the current reading
unsigned int total_temp = 0;                                                                          // running total
unsigned int total_ambPressure = 0;                                                                            // running total
unsigned int total_pitout = 0;                                                                          // running total
unsigned int average_temp = 0;                                                                        // average
unsigned int average_ambPressure = 0;                                                                          // average
unsigned int average_pitout = 0;                                                                        // average
float gv_temp_actual;
unsigned int gv_ambPressure_actual;
unsigned int gv_pitOutPressure_actual = 0;
const int Pn = 101325, Tkn = 298;                                                                                      // integer constant values
const float R_value = 287.05;                                                                                          // float constant values
float gv_flowRate;
float gv_K_1, gv_K_2, gv_K_3;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                                                                             // Defining an instance of Liquid Crystal function and passing values

void setup()
{
  Serial.begin(9600);
  pinMode(lm35_pin, INPUT_ANALOG);                                                                                     // Analog Read from  gv_temp_actual erature sensor
  pinMode(AmbPressure_pin, INPUT_ANALOG);                                                                              // Analog Read from pressure sensor
  pinMode(pitOutPressure_pin, INPUT_ANALOG);                                                                           // Analog Read from Delta pressure sensor

  // clearing the readings in integer array
  for (int thisReading = 0; thisReading < numReadings_ambPressure; thisReading++)
  {
    readings_ambPressure[thisReading] = 0;
  }
  // clearing the readings in integer array
  for (int thisReading = 0; thisReading < numReadings_temp; thisReading++)
  {
    readings_temp[thisReading] = 0;
  }
  // clearing the readings in integer array
  for (int thisReading = 0; thisReading < numReadings_pitout; thisReading++)
  {
    readings_pitout[thisReading] = 0;
  }

  lcd.begin(20, 4);                                                                                                    // Begin 20x4 LC display
  lcd.print("       MONTECH      ");
  delay(1000);
  lcd.clear();                                                                                                         // Clearing LC display
  delay(100);
  lcd.print("      AIRMETER      ");

}

void loop()
{
  // Calling the temperature function
  f_temp();
  // Calling the ambient pressure function
  f_ambPressure();
  // calling Pit Out Pressure function
  f_pitOutPressure();
  // Calling the calculations function
  f_calculations();
  // Calling the display function
  f_screen_display();
  // Adding the delay for better output display
  delay(100);

}

int valueSmoothing_lm(unsigned int input)
{
  total_temp = total_temp - readings_temp[readIndex_temp];
  // read from the sensor:
  readings_temp[readIndex_temp] = input;
  // add the reading to the total:
  total_temp = total_temp + readings_temp[readIndex_temp];
  // advance to the next position in the array:
  readIndex_temp += 1;

  // if we're at the end of the array...
  if (readIndex_temp >= numReadings_temp)
  { // ...wrap around to the beginning:
    readIndex_temp = 0;
  }
  // calculate the average:
  average_temp = total_temp / numReadings_temp;
  // send it to the computer as ASCII digits
  return average_temp;
}

int valueSmoothing_pressure(unsigned int input)
{
  total_ambPressure = total_ambPressure - readings_ambPressure[readIndex_ambPressure];
  // read from the sensor:
  readings_ambPressure[readIndex_ambPressure] = input;
  // add the reading to the total:
  total_ambPressure = total_ambPressure + readings_ambPressure[readIndex_ambPressure];
  // advance to the next position in the array:
  readIndex_ambPressure += 1;

  // if we're at the end of the array...
  if (readIndex_ambPressure >= numReadings_ambPressure)
  { // ...wrap around to the beginning:
    readIndex_ambPressure = 0;
  }
  // calculate the average:
  average_ambPressure = total_ambPressure / numReadings_ambPressure;
  // send it to the computer as ASCII digits
  return average_ambPressure;
}

int valueSmoothing_deltPressure(unsigned int input)
{
  total_pitout = total_pitout - readings_pitout[readIndex_pitout];
  // read from the sensor:
  readings_pitout[readIndex_pitout] = input;
  // add the reading to the total:
  total_pitout = total_pitout + readings_pitout[readIndex_pitout];
  // advance to the next position in the array:
  readIndex_pitout += 1;

  // if we're at the end of the array...
  if (readIndex_pitout >= numReadings_pitout)
  { // ...wrap around to the beginning:
    readIndex_pitout = 0;
  }
  // calculate the average:
  average_pitout = total_pitout / numReadings_pitout;
  // send it to the computer as ASCII digits
  return average_pitout;
}

void  f_temp()
{
  unsigned int lv_temp = 0;

  // Reading Ambient Temperature

  for (int i = 0; i < 20; i++)
  {
    lv_temp = lv_temp + analogRead(lm35_pin);
  }
  lv_temp = lv_temp / 20;

  //Averaging the value of temperature
  gv_temp_actual = lv_temp * 0.805;                                                                             // Converting the value of ADC to milliVolts i.e. 1 step of ADC means (3.3*1023)=0.003225 Volts or 3.225 milliVolts
  gv_temp_actual = gv_temp_actual / 10;                                                                                // Converting millivolts value into degree centigrate
  gv_temp_actual = valueSmoothing_lm(gv_temp_actual);                                                                         // Calling value Somoothning function and gets inreturn smooth value of Temperature Sensor
}
void f_ambPressure()
{
  unsigned int lv_ambPressure;

  // Reading Ambient Pressure
  lv_ambPressure = analogRead(AmbPressure_pin);                                                                        // First analog read from pressure sensor
  delay(c_adc_wait);                                                                                                   // delay of 10 milliseconds
  lv_ambPressure = analogRead(AmbPressure_pin);                                                                        // Second analog read from pressure sensor
  delay(c_adc_wait);                                                                                                   // delay of 10 milliseconds
  lv_ambPressure = lv_ambPressure / 4;                                                                                 //Converting values from 12 bit to 10 bit resolution
  lv_ambPressure = constrain(lv_ambPressure, 206, c_fullScale);

  // Smoothning the value of Ambient Pressure
  gv_ambPressure_actual = valueSmoothing_pressure(lv_ambPressure);                                                     // Calling the valueSmoothing function and gets in return smooth value of potentiometer
  gv_ambPressure_actual = map(gv_ambPressure_actual, 204, c_fullScale, 101325, 0);                                     // Mapping values with input and output values
  gv_ambPressure_actual = constrain(gv_ambPressure_actual, 205, 101325 );

}

void f_pitOutPressure()
{
  unsigned int lv_pitOutPressure;
  // Reading Differential Pressure
  lv_pitOutPressure = analogRead(pitOutPressure_pin);                                                                  // First analog read from pressure sensor
  delay(c_adc_wait);                                                                                                   // delay of 10 milliseconds
  lv_pitOutPressure = analogRead(pitOutPressure_pin);                                                                  // Second analog read from pressure sensor
  delay(c_adc_wait);                                                                                                   // delay of 10 milliseconds

  lv_pitOutPressure = lv_pitOutPressure / 4;                                                                           // Converting values from 12 bit to 10 bit resolution

  lv_pitOutPressure = valueSmoothing_deltPressure(lv_pitOutPressure);

  lv_pitOutPressure = constrain(lv_pitOutPressure, 206, c_fullScale);

  //Smoothning the value of Delta pressure
  gv_pitOutPressure_actual = lv_pitOutPressure ;
  gv_pitOutPressure_actual = map(gv_pitOutPressure_actual, 206, c_fullScale , 0, 37300);                               // Mapping values with input and output
  if (gv_pitOutPressure_actual < 0) gv_pitOutPressure_actual = 0;

}
void f_calculations()
{
  unsigned int lv_Tk;
  float lv_RAT_1, lv_RAT_2, lv_RAT_3, lv_RAT_4;


  // K1_value
  lv_RAT_1 = (float)(gv_ambPressure_actual) / Pn;                                                                      // ratio 1
  lv_RAT_2 = (float)Tkn / (273 + gv_temp_actual);                                                                      // ratio 2
  gv_K_1 = (float)sqrt(lv_RAT_1 * lv_RAT_2);                                                                           // value of K1

  // K2_value
  lv_Tk = (float)(273 + gv_temp_actual);
  lv_RAT_3 = (float)(gv_ambPressure_actual) / (R_value * lv_Tk);                                                       // ratio 3
  gv_K_2 = (float)sqrt(lv_RAT_3);                                                                                      // value of K2

  // K3_value
  gv_K_3 = (float)sqrt(gv_pitOutPressure_actual);                                                                      // value of K3

  // flow Rate
  gv_flowRate = (float)0.1343 * gv_K_1 * gv_K_2 * gv_K_3;
}
void f_screen_display()
{

  //LCD Print
  lcd.setCursor(0, 1); lcd.print("                    ");
  lcd.setCursor(0, 2); lcd.print("                    ");
  lcd.setCursor(0, 3); lcd.print("                    ");
  lcd.setCursor(0, 1);  lcd.print(" T"); lcd.print((int)gv_temp_actual);                                                 // cursor for first column and fourth row
  lcd.setCursor(7, 1); lcd.print("P"); lcd.print((int)gv_ambPressure_actual / 100);                                    //Converting to HectoPascal     // cursor for first column and fourth row
  lcd.setCursor(14, 1); lcd.print("P"); lcd.setCursor(15, 1);  lcd.print((int)gv_pitOutPressure_actual / 100);         // cursor for first column and fourth row
  lcd.setCursor(0, 3);  lcd.print("AirFlow "); lcd.print(gv_flowRate, 3); lcd.print("KG/SEC");                         // cursor for first column and fourth row

}
