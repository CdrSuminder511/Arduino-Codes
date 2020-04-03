int const c_stepPin1 =  3, c_dirPin1 = 4, c_en1 = 2;

int i = 0;
int const c_steps = 200,
          c_delay = 0,
          c_stepDelay = 1 ;
void setup()
{
  pinMode(c_stepPin1, OUTPUT);
  pinMode(c_dirPin1, OUTPUT);
  pinMode(c_en1, OUTPUT);
  digitalWrite(c_en1, LOW);
}

void loop()
{
 /**********MOTOR 1 ON*********/
//    digitalWrite(c_en1, LOW);          //Set motor 1 on
    digitalWrite(c_dirPin1, HIGH);     //Set motor 1 direction to clockwise
    for (i = 0; i <= c_steps; i++)
    {
      digitalWrite(c_stepPin1, HIGH);
      delay(c_stepDelay);
      digitalWrite(c_stepPin1, LOW);
      delay(c_stepDelay);
    }
    delay(c_delay);
    digitalWrite(c_dirPin1, LOW);       //Set motor 1 direction to counter clockwise
    for (i = 0; i <= c_steps; i++)
    {
      digitalWrite(c_stepPin1, HIGH);
      delay(c_stepDelay);
      digitalWrite(c_stepPin1, LOW);
      delay(c_stepDelay);
    }
    //digitalWrite(c_en1, HIGH);         //Set motor 1 oFF
    delay(2000);
    // delay(c_delay);
    

}
