int setPoint = 55;
String readString;
int InA1 = 7;
int InB1 = 8;
int PWM1 = 3;  //PWM1 connects to pin 3
int PWM1_val = 64; //(25% = 64; 50% = 127; 75% = 191; 100% = 255)

const int motorA1 = 7;
const int motorB1 = 8;
const int motorPWM1 = 3;
const int motorA2 = 10;
const int motorB2 = 11;
const int motorPWM2 = 9;

const int pingPinL = 2;
const int pingPinR = 4;

int leftSpeed = 40;
int rightSpeed = 50;

int InA2 = 2;
int InB2 = 4;
int PWM2 = 5;

int PMW_25p = 64;
int PMW_50p = 127;
int PMW_75p = 191;
int PMW_100p = 255;

const int pingPinFront = 12;
const int pingPinRight = 10;
const int pingPinLeft = 11;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(14400);  // initialize serial communications at 14400 bps
  pinMode(InA1, OUTPUT);
  pinMode(InB1, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(InA2, OUTPUT);
  pinMode(InB2, OUTPUT);
  pinMode(PWM2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // serial read section
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

  while (!Serial.available()) {
    hold();
  }
  
  while (Serial.available()) // this will be skipped if no data present, leading to                       // the code sitting in the delay function below
  {
    delay(30);  //delay to allow buffer to fill
    if (Serial.available() > 0)
    {
      char c = Serial.read();  //gets one byte from serial buffer

      //Move backwards if anything is in the way
      if (cmL < 10 || cmR < 10) {
        hold();
      } else if (c == 'L')
      {
        counterclockwise();
        //        Serial.println("forward");
      } else if (c == 'R') {
        clockwise();
        //        Serial.println("moving cw");
      } else if (c == 'S') {
        hold();
      } else if (c == 'F'){
        forward();
        //        Serial.println("Moving ccw and in else block gg");
      } else {
        hold();
      }
      readString += c; //makes the string readString
      if (readString.length() > 0)
      {
        //        Serial.print("Arduino received: ");
        //        Serial.println(readString); //see what was received
      }
    }
  }

  // serial write section

  //  char ard_sends = '1';
  //  Serial.print("Arduino sends: ");
  //  Serial.println(ard_sends);
  //  Serial.print("\n");
  //  Serial.flush();
}

void reverse() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB2, HIGH);
}
void forward() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB2, LOW);
}
void counterclockwise() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB2, LOW);
}
void clockwise() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB2, HIGH);
}
void hold() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB2, LOW);
}
long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
