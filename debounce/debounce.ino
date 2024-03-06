const int buttonPin = A2;  // Analog pin the button is connected to
int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // Previous state of the button
unsigned long lastDebounceTime = 0;  // Time of the last button state change
unsigned long debounceDelay = 30;  // Debounce time in milliseconds

void setup() {
  pinMode(buttonPin, INPUT);
  // digitalWrite(buttonPin, HIGH);  // Enable internal pull-up resistor
  Serial.begin(115200); // Initialize serial communication
}

void loop() {
  int reading = analogRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();  // Reset debounce timer
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState > 0) {
        Serial.println("Button pressed");
      }
    }
  }
  lastButtonState = reading;
}
