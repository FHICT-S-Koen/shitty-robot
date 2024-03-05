//Arduino PWM Speed Control：
int E1 = 5; // M1-
int M1 = 4; // M1+
int E2 = 6; // M2-
int M2 = 7; // M2+
int buttonPin = 2;

void setup()
{
  //   // initialize the LED pin as an output:
  // pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  // pinMode(buttonPin, INPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
}

void loop()
{
  shoot();
  // digitalWrite(M1,HIGH);
  // digitalWrite(M2, HIGH);
  // analogWrite(E1, 255);   //PWM Speed Control
  // analogWrite(E2, 255);   //PWM Speed Control

  // buttonState = digitalRead(buttonPin);

  // if (buttonState == HIGH) {
  //   shoot()
  // }

  // int value;
  // for(value = 0 ; value <= 255; value+=5)
  // {
  //   digitalWrite(M1,HIGH);
  //   digitalWrite(M2, HIGH);
  //   analogWrite(E1, value);   //PWM Speed Control
  //   analogWrite(E2, value);   //PWM Speed Control
  //   delay(30);
  // }
}

void shoot() 
{
  digitalWrite(M1,HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 255);   //PWM Speed Control
  analogWrite(E2, 255);   //PWM Speed Control
}


// /**set control port**/
// // const int E1Pin = 10;
// // const int M1Pin = 12;
// // const int E2Pin = 11;
// // const int M2Pin = 13;

// const int E1Pin = 5;
// const int M1Pin = 4;
// const int E2Pin = 6;
// const int M2Pin = 7;

// /**inner definition**/
// typedef struct {
//   byte enPin;
//   byte directionPin;
// } MotorContrl;

// const int M1 = 0;
// const int M2 = 1;
// const int MotorNum = 2;

// const MotorContrl MotorPin[] = { {E1Pin, M1Pin}, {E2Pin, M2Pin} } ;

// const int Forward = LOW;
// const int Backward = HIGH;

// /**program**/
// void setup() {
//   initMotor();
// }

// void loop() {
//   int value;
//   /**test M1 **/
//   setMotorDirection( M1, Forward );
//   setMotorSpeed( M1, 100 );
//   delay(1000);
//   setMotorSpeed( M1, 0 );
//   delay(100);

//   setMotorDirection( M1, Backward );
//   setMotorSpeed( M1, 50 );
//   delay(1000);
//   setMotorSpeed( M1, 0 );
//   delay(100);

//   /**test M2**/
//   setMotorDirection( M2, Backward );
//   for (value = 0 ; value <= 100; value += 5) {
//     setMotorSpeed( M2, value );
//     delay(100);
//   }
//   setMotorSpeed( M2, 0 );
//   setMotorDirection( M2, Forward );
//   for (value = 0 ; value <= 100; value += 5) {
//     setMotorSpeed( M2, value );
//     delay(100);
//   }
//   setMotorSpeed( M2, 0 );
// }

// /**functions**/
// void initMotor( ) {
//   int i;
//   for ( i = 0; i < MotorNum; i++ ) {
//     digitalWrite(MotorPin[i].enPin, LOW);

//     pinMode(MotorPin[i].enPin, OUTPUT);
//     pinMode(MotorPin[i].directionPin, OUTPUT);
//   }
// }

// /**  motorNumber: M1, M2
// direction:          Forward, Backward **/
// void setMotorDirection( int motorNumber, int direction ) {
//   digitalWrite( MotorPin[motorNumber].directionPin, direction);
// }

// /** speed:  0-100   * */
// inline void setMotorSpeed( int motorNumber, int speed ) {
//   analogWrite(MotorPin[motorNumber].enPin, 255.0 * (speed / 100.0) ); //PWM
// }


// // #include <Stepper.h>

// // const int STEPS = 200;

// // // create an instance of the stepper class, specifying

// // // the number of steps of the motor and the pins it's

// // // attached to

// // Stepper stepper(STEPS, 5, 4);

// // void setup() {
// //   // set the speed at 60 rpm:

// //   stepper.setSpeed(60);

// //   // initialize the serial port:

// //   Serial.begin(9600);
// // }


// // void loop() {
// //  // step one revolution  in one direction:

// //   Serial.println("clockwise");

// //   stepper.step(STEPS);

// //   delay(500);


// //   // step one revolution in the other direction:

// //   // Serial.println("counterclockwise");

// //   // stepper.step(-STEPS);

// //   delay(500);
// // }


