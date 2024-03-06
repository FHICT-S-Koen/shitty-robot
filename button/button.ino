int buttonPin = 2;

void setup()
{
  Serial.begin(115200);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop()
{
  bool started = false;

  while(!started) {
    int currentState = digitalRead(buttonPin);
    Serial.print(F("Starting: "));
    Serial.println(currentState);
    if (currentState == HIGH) {
      started = true;
      break;
    }
  }
  // if (!started) {
  //   return;
  // }
	Serial.println(F("STARTED"));
  delay(1000);
}