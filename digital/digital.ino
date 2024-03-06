const int buttonPin = 2;  // Analog pin the button is connected to
int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // Previous state of the button
unsigned long lastDebounceTime = 0;  // Time of the last button state change
unsigned long debounceDelay = 50;  // Debounce time in milliseconds

void setup() {
  pinMode(buttonPin, INPUT);
  // digitalWrite(buttonPin, HIGH);  // Enable internal pull-up resistor
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  int reading = digitalRead(buttonPin);

  // Check if the button state has changed
  if (reading != lastButtonState) {
    Serial.println("Reset debounce timer");
    delay(100); 
    lastDebounceTime = millis();  // Reset debounce timer
  }

  // If debounce time has passed, update the button state
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has been stable, update lastButtonState
    delay(100); 
    Serial.println("stable"); 

    if (reading != buttonState) {
      buttonState = reading;
      

      // Button pressed
      if (buttonState == HIGH) {
        Serial.println("Button pressed"); // Print message to serial monitor
        // Handle button press
        // Add your code here
      }
    }
  }
  lastButtonState = reading;
}
