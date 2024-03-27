#include <Servo.h> 
#include <AFMotor.h>

Servo servo;

AF_DCMotor dc_motor_1(3);
AF_DCMotor dc_motor_2(4);

void setup() {
	servo.attach(10);

	dc_motor_1.setSpeed(200);
	dc_motor_1.run(RELEASE);

  dc_motor_2.setSpeed(200);
	dc_motor_2.run(RELEASE);
}

int pos = 0;	// variable to store the servo position

void loop() {
	dc_motor_1.run(FORWARD);
	dc_motor_2.run(FORWARD);
  // servo.write(90);

  // while(true) {
  //   servo.write(90);
  //   delay(2000);
  //   servo.write(-90);
  //   delay(2000);
  // }
}
