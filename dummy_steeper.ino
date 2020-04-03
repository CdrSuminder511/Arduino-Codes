int const c_stepPin1 = A5, c_dirPin1 = A6, c_en1 = A7;
int const c_stepPin2 = 9, c_dirPin2 = 10, c_en2 = 8;  //Motor 2 step pin, diretion pin and enable at 5, 6, 7
int i = 0;
int const c_steps = 100,
          c_delay = 0,
          c_stepDelay = 10;

void setup()
{
  pinMode(c_stepPin1, OUTPUT);
  pinMode(c_dirPin1, OUTPUT);
  pinMode(c_en1, OUTPUT);

  pinMode(c_stepPin2, OUTPUT);
  pinMode(c_dirPin2, OUTPUT);
  pinMode(c_en2, OUTPUT);
}

void loop()
{
  digitalWrite(c_stepPin1, HIGH);
  digitalWrite(c_stepPin2, HIGH);
  digitalWrite(c_en1, HIGH);
  digitalWrite(c_en2, HIGH);
  digitalWrite(c_dirPin1, HIGH);
  digitalWrite(c_dirPin2, HIGH);
  delay(1000);
  digitalWrite(c_stepPin1, LOW);
  digitalWrite(c_stepPin2, LOW);
  digitalWrite(c_en1, LOW);
  digitalWrite(c_en2, LOW);
  digitalWrite(c_dirPin1, LOW);
  digitalWrite(c_dirPin2, LOW);
  delay(1000);
}
