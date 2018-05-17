const int motorA1 = 7;
const int motorB1 = 8;
const int motorPWM1 = 3;
const int motorA2 = 10;
const int motorB2 = 11;
const int motorPWM2 = 9;

const int pingPinL = 2;
const int pingPinR = 4;

int leftSpeed = 100;
int rightSpeed = 120;

int distAway = 50;
int trig = 0;
void setup() {
  pinMode(motorA1, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  analogWrite(motorPWM1, rightSpeed);
  analogWrite(motorPWM2, leftSpeed);
  long durationL, cmL, durationR, cmR;

  //Left Ping Sensor
  pinMode(pingPinL, OUTPUT);
  digitalWrite(pingPinL, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPinL, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPinL, LOW);

  pinMode(pingPinL, INPUT);
  durationL = pulseIn(pingPinL, HIGH);

  cmL = microsecondsToCentimeters(durationL);

  //Right Ping Sensor
  pinMode(pingPinR, OUTPUT);
  digitalWrite(pingPinR, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPinR, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPinR, LOW);

  pinMode(pingPinR, INPUT);
  durationR = pulseIn(pingPinR, HIGH);

  cmR = microsecondsToCentimeters(durationR);

  Serial.print(cmL);
  Serial.print("cm on left,");
  Serial.print(cmR);
  Serial.print("cm on right");

  if(cmR > distAway && cmL > distAway && trig == 0){
    forward(); Serial.print("\tFORWARD");
  }else if(cmR <= distAway && cmL <= distAway && trig == 0){
    counterclockwise(); trig = 1; Serial.print("\t\t\tToo close");
  }else if(cmR > distAway && cmL <= distAway && trig == 0){
    clockwise(); Serial.print("\t\t\t\t\tCLOCKWISE");
  }else if(cmR <= distAway && cmL > distAway && trig == 0){
    counterclockwise(); Serial.print("\t\t\t\t\t\t\tCOUNTER");
  }else if(trig == 1 && cmR > distAway && cmL > distAway){
    trig = 0;
  }
  Serial.println();

  delay(50);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

void reverse(){
  digitalWrite(motorA1,LOW);
  digitalWrite(motorB1,HIGH);
  digitalWrite(motorA2,LOW);
  digitalWrite(motorB2,HIGH);
}
void forward(){
  digitalWrite(motorA1,HIGH);
  digitalWrite(motorB1,LOW);
  digitalWrite(motorA2,HIGH);
  digitalWrite(motorB2,LOW);
}
void counterclockwise(){
  digitalWrite(motorA1,LOW);
  digitalWrite(motorB1,HIGH);
  digitalWrite(motorA2,HIGH);
  digitalWrite(motorB2,LOW);
}
void clockwise(){
  digitalWrite(motorA1,HIGH);
  digitalWrite(motorB1,LOW);
  digitalWrite(motorA2,LOW);
  digitalWrite(motorB2,HIGH);
}
void hold(){
  digitalWrite(motorA1,LOW);
  digitalWrite(motorB1,LOW);
  digitalWrite(motorA2,LOW);
  digitalWrite(motorB2,LOW);
}
