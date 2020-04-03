/*******
   THIS PROGRAM IS FOR DUAL DTEP MOTOR SRIVER ic TESTER JIG
   TO CHECK WHETHER THE IC IS WORKING OR NOT

*/

int const c_stepPin1 = 4, c_dirPin1 = 3, c_en1 = 2;
int i = 0;
int const c_steps = 400,
          c_delay = 0,
          c_step_delay = 5;

void f_test_code(int lv_enable, int lv_step, int lv_direction) // this is for the testing of all the connected pins working properly or not
{
  digitalWrite(lv_enable, HIGH);
  digitalWrite(lv_enable, HIGH);
  digitalWrite(lv_enable, HIGH);
  delay(2000);
  digitalWrite(lv_enable, LOW);
  digitalWrite(lv_enable, LOW);
  digitalWrite(lv_enable, LOW);
  delay(2000);
}

void f_clockwise(int lv_enable, int lv_step, int lv_direction) // this funtiion  runs the motor in clockwise direction
{
  //ENABLE THE MOTOR PIN
  digitalWrite(lv_enable, LOW);
  //SET THE DIRECTION PIN
  digitalWrite(lv_direction, LOW); // currently set to low
  for (int i = 0; i <= c_steps; i++)
  {
    digitalWrite(lv_step, HIGH);
    delay(c_step_delay);
    digitalWrite(lv_step, LOW);
    delay(c_step_delay);
  }
  digitalWrite(lv_enable, HIGH);
}

void f_anticlockwise(int lv_enable, int lv_step, int lv_direction)
{
  //ENABLE THE MOTOR PIN
  digitalWrite(lv_enable, LOW);
  //SET THE DIRECTION PIN
  digitalWrite(lv_direction, HIGH); // currently set to high

  for (int i = 0; i <= c_steps; i++)
  {
    digitalWrite(lv_step, HIGH);
    delay(c_step_delay);
    digitalWrite(lv_step, LOW);
    delay(c_step_delay);
  }
  digitalWrite(lv_enable, HIGH);
}

void setup()
{
  pinMode(c_stepPin1, OUTPUT);
  pinMode(c_dirPin1, OUTPUT);
  pinMode(c_en1, OUTPUT);
  /***********SET MOTOR TO OFF INITIALLY****/
  digitalWrite(c_en1, HIGH);         //Set initially both motor's enable off

}

void loop()
{
  /***********/
  f_clockwise(c_en1, c_stepPin1, c_dirPin1);
  delay(1000);
  f_anticlockwise(c_en1, c_stepPin1, c_dirPin1);
  delay(1000);
  /**********/
//  f_test_code(); // function to check all I/O's currently disabled

}
