
#include <Stepper.h>

const int STEPS = 50;

Stepper stepper(STEPS, 8, 9, 10, 11);

void setup() {
  // set the speed at 60 rpm:
  stepper.setSpeed(50);

  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
 // step one revolution  in one direction:
  stepper.step(STEPS);
  // delay(2000);
  // stepper.step(-STEPS);
  // delay(2000);
}
