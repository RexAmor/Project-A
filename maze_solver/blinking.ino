#define IN 0
#define OUT 1
#define one_ms 16000

int power(int base, int exponent) { // power function
  if (exponent==0) return 1;
  int result = 1;
  for (int i = 0; i<exponent; i++)
    result*=base;
  return result;
}

void setPin(int pin, int mode) { // set pin mode (IN or OUT)
  if (mode==OUT) {
    if (pin<=7) DDRD = DDRD|power(2, pin);
    else DDRB = DDRB|power(2, pin-8);
  } else {
    if (pin<=7) DDRD = DDRD&(255-power(2, pin));
    else DDRB = DDRB&(255-power(2, pin-8));
  }
}

void dWrite(int pin, int value) {
  if (pin<=7) PORTD = value==1 ? PORTD|power(2, pin) : PORTD&(255-power(2, pin));
  else PORTB = value==1 ? PORTB|power(2, pin-8) : PORTB&(255-power(2, pin-8));
}

void setup() {
  // put your setup code here, to run once:
  setPin(13, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
  dWrite(13, 1);
  delay(1000);
  dWrite(13, 0);
  delay(1000);
}
