int const c_pulse=10;

void setup() {
//pinMode(0,OUTPUT);
//pinMode(1,OUTPUT);
DDRB=B00011111; //Set all pins to output
}

void loop()
{
while(1){
PORTB=B00000001;
delayMicroseconds(c_pulse);
PORTB=B00000010;
delayMicroseconds(c_pulse);
}
}
