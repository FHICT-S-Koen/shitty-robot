
/**
 * Arduino PWM DC motor speed control:
 * E1 = M1-
 * M1 = M1+
 * E2 = M2-
 * M2 = M2+
 */
int E1 = 5;
int M1 = 4;
int E2 = 6;
int M2 = 7;
int buttonPin = 2;

void setup() {
  Serial.begin(115200);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
}

void loop() {
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 255); // PWM Speed Control
  analogWrite(E2, 80); // PWM Speed Control
}
