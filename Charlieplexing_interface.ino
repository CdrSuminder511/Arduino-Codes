/*******************************************************************************
IN THIS ARDUINOO CODE I AM TRYING FOR CHARLIEPLEXING USING ARDUINO NANO
3 PINS OF ARDUINO NANO ARE USED NAMELY D2, D3 AND D4
IN THIS I AM PROMPTING THE USER FOR INPUT TO ASK  WHICH LED TO LIGHT UP
**********************************************************************************/

/*****___CONSTANTS____*******/
int const c_serial_baud_rate = 9600;         // CONSTANT FOR SERIAL BAUD RATE TO COMMUNICATE WITH ARDUINO (CURRENTLY SET TO 9600) 
int const c_pin_1 = 2;                       // CONSTANT 
int const c_pin_2 = 3; 
int const c_pin_3 = 4; 
String const c_on = "HIGH";
String const c_off = "LOW  ";
//String const c_on = "HIGH";
void setup() 
{
 Serial.begin(c_serial_baud_rate);
 

}

void loop() 
{


}
