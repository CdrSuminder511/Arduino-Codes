/*****Motor 1 connection****/
int const c_stepPin1 = 6;
int const c_dirPin1 = 5;
int const c_en1 = 7;
/*****Motor 2 connection****/
int const c_stepPin2 = 3;
int const c_dirPin2 = 2;
int const c_en2 = 4; 
 
int i = 0;

int const c_steps = 400;
int const c_step_delay = 2;

void f_clockwise(int lv_enable, int lv_step, int lv_direction) // this function runs a single motor in clockwise direction
{
  //ENABLE THE MOTOR PIN
  digitalWrite(lv_enable, LOW);
  //SET THE DIRECTION PIN
  digitalWrite(lv_direction, LOW);
  for (int i = 0; i <= c_steps; i++)
  {
    digitalWrite(lv_step, HIGH);
    delay(c_step_delay);
    digitalWrite(lv_step, LOW);
    delay(c_step_delay);
  }
  digitalWrite(lv_enable, HIGH);
}

void f_anticlockwise(int lv_enable, int lv_step, int lv_direction) // this function runs a single motor in anti clockwise direction
{
  //ENABLE THE MOTOR PIN
  digitalWrite(lv_enable, LOW);
  //SET THE DIRECTION PIN
  digitalWrite(lv_direction, LOW);

  for (int i = 0; i <= c_steps; i++)
  {
    digitalWrite(lv_step, HIGH);
    delay(c_step_delay);
    digitalWrite(lv_step, LOW);
    delay(c_step_delay);
  }
  digitalWrite(lv_enable, HIGH);
}

void f_clockwise_both(int lv_enable1, int lv_step1, int lv_direction1, int lv_enable2, int lv_step2, int lv_direction2)
{
  //ENABLE THE MOTOR PIN               // this function runs a dual motors in clockwise direction
  digitalWrite(lv_enable1, LOW);
  digitalWrite(lv_enable2, LOW);
  //SET THE DIRECTION PIN
  digitalWrite(lv_direction2, LOW);
  digitalWrite(lv_direction1, LOW);
  for (int i = 0; i <= c_steps; i++)
  {
    digitalWrite(lv_step1, HIGH);
    digitalWrite(lv_step2, HIGH);
    delay(c_step_delay);
    digitalWrite(lv_step1, LOW);
    digitalWrite(lv_step2, LOW);
    delay(c_step_delay);
  }
  digitalWrite(lv_enable1, HIGH);
  digitalWrite(lv_enable1, HIGH);
}

void f_anticlockwise_both(int lv_enable1, int lv_step1, int lv_direction1, int lv_enable2, int lv_step2, int lv_direction2)
{
  //ENABLE THE MOTOR PIN        // this function runs a dual motors in anti clockwise direction
  digitalWrite(lv_enable1, LOW);
  digitalWrite(lv_enable2, LOW);
  //SET THE DIRECTION PIN
  digitalWrite(lv_direction1, HIGH);
  digitalWrite(lv_direction2, HIGH);
  for (int i = 0; i <= c_steps; i++)
  {
    digitalWrite(lv_step1, HIGH);
    digitalWrite(lv_step2, HIGH);
    delay(c_step_delay);
    digitalWrite(lv_step1, LOW);
    digitalWrite(lv_step2, LOW);
    delay(c_step_delay);
  }
  digitalWrite(lv_enable1, HIGH);
  digitalWrite(lv_enable1, HIGH);
}
void f_both_motors_opposite()      // this function runs a dual motors in clockwise direction
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
    delay(c_step_delay);
    digitalWrite(c_stepPin1, LOW);
    digitalWrite(c_stepPin2, LOW);
    delay(c_step_delay);
  }

  delay(200);
  digitalWrite(c_dirPin1, HIGH);
  digitalWrite(c_dirPin2, LOW);
  for (i = 0; i <= c_steps; i++)
  {
    digitalWrite(c_stepPin1, HIGH);
    digitalWrite(c_stepPin2, HIGH);
    delay(c_step_delay);
    digitalWrite(c_stepPin1, LOW);
    digitalWrite(c_stepPin2, LOW);
    delay(c_step_delay);
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
  /**********MOTOR 1 ON*********
    f_clockwise(c_en1, c_stepPin1, c_dirPin1);
    delay(200);
    f_anticlockwise(c_en1, c_stepPin1, c_dirPin1);
    /*********MOTOR 2 ON*******
    f_clockwise(c_en2, c_stepPin2, c_dirPin2);
    delay(200);
    f_anticlockwise(c_en2, c_stepPin2, c_dirPin2);
    /********BOTH MOTORS ON both moving in same direction*******/
  f_clockwise_both(c_en1, c_stepPin1, c_dirPin1, c_en2, c_stepPin2, c_dirPin2);
  delay(200);
  f_anticlockwise_both(c_en1, c_stepPin1, c_dirPin1, c_en2, c_stepPin2, c_dirPin2);
  delay(200);
  /******moving both motors in opposite direction to each other*******/
 // f_both_motors_opposite();

  /********check for holding current********/
  digitalWrite(c_en1, LOW);
  //digitalWrite(c_en2, LOW);
  delay(2000);
  digitalWrite(c_en1, HIGH);
//  digitalWrite(c_en2, HIGH);
}                                   //closes loop function
