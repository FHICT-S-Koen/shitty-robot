
#include <Stepper.h>

const int STEPS = 200;

Stepper stepper(STEPS, 4, 5, 6, 7);

void setup() {
  // set the speed at 60 rpm:
  stepper.setSpeed(60);

  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
 // step one revolution  in one direction:
  stepper.step(STEPS);
  delay(500);
}
