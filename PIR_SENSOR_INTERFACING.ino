/******I/O Pins****/
const uint8_t c_pir_sensor = 2;  //PIR Sensor is attached to pin D2
const uint8_t c_led_pin = 4;     //Led is connected to Pin D4
/******Interrupt Flag*****/
volatile uint8_t vo_pir_flag = 0; //volatile variable flag to change during interrupt

void setup()
{
//  pinMode(c_pir_sensor, INPUT);     //
  pinMode(c_led_pin, OUTPUT);         //Making led pin as the output
  attachInterrupt(digitalPinToInterrupt(c_pir_sensor ), f_ISR, RISING); //making pir pin as the interrupt pin
}

void loop()
{
  /*****Normal routine*****/
  digitalWrite(c_led_pin, HIGH);
  delay(500);
  digitalWrite(c_led_pin, LOW);
  delay(500);
  /******When ever interrupt flag is set high******/
  if (vo_pir_flag == 1)
  {
    digitalWrite(c_led_pin, HIGH);
    delay(2000);
    vo_pir_flag = 0;
  }
  else
  {
    digitalWrite(c_led_pin, LOW);
  }
}

void f_ISR()
{
  vo_pir_flag = 1;
}
