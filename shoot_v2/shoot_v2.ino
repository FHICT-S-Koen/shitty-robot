#include <AFMotor.h>

AF_DCMotor dc_motor_1(1);
AF_DCMotor dc_motor_2(2);

void setup() {
	dc_motor_1.setSpeed(200);
	dc_motor_1.run(RELEASE);

  dc_motor_2.setSpeed(200);
	dc_motor_2.run(RELEASE);
}

void loop() {
	// dc_motor_1.run(BACKWARD);
	// dc_motor_2.run(BACKWARD);
}
