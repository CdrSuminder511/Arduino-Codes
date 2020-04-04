char tag[] ="10004B2EFE8B"; // Replace with your own Tag ID
char input[12];        // A variable to store the Tag ID being presented
int count = 0;        // A counter variable to navigate through the input[] character array
boolean flag = 0;     // A variable to store the Tag match status
#include <LiquidCrystal.h>
LiquidCrystal LCD(9,8,7,6,5,4);
#define MOTOR_R 10
#define MOTOR_G 11
#define BUZZER 12

void setup()
{
  Serial.begin(9600);
  LCD.begin(16,2);   
  pinMode(MOTOR_R,OUTPUT); 
  pinMode(MOTOR_G,OUTPUT); 
  pinMode(BUZZER,OUTPUT);
  LCD.setCursor(0,0);
  LCD.print("RFID BASED ");
  LCD.setCursor(0,1);
  LCD.print("Attendence ");
  delay(5000);
  LCD.clear();
  LCD.print("System");
  delay(2000);
  LCD.clear();
}
void loop()
{
  LCD.print("Place your card");
  
  if(Serial.available())// Check if there is incoming data in the RFID Reader Serial Buffer.
  {
    count = 0; // Reset the counter to zero
    /* Keep reading Byte by Byte from the Buffer till the RFID Reader Buffer is empty 
       or till 12 Bytes (the ID size of our Tag) is read */
    while(Serial.available() && count < 12) 
    {
      input[count] = Serial.read(); // Read 1 Byte of data and store it in the input[] variable
      count++; // increment counter
      delay(5);
    }
    /* When the counter reaches 12 (the size of the ID) we stop and compare each value 
        of the input[] to the corresponding stored value */
    if(count == 12) // 
    {
      count =0; // reset counter varibale to 0
      flag = 1;
      /* Iterate through each value and compare till either the 12 values are 
         all matching or till the first mistmatch occurs */
      while(count<12 && flag !=0)  
      {
        if(input[count]==tag[count])
        flag = 1; // everytime the values match, we set the flag variable to 1
        else
        flag= 0; 
                               /* if the ID values don't match, set flag variable to 0 and 
                                  stop comparing by exiting the while loop */
        count++; // increment i
      }
    }
    if(flag == 1) // If flag variable is 1, then it means the tags match
    {
      LCD.clear();
      LCD.println("ATTENDENCE REGISTERED");
      Serial.println("ATTENDENCE REGISTERED");
      
      digitalWrite(BUZZER,HIGH);
      delay(2000);
      digitalWrite(BUZZER,LOW);
      delay(500);

      digitalWrite(BUZZER,HIGH);
      delay(2000);
      digitalWrite(BUZZER,LOW);
      delay(500);
      
      digitalWrite(MOTOR_R,HIGH);
      digitalWrite (MOTOR_R,LOW);
      delay (5000);
      digitalWrite(MOTOR_R,LOW);
      digitalWrite(MOTOR_R,HIGH);
      
    }
    else
    {
      LCD.clear();
      LCD.println("INVALID CARD"); // Incorrect Tag Message
      Serial.println("Invalid Card");
      digitalWrite(BUZZER,HIGH);
      delay(10000);
      digitalWrite(BUZZER,LOW);
    }
    /* Fill the input variable array with a fixed value 'F' to overwrite 
    all values getting it empty for the next read cycle */
    for(count=0; count<12; count++) 
    {
      input[count]= 'F';
    }
    count = 0; // Reset counter variable
  }
}
