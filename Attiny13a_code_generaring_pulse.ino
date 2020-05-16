/*
This code simply generates a pulse of 10us on the two pins if atiny 13a

Pin configuration of Atiny13a

Atiny13a        Function              Arduino

1              PB5(RST/ADC0)            A0/5
2              PB3(ADC3)                A3/3
3              PB2(ADC2)                A2/4
4                 GND                    GND
5              PB0(MOSI/OCOA)             0
6              PB1(MISO/OCOB/INT0)        1
7              PB2(SCK/ADC1)            A1/2
8                 Vcc                    VCC

PIN IN BIT(PORT/DDR)



*/
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
