int InA1 = 7;
int InB1 = 8;
int PWM1 = 3;  //PWM1 connects to pin 3
int PWM1_val = 64; //(25% = 64; 50% = 127; 75% = 191; 100% = 255)

int InA2 = 2;
int InB2 = 1;
int PWM2 = 5;

int PMW_25p = 64;
int PMW_50p = 127;
int PMW_75p = 191;
int PMW_100p = 255;

void setup() {
Serial.begin(9600);
pinMode(InA1, OUTPUT);
pinMode(InB1, OUTPUT);
pinMode(PWM1, OUTPUT);
pinMode(InA2, OUTPUT);
pinMode(InB2, OUTPUT);
pinMode(PWM2, OUTPUT);
}

void loop() {
  spinClockwise(PMW_25p,1000);
//  delay(1000);
  spinCounterClockwise(PMW_25p, 1000);
  delay(1000);
  forwards(PMW_75p, 1000);
  delay(1000);
  forwards(0);
  delay(10000);
//digitalWrite(InA1, HIGH);
//digitalWrite(InB1, LOW);
//digitalWrite(InA2, LOW);
//digitalWrite(InB2, HIGH);
//analogWrite(PWM2, PWM2_val);
//analogWrite(PWM1, PWM1_val);
}

void spinClockwise(int rotation_speed, int waitTime) {
  digitalWrite(InA1, HIGH);
  digitalWrite(InB1, LOW);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, HIGH);
  analogWrite(PWM2, rotation_speed);
  analogWrite(PWM1, rotation_speed);
  delay(waitTime);
}

void spinCounterClockwise(int rotation_speed, int waitTime) {
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, HIGH);
  digitalWrite(InA2, HIGH);
  digitalWrite(InB2, LOW);
  analogWrite(PWM2, rotation_speed);
  analogWrite(PWM1, rotation_speed);
  delay(waitTime);
  analogWrite(PWM2, 0);
  analogWrite(PWM1, 0);
}

void forwards(int direction_speed) {
  digitalWrite(InA1, HIGH);
  digitalWrite(InB1, LOW);
  digitalWrite(InA2, HIGH);
  digitalWrite(InB2, LOW);
  analogWrite(PWM2, rotation_speed);
  analogWrite(PWM1, rotation_speed);
}

void forwards(int direction_speed, int waitTime) {
  digitalWrite(InA1, HIGH);
  digitalWrite(InB1, LOW);
  digitalWrite(InA2, HIGH);
  digitalWrite(InB2, LOW);
  analogWrite(PWM2, rotation_speed);
  analogWrite(PWM1, rotation_speed);
  dealy(waitTime);
  analogWrite(PWM2, 0);
  analogWrite(PWM1, 0);
  
}

