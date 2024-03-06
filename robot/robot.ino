#include <SPI.h>

//Add the SdFat Libraries
#include <SdFat.h>
#include <SdFatUtil.h>

//and the MP3 Shield Library
#include <SFEMP3Shield.h>

/**
 * \brief Object instancing the SdFat library.
 *
 * principal object for handling all SdCard functions.
 */
SdFat sd;

/**
 * \brief Object instancing the SFEMP3Shield library.
 *
 * principal object for handling all the attributes, members and functions for the library.
 */
SFEMP3Shield MP3player;

/**
 * Arduino PWM DC motor speed control:
 * E1 = M1-
 * M1 = M1+
 * E2 = M2-
 * M2 = M2+
 */
int E1 = 5;
int M1 = 4;
int E2 = 6;
int M2 = 7;
int buttonPin = 2;

void setup()
{
  Serial.begin(115200);
  // initialize the pushbutton pin as an input:
  // pinMode(buttonPin, INPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

  //Initialize the SdCard.
  if(!sd.begin(SD_SEL, SPI_FULL_SPEED)) sd.initErrorHalt();
  // depending upon your SdCard environment, SPI_HAVE_SPEED may work better.
  if(!sd.chdir("/")) sd.errorHalt("sd.chdir");

  uint8_t result = MP3player.begin();
  MP3player.setVolume(0,0);
  if(result != 0) {
    Serial.print(F("Error code: "));
    Serial.print(result);
    Serial.println(F(" when trying to start MP3 player"));
    if( result == 6 ) {
      Serial.println(F("Warning: patch file not found, skipping.")); // can be removed for space, if needed.
      Serial.println(F("Use the \"d\" command to verify SdCard can be read")); // can be removed for space, if needed.
    }
  }
}

void loop()
{
  bool start = true;

  // Start game
  if (!start) {
    // Zijn jullie ready?
    playTrack(1);
    delay(10000);
    return;
  }

  // Het spel gaat starten!! 3,2,1 GO! 
  // playTrack(9);

  // Go Go Go! 
  // Sneller! 
  // Kan je ze allemaal vinden?

  time
  while() 
  playTrack(random(3, 6));

  // delay(1000);

  // Tijdens het spel 






  // Eind spel 

  // Alle balletjes zijn geschoten! 
  // Hebben jullie alles gevonden? 
  // Hervul me om een nieuw spel te starten. 

  shoot(5000);
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

void shoot(int ms) 
{
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 255);   //PWM Speed Control
  analogWrite(E2, 255);   //PWM Speed Control
  delay(ms);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
}

void playTrack(uint8_t track)
{
  uint8_t result = MP3player.playTrack(track);

  if(result != 0) {
    Serial.print(F("Error code: "));
    Serial.print(result);
    Serial.println(F(" when trying to play track"));
  } else {
    Serial.print(F("Playing: "));
    Serial.println(track);


    // MP3player.stopTrack();


    // //we can get track info by using the following functions and arguments
    // //the functions will extract the requested information, and put it in the array we pass in
    // MP3player.trackArtist((char*)&artist);
    // MP3player.trackAlbum((char*)&album);

    // //print out the arrays of track information
    // Serial.write((byte*)&title, 30);
    // Serial.println();
    // Serial.print(F("by:  "));
    // Serial.write((byte*)&artist, 30);
    // Serial.println();
    // Serial.print(F("Album:  "));
    // Serial.write((byte*)&album, 30);
    // Serial.println();
  }
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


