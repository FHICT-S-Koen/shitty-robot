
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
int buttonPin = A2;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(buttonPin, HIGH);  // Enable internal pull-up resistor
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
}

void loop() {
  while(true) {
    int reading = digitalRead(buttonPin);

    Serial.println(reading);

    if (reading > 0) {
      break;
    }
  }
  while(true) {
    int reading = digitalRead(buttonPin);
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 120); // PWM Speed Control
  analogWrite(E2, 120); // PWM Speed Control

    if (reading > 0) {
      break;
    }
  }
}
