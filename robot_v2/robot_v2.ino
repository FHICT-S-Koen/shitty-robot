const int buttonPin = A2;

// Motors
#include <Servo.h>
#include <AFMotor.h>

Servo servo;

AF_DCMotor dc_motor_1(1);
AF_DCMotor dc_motor_2(2);
// DC motors PWM speed control
const int SPEED = 100;

void setup() {
  Serial.begin(115200);

  pinMode(buttonPin, INPUT_PULLUP);

	servo.attach(10);

	dc_motor_1.setSpeed(SPEED);
  dc_motor_2.setSpeed(SPEED);
}

void loop()
{
  dc_motor_1.run(RELEASE);
  dc_motor_2.run(RELEASE);

  bool started = false;

  Serial.println("START GAME?");
  while(true) {
    int reading = analogRead(buttonPin);
    Serial.println(reading);
    if (reading < 20) {
      break;
    }
  }
	Serial.println("STARTED");

	dc_motor_1.run(FORWARD);
	dc_motor_2.run(FORWARD);

  int lastButtonState = 1;
	while (true)
	{
    int reading = digitalRead(buttonPin);
    Serial.println(reading);
    if (reading == 0 && lastButtonState == 0) {
      break;
    }
    lastButtonState = reading;

	  dc_motor_1.setSpeed(0);
	  dc_motor_2.setSpeed(0);
		servo.write(90);
		delay(500);

    dc_motor_1.setSpeed(SPEED);
	  dc_motor_2.setSpeed(SPEED);
		delay(4000);

    reading = digitalRead(buttonPin);
    Serial.println(reading);
    if (reading == 0 && lastButtonState == 0) {
      break;
    }
    lastButtonState = reading;

	  dc_motor_1.setSpeed(0);
	  dc_motor_2.setSpeed(0);
		servo.write(-90);
		delay(500);

    dc_motor_1.setSpeed(SPEED);
	  dc_motor_2.setSpeed(SPEED);
		delay(4000);
	}
}
