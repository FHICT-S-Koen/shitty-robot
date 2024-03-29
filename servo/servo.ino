#include <Servo.h>

Servo servo;

void setup() {
	// servo.attach(10);
}

void loop() {
  // servo.write(90);

  // while(true) {
    servo.write(90);
    delay(2000);
    servo.write(-90);
    delay(2000);
  // }
}
