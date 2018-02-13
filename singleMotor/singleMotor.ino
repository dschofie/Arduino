
    int InA1 = 7;
    int InB1 = 8;
    int PWM1 = 3;  //PWM1 connects to pin 3
    int PWM1_val = 127; //(25% = 64; 50% = 127; 75% = 191; 100% = 255)

    void setup() {
    Serial.begin(9600);
    pinMode(InA1, OUTPUT);
    pinMode(InB1, OUTPUT);
    pinMode(PWM1, OUTPUT);
    }

    void loop() {
    digitalWrite(InA1, HIGH);
    digitalWrite(InB1, LOW);
    analogWrite(PWM1, PWM1_val);
    }

