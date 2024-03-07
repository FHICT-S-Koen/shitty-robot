const int buttonPin = A2;  // Analog pin the button is connected 

void setup() {
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);  // Enable internal pull-up resistor
  Serial.begin(115200); // Initialize serial communication
}

void loop() {
  int reading = digitalRead(buttonPin);
  if (reading > 0) {
		Serial.println("Button pressed");
	}
}
