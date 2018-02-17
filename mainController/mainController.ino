int InA1 = 7;
int InB1 = 8;
int PWM1 = 3;  //PWM1 connects to pin 3
int PWM1_val = 64; //(25% = 64; 50% = 127; 75% = 191; 100% = 255)

int InA2 = 2;
int InB2 = 4;
int PWM2 = 5;

int PMW_25p = 64;
int PMW_50p = 127;
int PMW_75p = 191;
int PMW_100p = 255;

const int pingPinFront = 12;
const int pingPinRight = ?;
const int pingPinLeft = ?;

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
//  spinClockwise(PMW_50p,1000);
////  delay(1000);
//  spinCounterClockwise(PMW_25p, 1000);
  //delay(1000);
//  forwards(PMW_75p, 1000);
//  delay(1000);
//  forwards(0);
//  delay(10000);
//digitalWrite(InA1, HIGH);
//digitalWrite(InB1, LOW);
//digitalWrite(InA2, LOW);
//digitalWrite(InB2, HIGH);
//analogWrite(PWM2, PWM2_val);
//analogWrite(PWM1, PWM1_val);

  long durationFront, inchesFront, cmFront;
  long durationLeft, inchesLeft;
  long durationRight, inchesRight;
  
  configurePingSensors();

  pinMode(pingPinFront, INPUT);
  durationFront = pulseIn(pingPinFront, HIGH);
  pinMode(pingPinRight, INPUT);
  durationFront = pulseIn(pingPinFront, HIGH);
  pinMode(pingPinLeft, INPUT);
  durationFront = pulseIn(pingPinFront, HIGH);
  
  // convert the time into a distance
  inchesFront = microsecondsToInches(durationFront);
  cmFront = microsecondsToCentimeters(durationFront);

  inchesLeft = microsecondsToInches(durationLeft);
  inchesRight = microsecondsToInches(durationRight);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  if(inchesFront < 4)
  {
    if(inchesLeft > inchesRight){
      spinCounterClockwise(PMW_50p, 500);
    } else {
      spinClockwise(PMW_50p, 500);
    }
//    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    backwards-(PMW_50p,1000);
    delay(100);                       // wait for a second
//      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//      delay(100); 
  } else {
    forwards(PMW_50p,1000);
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);
  }
}

void spinClockwise(int rotation_speed, int waitTime) {
  digitalWrite(InA1, HIGH);
  digitalWrite(InB1, LOW);
  digitalWrite(InA2, HIGH);
  digitalWrite(InB2, LOW);
  analogWrite(PWM2, rotation_speed);
  analogWrite(PWM1, rotation_speed);
  delay(waitTime);
  analogWrite(PWM2, 0);
  analogWrite(PWM1, 0);
  delay(waitTime);
}

void configurePingSensors(){

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPinFront, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPinFront, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPinFront, LOW);

  pinMode(pingPinLeft, OUTPUT);
  digitalWrite(pingPinLeft, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPinLeft, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPinLeft, LOW);

  pinMode(pingPinRight, OUTPUT);
  digitalWrite(pingPinRight, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPinRight, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPinRight, LOW);
}

void spinCounterClockwise(int rotation_speed, int waitTime) {
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, HIGH);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, HIGH);
  analogWrite(PWM2, rotation_speed);
  analogWrite(PWM1, rotation_speed);
  delay(waitTime);
  analogWrite(PWM2, 0);
  analogWrite(PWM1, 0);
  delay(waitTime);
}

void forwards(int direction_speed) {
  digitalWrite(InA1, HIGH);
  digitalWrite(InB1, LOW);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, HIGH);
  analogWrite(PWM2, direction_speed);
  analogWrite(PWM1, direction_speed);
}

void forwards(int direction_speed, int waitTime) {
  digitalWrite(InA1, HIGH);
  digitalWrite(InB1, LOW);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, HIGH);
  analogWrite(PWM2, direction_speed);
  analogWrite(PWM1, direction_speed);
  delay(waitTime);
  analogWrite(PWM2, 0);
  analogWrite(PWM1, 0);
  
}

void backwards(int direction_speed, int waitTime) {
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, HIGH);
  digitalWrite(InA2, HIGH);
  digitalWrite(InB2, LOW);
  analogWrite(PWM2, direction_speed);
  analogWrite(PWM1, direction_speed);
  delay(waitTime);
  analogWrite(PWM2, 0);
  analogWrite(PWM1, 0);
  
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
