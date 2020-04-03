#include <LiquidCrystal.h>
#include <EEPROM.h>
const int rs = 5, en = 6, d4 = 7, d5 = 8, d6 = 9, d7 = 10; //LCD pins configuration
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/*******DECLARATION OF INPUTS***********/
int const c_cap_Sensor = A0;             // CAV444 INPUT AT A0 PIN-no:23
int const c_LM35 = A1;                   // LM35   INPUT AT A1 PIN-no:24
int const c_button_config = A2;          // BUTTON FOR CONFIGURATION MENU
int const c_button_up = A3;              // BUTTON FOR INCREMENT MOISTURE VALUES
int const c_button_down = A4;            // BUTTON FOR DECREMENT MOISTURE VALUES
int const c_button_ok = A5;              // BUTTON FOR ACCEPTING AND SORING THE VALUES
int const c_max_no_of_profiles = 3;
/*******CONSTANTS*********/
//int const c_average_times = 100;         // CONSTANT FOR AVERAGING THE ADC READING
float const c_least_count = 0.1;   // CALIRATION SCALE VALUE CONSTANT
int const c_gv_moisture_min_address = 0; // ADDRESS TO STORE MINIMUM VALUE OF MOISTURE
int const c_gv_moisture_max_address = 5; // ADDRESS TO STORE MAXIMUM VALUE OF MOISTURE
int const c_default_min_moisture = 30;   // DEFAULT VALUE OF MINIMUM MOISTURE
int const c_default_max_moisture = 300;  // DEFAULT VALUE OF MAXIMUM MOISTURE
/******GLOBAL VARIABLES******/
int gv_profile = 1;                      // VARIABLE FOR THE SELECTION OF THE PROFILES

float gv_moisture_min ;                  // VARIABLE FOR MINIMUM VALUE OF MOISTURE
float gv_moisture_max ;                  // VARIABLE FOR MAXIMUM VALUE OF MOISTURE

float gv_moisture_value ;                 // VARIABLE TO DISPLAY THE MOISTURE VALUES ON LCD

float gv_temperature ;                    // VARIABLE FOR TEMPRATURE VALUES

float gv_adc ;                            // VARIABLE WHICH STORES THE VALUES READ FROM A0 PIN(c_cap_sensor)

float gv_voltage ;                        // VARIABLE TO DISPLAY THE VALUES OF VOLTAGE ON LCD
/********FUNCTIONS**********/

/******AVERAGE FUNCTION*******/    // NOT USING CURRENTLY
float f_average()                         //THIS FUNCTION AVERAGES THE c_average_times VALUES THAT ARE READ FROM ADC PIN 0
{
  float lv_avg = 0 ;                      //LOCAL VARIABLE WHICH STORES THE AVERAGE OF c_average_times VALUES
  float lv_sum = 0;                       //LOCAL VARIABLE WHICH SUMS c_average_times VALUES
  for (int i = 0; i < c_average_times; i++)
  {
    lv_sum = lv_sum + 941.20;//analogRead(c_cap_Sensor);
  }
  //Serial.print("lv_sum:");
  //Serial.print(lv_sum);
  lv_avg =  lv_sum / c_average_times;

  return lv_avg;
}
/****DISPLAY MOISTURE FUNCTION******/
void f_display_moisture()                        // THIS FUNCTION DISPLAYS THE MOISTURE VALUE READ FROM ADC
{
  gv_adc = analogRead(c_cap_Sensor);
  gv_voltage = (gv_adc / 1023) * 5;

  lcd.setCursor(13, 1);
  lcd.print(gv_voltage);

  gv_moisture_value = ((gv_adc / 1023) * (gv_moisture_max - gv_moisture_min )) + gv_moisture_min;

  lcd.setCursor(0, 1);
  lcd.print("Mos:");
  lcd.print(gv_moisture_value);
}
/*******DISPLAY PROFILE******/
void f_display_profile()         // THIS FUNCTION DISPLAYS PROFILE MESSEGE OF WHAET RICE AND PADDY
{
  //lcd.clear();
  switch (gv_profile)
  {
    case 1:                  //PROFILE FOR WHEAT
      lcd.setCursor(4, 0);
      lcd.print("WHEAT");
      break;

    case 2:                  //PROFILE FOR RICE
      lcd.setCursor(4, 0);
      lcd.print("RICE");
      break;

    case 3:                  //PROFILE FOR PADDY
      lcd.setCursor(4, 0);
      lcd.print("PADDY");
      break;
  }
}                                 // END OF PROFILE FUNTION
/*********CALIBRATION MENU FUNCTION*********///DELETED DUE TO NON FUNCTIONING




/******SETUP FUNCTION********/
void setup()
{
  if (digitalRead(c_button_ok) == 0)
  {
    gv_moisture_min = 30;
    gv_moisture_max = 300;
    EEPROM.put(c_gv_moisture_min_address, gv_moisture_min);
    EEPROM.put(c_gv_moisture_max_address, gv_moisture_max);
  }
//  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(c_cap_Sensor, INPUT);
  pinMode(c_LM35, INPUT);
  pinMode(c_button_config, INPUT);
  pinMode(c_button_up, INPUT);
  pinMode(c_button_down, INPUT);
  pinMode(c_button_ok, INPUT);
  //????????GET VALUES BASED ON PROFILE????????
  //???????SAVE PROFILE IN EEPROM ALSO?????
  EEPROM.get(c_gv_moisture_min_address, gv_moisture_min);   //
  EEPROM.get(c_gv_moisture_max_address, gv_moisture_max);
  // if out of range then assign default
  /*
    if ( ((String)gv_moisture_min).compareTo("nan"))
    {
    gv_moisture_min = 30.00f;
    EEPROM.put(c_gv_moisture_min_address, gv_moisture_min);
    }
    if ( ((String)gv_moisture_max).compareTo("nan"))
    {
    gv_moisture_max = 300.00f;
    EEPROM.put(c_gv_moisture_max_address, gv_moisture_max);
    }
  */

}
/********LOOP FUNCTION**********/
void loop()
{

  /****PROFILE SELECTION****/
  while (digitalRead(c_button_up) == 0)      // WHEN BUTTN 2 IS PRESSED
  {
    if (digitalRead(c_button_up) == 1)        // WAIT TILL BUTTON IS RELEAED
    {
      gv_profile++;                           // INCREMENT THE gv_profile BY 1
    }
  }
  while (digitalRead(c_button_down) == 0)   // WHEN  BUTTON 3 IS PRESSEED
  {
    if (digitalRead(c_button_down) == 1)     // WAIT TILL BUTTON IS RELEASED
    {
      gv_profile--;                           // DECRMENT THE gv_profile BY 1
    }
  }
  if (gv_profile > c_max_no_of_profiles)
  {
    gv_profile = 1;
  }
  if (gv_profile < 0)
  {
    gv_profile = 1;
  }
  /*******DISPLAY PROFILE*********/
  f_display_profile();
  /******CALIBRATION MENU*****/
  //??????PUT THIS IN FUNCTION??????
 //????ADD FUNTIONALITY FOR LONG PRESS CHANGE ALSO?????
  if (digitalRead(c_button_config) == 0)       // WHEN BUTTON1 IS PRESSSED ENTERS TO CONFIG MENU
  {
    lcd.clear();                                // CLEAR THE LCD
    while (digitalRead(c_button_ok) == 1)       // TILL THE BUTTON 4 IS NOT PRESSED REMAINS IN THE WHILE LOOP
    {
      while (digitalRead(c_button_up) == 0)     // WHEN BUTTON 2 IS PRESSED
      {
        if (digitalRead(c_button_up) == 1)      // WAIT TILL THE BUTTON IS RELEASED
        {
          gv_moisture_min += c_least_count;   // INCREMENT gv_moisture_min VALUE BY c_least_count
        }
      }
      while (digitalRead(c_button_down) == 0)      // WHEN BUTTON 3 IS PRESSSED
      {
        if (digitalRead(c_button_down) == 1)       // WAIT TILL BUTTON IS RELEASED
        {
          gv_moisture_min -= c_least_count;   // DECREMENT VALUE gv_moisture_min BY c_calibation_vlaue
        }
      }
      lcd.setCursor(0, 0);                       // SET LCD CURSOR TO 0,0
      lcd.print( "Minimum:");                    // DISPLAY MESSEGE (8 CHARACTERS)
      lcd.print(gv_moisture_min);                // DISPLAY MINIMUM VALUE OF MOISTURE ON SCREEN
    }

    while (digitalRead(c_button_ok) == 0)      // WHEN BUTTON 4 IS PRESSED OUT OF THE FIRST WHILE LOOP
    {
      if (digitalRead(c_button_ok) == 1)        // LOCK IN THE SECOND THE SECOND WHILE LOOP
      {
        lcd.clear();                             // CLEAR THE LCD SCREEN
      }
    }
    while (digitalRead(c_button_ok) == 1)      // TILL BUTTON 4 IS NOT PRESSED
    { // REMAIN IN THIS LOOP

      while (digitalRead(c_button_up) == 0)    // WHEN BUTTON 2 IS PRESSED
      { // ENTER THE WHILE LOOP
        if (digitalRead(c_button_up) == 1)     // WAIT TILL BUTTON IS RELEASED
        {
          gv_moisture_max += c_least_count; // COMPOUND INCREMENT gv_moisture_max BY c_least_count
        }
      }
      while (digitalRead(c_button_down) == 0)    // WHEN BUTTON 3 IS PRESSED
      {
        if (digitalRead(c_button_down) == 1)     // WAIT TILL BUTTON IS RELEASED
        {
          gv_moisture_max -= c_least_count; // COMPOUND DECREMENT gv_moisture_max BY c_least_count
        }
      }
      lcd.setCursor(0, 0);                       // SET LCD CURSOR TO ROW:0, COLUMN:0
      lcd.print("Maximum:");                     // DISPLAY MAXIMUM: 8 CHARACTERS
      lcd.print(gv_moisture_max);                // DISPLAY VALUE OF gv_moisture_max
    }
    delay(100);
    /******DISPLAY THE MINIMUM AND MAXIMIUM VALUES AFTER CALIBRATION******/
    lcd.setCursor(0, 0);
    lcd.print("Minimum:");
    lcd.print(gv_moisture_min);
    lcd.setCursor(0, 1);
    lcd.print("Maximum:");
    lcd.print(gv_moisture_max);
    delay(2000);
  }                                         // CLOSES THE CALIBRATION MENU
  //??????PUT ACCORDING TO PROFILE?????
  EEPROM.put(c_gv_moisture_min_address, gv_moisture_min); //PUT THE MINIMUM AND MAXIMUMM VALUES IN EEPROM
  EEPROM.put(c_gv_moisture_max_address, gv_moisture_max);
  /*****DISPLAY THE MOISTURE******/
  //????ADD AVERAGING AND SMOOTHING FUNCTION??????
  f_display_moisture();                        // CALL 
}                                                            // CLOSES LOOP FUNCTION



