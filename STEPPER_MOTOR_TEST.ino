int const c_stepPin1 = 3, c_dirPin1 = 4, c_en1 = 2;
int const c_stepPin2 = 9, c_dirPin2 = 10, c_en2 = 8;  //Motor 2 step pin, diretion pin and enable at 5, 6, 7
int i = 0;
int const c_steps = 100,
          c_delay = 0,
          c_stepDelay = 10;

void f_motor_1()
{
  digitalWrite(c_en1, LOW);          //Set motor 1 on
  digitalWrite(c_en2, HIGH);
  digitalWrite(c_dirPin1, HIGH);     //Set motor 1 direction to clockwise
  for (i = 0; i <  c_steps; i++)
  {
    digitalWrite(c_stepPin1, HIGH);
    digitalWrite(c_stepPin2, HIGH);
    delay(c_stepDelay);
    digitalWrite(c_stepPin1, LOW);
    digitalWrite(c_stepPin2, LOW);
    delay(c_stepDelay);
  }
  //delay(c_delay);
  /****motor 1 reverse diresction*****/
  digitalWrite(c_dirPin1, LOW);       //Set motor 1 direction to counter clockwise
  for (i = 0; i <= c_steps; i++)
  {
    digitalWrite(c_stepPin1, HIGH);
    digitalWrite(c_stepPin2, HIGH);
    delay(c_stepDelay);
    digitalWrite(c_stepPin1, LOW);
    digitalWrite(c_stepPin2, LOW);
    delay(c_stepDelay);
  }
  digitalWrite(c_en1, HIGH);         //Set motor 1  enable oFF
}                                    // END OF MOTOR 1 FUNCTION

void f_motor_2()
{
  digitalWrite(c_en1, HIGH);
  digitalWrite(c_en2, LOW);          //Set motor 2 on
  digitalWrite(c_dirPin2, HIGH);     //Set motor 2 direction to clockwise
  delay(200);
  for (i = 0; i <= c_steps; i++)
  {
    digitalWrite(c_stepPin1, HIGH);
    digitalWrite(c_stepPin2, HIGH);
    delay(c_stepDelay);
    digitalWrite(c_stepPin1, LOW);
    digitalWrite(c_stepPin2, LOW);
    delay(c_stepDelay);
  }
  delay(c_delay);
  /*****MOTOR 2 REVERSE DIRECTION*****/
  digitalWrite(c_en2, LOW);          //Set motor 2 on
  digitalWrite(c_dirPin2, LOW);      //Set motor 2 direction to counter clockwise
  for (i = 0; i <= c_steps; i++)
  {
    digitalWrite(c_stepPin1, HIGH);
    digitalWrite(c_stepPin2, HIGH);
    delay(c_stepDelay);
    digitalWrite(c_stepPin1, LOW);
    digitalWrite(c_stepPin2, LOW);
    delay(c_stepDelay);
  }
  digitalWrite(c_en1, HIGH);         //Set motor 2 oFF
}

void f_both_motors_same_direction()
{
  digitalWrite(c_en1, LOW);          //Set BOTH motors on
  digitalWrite(c_en2, LOW);
  delay(200);
  digitalWrite(c_dirPin1, HIGH);    //Set BOTH motor direction to clockwise
  digitalWrite(c_dirPin2, HIGH);
  for (i = 0; i <= c_steps; i++)
  {
    digitalWrite(c_stepPin1, HIGH);
    digitalWrite(c_stepPin2, HIGH);
    delay(c_stepDelay);
    digitalWrite(c_stepPin1, LOW);
    digitalWrite(c_stepPin2, LOW);
    delay(c_stepDelay);
  }
  delay(200);
  digitalWrite(c_dirPin1, LOW);    //Set motor direction to counter clockwise
  digitalWrite(c_dirPin2, LOW);
  for (i = 0; i <= c_steps; i++)
  {
    digitalWrite(c_stepPin1,  HIGH);
    digitalWrite(c_stepPin2, HIGH);
    delay(c_stepDelay);
    digitalWrite(c_stepPin1, LOW);
    digitalWrite(c_stepPin2, LOW);
    delay(c_stepDelay);
  }
  digitalWrite(c_en1, HIGH);
  digitalWrite(c_en2, HIGH);
}                               //end of both motors in same direction funtion

void f_both_motors_opposite()
{
  digitalWrite(c_en1, LOW);          //Set BOTH motors on
  digitalWrite(c_en2, LOW);
  delay(200);
  digitalWrite(c_dirPin1, LOW);
  digitalWrite(c_dirPin2, HIGH);
  for (i = 0; i <= c_steps; i++)
  {
    digitalWrite(c_stepPin1, HIGH);
    digitalWrite(c_stepPin2, HIGH);
    delay(c_stepDelay);
    digitalWrite(c_stepPin1, LOW);
    digitalWrite(c_stepPin2, LOW);
    delay(c_stepDelay);
  }

  delay(200);
  digitalWrite(c_dirPin1, HIGH);
  digitalWrite(c_dirPin2, LOW);
  for (i = 0; i <= c_steps; i++)
  {
    digitalWrite(c_stepPin1, HIGH);
    digitalWrite(c_stepPin2, HIGH);
    delay(c_stepDelay);
    digitalWrite(c_stepPin1, LOW);
    digitalWrite(c_stepPin2, LOW);
    delay(c_stepDelay);
  }
  digitalWrite(c_en1, HIGH);
  digitalWrite(c_en2, HIGH);
}                                  //end of both motors in opposite direction

void setup()
{
  pinMode(c_stepPin1, OUTPUT);
  pinMode(c_dirPin1, OUTPUT);
  pinMode(c_en1, OUTPUT);

  pinMode(c_stepPin2, OUTPUT);
  pinMode(c_dirPin2, OUTPUT);
  pinMode(c_en2, OUTPUT);

  /***********BOTH MOTORS OFF****/
 // digitalWrite(c_en1, HIGH);         //Set initially both motor's enable off
 // digitalWrite(c_en2, HIGH);
}

void loop()
{
  /**********MOTOR 1 ON*********/
  f_motor_1();
  delay(200);
  /*********MOTOR 2 ON*******/
  f_motor_2();
  delay(200);
  /********BOTH MOTORS ON both moving in same direction*******/
  f_both_motors_same_direction();
  delay(200);
  /******moving both motors in opposite direction to each other*******/
  f_both_motors_opposite();
 
/********check for holding current********/ 
  digitalWrite(c_en1, LOW);
  digitalWrite(c_en2, LOW);
  delay(2000);
  digitalWrite(c_en1, HIGH);
  digitalWrite(c_en2, HIGH);
}                                   //closes loop function

