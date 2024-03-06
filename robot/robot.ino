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
  pinMode(buttonPin, INPUT_PULLUP);
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
  bool started = true;

  // Start game
  if (!started) {
    // Zijn jullie ready?
    playTrack(1);
    delay(1000);

    while(!started) {
      int currentState = digitalRead(buttonPin);
      Serial.print(F("Starting: "));
      Serial.println(currentState);
      if (currentState == HIGH) {
        started = true;
        break;
      }
    }
    return;
  }

  // Het spel gaat starten!! 3,2,1 GO! 
  playTrack(2);

  shoot(10000);

  bool stop = true;
  
  // Tijdens het spel 
  while(stop) {
    // int currentState = digitalRead(buttonPin);
    // if (currentState == HIGH) {
    //   stop = true;
    //   break;
    // }
    // Go Go Go! 
    // Sneller! 
    // Kan je ze allemaal vinden?
    playTrack(9);
    delay(10000);
    MP3player.stopTrack();
    playTrack(random(3, 6));
    delay(1000);
  }
  // start = false;

  delay(1000);
  // Eind spel 

  // SCRAP - Alle balletjes zijn geschoten! 

  // Hebben jullie alles gevonden? 
  playTrack(7);
  // Hervul me om een nieuw spel te starten. 
  playTrack(8);
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
  }
}

#include <Stepper.h>

const int STEPS = 200;

// create an instance of the stepper class, specifying

// the number of steps of the motor and the pins it's

// attached to

Stepper stepper(STEPS, 5, 4);

void setup() {
  // set the speed at 60 rpm:

  stepper.setSpeed(60);

  // initialize the serial port:

  Serial.begin(9600);
}


void loop() {
 // step one revolution  in one direction:

  Serial.println("clockwise");

  stepper.step(STEPS);

  delay(500);


  // step one revolution in the other direction:

  // Serial.println("counterclockwise");

  // stepper.step(-STEPS);

  delay(500);
}


