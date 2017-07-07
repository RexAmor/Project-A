#define IN1  7
#define IN2 6
#define IN3 5
#define IN4 4
#define MAX_SPEED 255 //từ 0-255
#define MIN_SPEED 0

void setup() {
  DDRB = DDRB&0b11100000;
  DDRD = DDRB|0b00001111;
  Serial.begin(9600);
}

void motor_1_Dung() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
 
void motor_2_Dung() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void motor_1_Tien(int speed) { //speed: từ 0 - MAX_SPEED
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  digitalWrite(IN1, HIGH);// chân này không có PWM
  analogWrite(IN2, 255 - speed);
}
 
void motor_1_Lui(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  digitalWrite(IN1, LOW);// chân này không có PWM
  analogWrite(IN2, speed);
}
 
void motor_2_Tien(int speed) { //speed: từ 0 - MAX_SPEED
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  analogWrite(IN3, speed);
  digitalWrite(IN4, LOW);// chân này không có PWM
}
 
void motor_2_Lui(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  analogWrite(IN4, 255 - speed);
  digitalWrite(IN3, HIGH);// chân này không có PWM
}

void goStraight() {
  motor_1_Tien(MAX_SPEED);
  motor_2_Tien(MAX_SPEED);
}

void forwardALittle() {
  motor_1_Tien(MAX_SPEED);
  motor_2_Tien(MAX_SPEED);
    delay(200);
}

void turnLeft() {
   motor_1_Lui(MAX_SPEED);
   motor_2_Tien(MAX_SPEED);
   delay(500);
}

void turnRight() {
   motor_2_Lui(MAX_SPEED);
   motor_1_Tien(MAX_SPEED);
   delay(500);
}

void Uturn() {
  turnLeft();
  turnLeft();
}

void slightLeft() {
   motor_1_Tien(200);
   motor_2_Tien(MAX_SPEED);
}

void mediumLeft() {
   motor_1_Tien(150);
   motor_2_Tien(MAX_SPEED);
}

void hardLeft() {
   motor_1_Tien(100);
   motor_2_Tien(MAX_SPEED);
}

void slightRight() {
   motor_2_Tien(200);
   motor_1_Tien(MAX_SPEED);
}

void mediumRight() {
   motor_2_Tien(150);
   motor_1_Tien(MAX_SPEED);
}

void hardRight() {
   motor_2_Tien(100);
   motor_1_Tien(MAX_SPEED);
}


byte s1, s2, s3, s4, s5;
int s;

void loop() {
  s1 = digitalRead(12);
  s2 = digitalRead(11);
  s3 = digitalRead(10);
  s4 = digitalRead(9);
  s5 = digitalRead(8);
  s = s1*1+s2*2+s3*4+s4*8+s5*16;
  if (s==0b11011) goStraight();
  else if (s==0b10011) slightLeft();
  else if (s==0b10111) mediumLeft();
  else if (s==0b01111||s==0b00111) hardLeft();
  else if (s==0b11001) slightRight();
  else if (s==0b11101) mediumRight();
  else if (s==0b11110||s==0b11100) hardRight();
  else {
    if (s==0b11111) Uturn();
    if (s==0b00100||0b00111||0b00011) turnLeft();
    if (s==0b11100) turnRight();
    if (s=0b00000) {
      forwardALittle();
      if (s=0b00000) {motor_1_Dung();motor_2_Dung();}
      if (s=0b11011) turnLeft();
    }
  }
  Serial.print(s1);
}
