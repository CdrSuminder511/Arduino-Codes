/* Charliplexing for 5 matrix(15) LEDs
   THIS PROGRAM IS JUST A SIMPLE INTERFACE OF 15 LEDS USING CHARLIEPLEXING
   PROGRAM TURNS ON 6 LEDS ONE BY ONE
  --------------------------------------------------------------------------------
  Row 1 (R1): Arduino Pin 2
  Row 2 (R2): Arduino Pin 3
  Row 3 (R3): Arduino Pin 4
  --------------------------------------------------------------------------------
  variable    pinMode      state
  L           OUTPUT       LOW
  H           OUTPUT       HIGH
  X           INPUT        TRISTATE(NONE)
  ---------------------------------------------------------------------------------
    R1 (Pin 2)      R2 (Pin 3)     R3 (Pin 4)
  L1    H                 L                X
  L2    X                 H                L
  L3    L                 H                X
  L4    X                 L                H
  L5    H                 X                L
  L6    L                 X                H
  -----------------------------------------------------------------------------------
  LED   CONNECTIONS

  [D2]----<><><><>-----------------------------
               +|         - |        |       |
               (L1)       (L3)       |       |
               -|         + |       +|      -|
  [D3]----<><><><>------------      (L5)     (L6)
               -|          -|       -|      +|
               (L2)        (L4)      |       |
               +|          +|        |       |
  [D4]----<><><><>-----------------------------

  ---------------------------------------------------------------------------------
  LED    Cathode      Anode
  1         R2          R1
  2         R3          R2
  3         R1          R2
  4         R2          R3
  5         R3          R1
  6         R1          R3
  ---------------------------------------------------------------------------------
*/

const int c_row_1 = 2;     //LED row 1
const int c_row_2 = 3;     //LED row 2
const int c_row_3 = 4;     //LED row 3
const int c_row_4 = 5;     //LED row 4
const int c_row_5 = 6;     //LED row 5


void f_blink_led(int lv_in_1, int lv_in_2, int lv_in_3, int lv_out_1, int lv_out_2)
{
  //  delay(1000);
  pinMode(lv_in_1, INPUT);
  pinMode(lv_in_2, INPUT);
  pinMode(lv_in_3, INPUT);

  pinMode(lv_out_1, OUTPUT);
  digitalWrite(lv_out_1, HIGH);
  pinMode(lv_out_2, OUTPUT);
  digitalWrite(lv_out_2, LOW);
}

void f_digit_ones_zero()
{
  f_blink_led(c_row_3, c_row_4, c_row_5, c_row_1, c_row_2); //Blink L1
  f_blink_led(c_row_1, c_row_4, c_row_5, c_row_2, c_row_3); //Blink L2
  f_blink_led(c_row_1, c_row_2, c_row_5, c_row_3, c_row_4); //Blink L3
  f_blink_led(c_row_1, c_row_2, c_row_3, c_row_4, c_row_5); //Blink L4
  f_blink_led(c_row_1, c_row_2, c_row_3, c_row_5, c_row_4); //Blink L5
  f_blink_led(c_row_1, c_row_2, c_row_5, c_row_4, c_row_3); //Blink L6
  //  delay(1000);
}

void f_digit_ones_one()
{
  digitalWrite(c_row_3, LOW);
  f_blink_led(c_row_1, c_row_4, c_row_5, c_row_2, c_row_3); //Blink L2
  f_blink_led(c_row_1, c_row_2, c_row_5, c_row_3, c_row_4); //Blink L3
  //  delay(1000);
}

void f_digit_ones_two()
{
  f_blink_led(c_row_3, c_row_4, c_row_5, c_row_1, c_row_2); //Blink L1
  f_blink_led(c_row_1, c_row_4, c_row_5, c_row_2, c_row_3); //Blink L2
  f_blink_led(c_row_1, c_row_2, c_row_3, c_row_4, c_row_5); //Blink L4
  f_blink_led(c_row_1, c_row_2, c_row_3, c_row_5, c_row_4); //Blink L5
  f_blink_led(c_row_1, c_row_4, c_row_5, c_row_3, c_row_2); //Blink L7
  //  delay(1000);
}

void f_digit_ones_three()
{
  f_blink_led(c_row_3, c_row_4, c_row_5, c_row_1, c_row_2); //Blink L1
  f_blink_led(c_row_1, c_row_4, c_row_5, c_row_2, c_row_3); //Blink L2
  f_blink_led(c_row_1, c_row_2, c_row_5, c_row_3, c_row_4); //Blink L3
  f_blink_led(c_row_1, c_row_2, c_row_3, c_row_4, c_row_5); //Blink L4
  f_blink_led(c_row_1, c_row_4, c_row_5, c_row_3, c_row_2); //Blink L7
  //  delay(1000);
}

void f_digit_ones_four()
{
  f_blink_led(c_row_1, c_row_4, c_row_5, c_row_2, c_row_3); //Blink L2
  f_blink_led(c_row_1, c_row_2, c_row_5, c_row_3, c_row_4); //Blink L3
  f_blink_led(c_row_1, c_row_2, c_row_5, c_row_4, c_row_3); //Blink L6
  f_blink_led(c_row_1, c_row_4, c_row_5, c_row_3, c_row_2); //Blink L7
  //  delay(1000);
}

void f_digit_ones_five()
{
  f_blink_led(c_row_3, c_row_4, c_row_5, c_row_1, c_row_2); //Blink L1
  f_blink_led(c_row_1, c_row_2, c_row_5, c_row_3, c_row_4); //Blink L3
  f_blink_led(c_row_1, c_row_2, c_row_3, c_row_4, c_row_5); //Blink L4
  f_blink_led(c_row_1, c_row_2, c_row_5, c_row_4, c_row_3); //Blink L6
  f_blink_led(c_row_1, c_row_4, c_row_5, c_row_3, c_row_2); //Blink L7
  //  delay(1000);
}

void f_digit_ones_six()
{
  f_blink_led(c_row_3, c_row_4, c_row_5, c_row_1, c_row_2); //Blink L1
  f_blink_led(c_row_1, c_row_2, c_row_5, c_row_3, c_row_4); //Blink L3
  f_blink_led(c_row_1, c_row_2, c_row_3, c_row_4, c_row_5); //Blink L4
  f_blink_led(c_row_1, c_row_2, c_row_3, c_row_5, c_row_4); //Blink L5
  f_blink_led(c_row_1, c_row_2, c_row_5, c_row_4, c_row_3); //Blink L6
  f_blink_led(c_row_1, c_row_4, c_row_5, c_row_3, c_row_2); //Blink L7
  //  delay(1000);
}

void f_digit_ones_seven()
{
  f_blink_led(c_row_3, c_row_4, c_row_5, c_row_1, c_row_2); //Blink L1
  f_blink_led(c_row_1, c_row_4, c_row_5, c_row_2, c_row_3); //Blink L2
  f_blink_led(c_row_1, c_row_2, c_row_5, c_row_3, c_row_4); //Blink L3
  //  delay(1000);
}

void f_digit_ones_eight()
{
  f_blink_led(c_row_3, c_row_4, c_row_5, c_row_1, c_row_2); //Blink L1
  f_blink_led(c_row_1, c_row_4, c_row_5, c_row_2, c_row_3); //Blink L2
  f_blink_led(c_row_1, c_row_2, c_row_5, c_row_3, c_row_4); //Blink L3
  f_blink_led(c_row_1, c_row_2, c_row_3, c_row_4, c_row_5); //Blink L4
  f_blink_led(c_row_1, c_row_2, c_row_3, c_row_5, c_row_4); //Blink L5
  f_blink_led(c_row_1, c_row_2, c_row_5, c_row_4, c_row_3); //Blink L6
  f_blink_led(c_row_1, c_row_4, c_row_5, c_row_3, c_row_2); //Blink L7
  //  delay(1000);
}

void f_digit_ones_nine()
{
  f_blink_led(c_row_3, c_row_4, c_row_5, c_row_1, c_row_2); //Blink L1
  f_blink_led(c_row_1, c_row_4, c_row_5, c_row_2, c_row_3); //Blink L2
  f_blink_led(c_row_1, c_row_2, c_row_5, c_row_3, c_row_4); //Blink L3
  f_blink_led(c_row_1, c_row_2, c_row_3, c_row_4, c_row_5); //Blink L4
  f_blink_led(c_row_1, c_row_2, c_row_3, c_row_5, c_row_4); //Blink L5
  f_blink_led(c_row_1, c_row_4, c_row_5, c_row_3, c_row_2); //Blink L7
  //  delay(1000);
}

void f_digit_tens_zero()
{
  f_blink_led(c_row_4, c_row_2, c_row_5, c_row_1, c_row_3); //Blink L9
  f_blink_led(c_row_4, c_row_2, c_row_1, c_row_3, c_row_5); //Blink L10
  f_blink_led(c_row_4, c_row_2, c_row_1, c_row_5, c_row_3); //Blink L11
  f_blink_led(c_row_4, c_row_2, c_row_5, c_row_3, c_row_1); //Blink L12
  f_blink_led(c_row_4, c_row_2, c_row_3, c_row_1, c_row_5); //Blink L13
  f_blink_led(c_row_4, c_row_2, c_row_3, c_row_5, c_row_1); //Blink L14

}

void f_digit_tens_one()
{
  digitalWrite(c_row_3, LOW);
  f_blink_led(c_row_1, c_row_4, c_row_5, c_row_2, c_row_3); //Blink L2
  f_blink_led(c_row_1, c_row_2, c_row_5, c_row_3, c_row_4); //Blink L3
  //  delay(1000);
}
void f_digit_tens_two()
{
  f_blink_led(c_row_4, c_row_2, c_row_5, c_row_1, c_row_3); //Blink L9
  f_blink_led(c_row_4, c_row_2, c_row_1, c_row_3, c_row_5); //Blink L10
  //  f_blink_led(c_row_4, c_row_2, c_row_1, c_row_5, c_row_3); //Blink L11
  f_blink_led(c_row_4, c_row_2, c_row_5, c_row_3, c_row_1); //Blink L12
  f_blink_led(c_row_4, c_row_2, c_row_3, c_row_1, c_row_5); //Blink L13
}

void f_digit_tens_three()
{
  f_blink_led(c_row_4, c_row_2, c_row_5, c_row_1, c_row_3); //Blink L9
  f_blink_led(c_row_4, c_row_2, c_row_1, c_row_3, c_row_5); //Blink L10
  f_blink_led(c_row_4, c_row_2, c_row_1, c_row_5, c_row_3); //Blink L11
  f_blink_led(c_row_4, c_row_2, c_row_5, c_row_3, c_row_1); //Blink L12
  //  f_blink_led(c_row_4, c_row_2, c_row_3, c_row_1, c_row_5); //Blink L13
  f_blink_led(c_row_4, c_row_1, c_row_3, c_row_2, c_row_5); //Blink L15
}

void f_digit_tens_four()
{
  //f_blink_led(c_row_4, c_row_2, c_row_5, c_row_1, c_row_3); //Blink L9
  f_blink_led(c_row_4, c_row_2, c_row_1, c_row_3, c_row_5); //Blink L10
  f_blink_led(c_row_4, c_row_2, c_row_1, c_row_5, c_row_3); //Blink L11
  //  f_blink_led(c_row_4, c_row_2, c_row_5, c_row_3, c_row_1); //Blink L12
  //  f_blink_led(c_row_4, c_row_2, c_row_3, c_row_1, c_row_5); //Blink L13
  f_blink_led(c_row_4, c_row_2, c_row_3, c_row_5, c_row_1); //Blink L14
  f_blink_led(c_row_4, c_row_1, c_row_3, c_row_2, c_row_5); //Blink L15
}

void f_digit_tens_five()
{
  f_blink_led(c_row_4, c_row_2, c_row_5, c_row_1, c_row_3); //Blink L9
  //  f_blink_led(c_row_4, c_row_2, c_row_1, c_row_3, c_row_5); //Blink L10
  f_blink_led(c_row_4, c_row_2, c_row_1, c_row_5, c_row_3); //Blink L11
  f_blink_led(c_row_4, c_row_2, c_row_5, c_row_3, c_row_1); //Blink L12
  //  f_blink_led(c_row_4, c_row_2, c_row_3, c_row_1, c_row_5); //Blink L13
  f_blink_led(c_row_4, c_row_2, c_row_3, c_row_5, c_row_1); //Blink L14
  f_blink_led(c_row_4, c_row_1, c_row_3, c_row_2, c_row_5); //Blink L15
}

void f_digit_tens_six()
{
  f_blink_led(c_row_4, c_row_2, c_row_5, c_row_1, c_row_3); //Blink L9
  //  f_blink_led(c_row_4, c_row_2, c_row_1, c_row_3, c_row_5); //Blink L10
  f_blink_led(c_row_4, c_row_2, c_row_1, c_row_5, c_row_3); //Blink L11
  f_blink_led(c_row_4, c_row_2, c_row_5, c_row_3, c_row_1); //Blink L12
  f_blink_led(c_row_4, c_row_2, c_row_3, c_row_1, c_row_5); //Blink L13
  f_blink_led(c_row_4, c_row_2, c_row_3, c_row_5, c_row_1); //Blink L14
  f_blink_led(c_row_4, c_row_1, c_row_3, c_row_2, c_row_5); //Blink L15
}

void f_digit_tens_seven()
{
  f_blink_led(c_row_4, c_row_2, c_row_5, c_row_1, c_row_3); //Blink L9
  f_blink_led(c_row_4, c_row_2, c_row_1, c_row_3, c_row_5); //Blink L10
  f_blink_led(c_row_4, c_row_2, c_row_1, c_row_5, c_row_3); //Blink L11
}


void f_digit_tens_eight()
{
  f_blink_led(c_row_4, c_row_2, c_row_5, c_row_1, c_row_3); //Blink L9
  f_blink_led(c_row_4, c_row_2, c_row_1, c_row_3, c_row_5); //Blink L10
  f_blink_led(c_row_4, c_row_2, c_row_1, c_row_5, c_row_3); //Blink L11
  f_blink_led(c_row_4, c_row_2, c_row_5, c_row_3, c_row_1); //Blink L12
  f_blink_led(c_row_4, c_row_2, c_row_3, c_row_1, c_row_5); //Blink L13
  f_blink_led(c_row_4, c_row_2, c_row_3, c_row_5, c_row_1); //Blink L14
  f_blink_led(c_row_4, c_row_1, c_row_3, c_row_2, c_row_5); //Blink L15

  //  delay(1000);
}

void f_digit_tens_nine()
{
  f_blink_led(c_row_4, c_row_2, c_row_5, c_row_1, c_row_3); //Blink L9
  f_blink_led(c_row_4, c_row_2, c_row_1, c_row_3, c_row_5); //Blink L10
  f_blink_led(c_row_4, c_row_2, c_row_1, c_row_5, c_row_3); //Blink L11
  f_blink_led(c_row_4, c_row_2, c_row_5, c_row_3, c_row_1); //Blink L12
  f_blink_led(c_row_4, c_row_2, c_row_3, c_row_1, c_row_5); //Blink L13
  //  f_blink_led(c_row_4, c_row_2, c_row_3, c_row_5, c_row_1); //Blink L14
  f_blink_led(c_row_4, c_row_1, c_row_3, c_row_2, c_row_5); //Blink L15
}

void f_decimal_point()
{
  f_blink_led(c_row_3, c_row_4, c_row_5, c_row_2, c_row_1); //Blink L8
}

void setup()
{
  digitalWrite(c_row_1, LOW);
  digitalWrite(c_row_2, LOW);
  digitalWrite(c_row_3, LOW);
  digitalWrite(c_row_4, LOW);
  digitalWrite(c_row_5, LOW);
}

void loop()
{
  //  f_digit_ones_zero();
//    f_digit_ones_one();
  //  f_digit_ones_two();
  //  f_digit_ones_three();
  //  f_digit_ones_four();
  //  f_digit_ones_five();
  //  f_digit_ones_six();
  //  f_digit_ones_seven();
    f_digit_ones_eight();

    f_decimal_point();

  //  f_digit_tens_zero();
  //  f_digit_tens_one();
  //  f_digit_tens_two();
  //  f_digit_tens_three();
  //  f_digit_tens_four();
  //  f_digit_tens_five();
  //  f_digit_tens_six();
  //  f_digit_tens_seven();
    f_digit_tens_eight();
}
