#include <Stepper.h>
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>

const int buttonPin = A2;
int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // Previous state of the button
unsigned long lastDebounceTime = 0;  // Time of the last button state change
unsigned long debounceDelay = 30;  // Debounce time in milliseconds

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
// MP3 Player volume 0=max, 255=lowest (off)
const uint8_t volume = 0;

/**
 * Arduino PWM DC motors
 */
const int E1 = 5; // M1- 
const int M1 = 4; // M1+
const int E2 = 6; // M2-
const int M2 = 7; // M2+
// DC motors PWM speed control
const int SPEED = 255;

/**
 * Arduino stepper motor
 */
const int STEPS = 200;
const int RPM = 60;
Stepper stepper(STEPS, 4, 5, 6, 7);

void setup()
{
  Serial.begin(115200);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

  stepper.setSpeed(RPM);

  initSD();
  initMP3Player();
}

void loop()
{
  while(true) {
    int reading = digitalRead(buttonPin);

    if (reading > 0) {
      break;
    }
  }
  bool started = false;

  Serial.println(F("START GAME?"));
  if (!started) {
    // Zijn jullie ready?
    playTrack(1);
    delay(2000);

    while(!started) {
      int reading = digitalRead(buttonPin);

      if (reading != lastButtonState) {
        // Reset debounce timer
        lastDebounceTime = millis();
      }

      if ((millis() - lastDebounceTime) > debounceDelay) {

        if (reading != buttonState) {
          buttonState = reading;
          
          if (buttonState > 0) {
            break;
          }
        }
      }
      lastButtonState = reading;
    }
  }
	Serial.println(F("STARTED"));

  // Het spel gaat starten!! 3,2,1 GO! 
  playTrack(2);
  delay(5000);

  Serial.println(F("SHOOTING"));
  for (int i = 0; i <= 10; i++) {
    shoot(3000);
    stepper.step(STEPS);
  }

  Serial.println(F("BALLS SHOT"));
  Serial.println(F("START GATHERING"));

  // Tijdens het spel
  while(true) {
    int reading = digitalRead(buttonPin);

    if (reading > 0) {
      break;
    }

    // Music
    playTrack(9);
    delay(10000);
    MP3player.stopTrack();
    // Go Go Go! 
    // Sneller! 
    // Kan je ze allemaal vinden?
    playTrack(random(3, 6));
    delay(1500);
  }

  // Eind spel
  Serial.println(F("GAME ENDED"));
  delay(1000);

  // SCRAP - Alle balletjes zijn geschoten! 

  // Hebben jullie alles gevonden? 
  playTrack(7);
  delay(3000);

  // Hervul me om een nieuw spel te starten. 
  playTrack(8);
}

void shoot(int ms) 
{
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  // PWM Speed Control
  analogWrite(E1, SPEED);
  analogWrite(E2, SPEED);
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
    Serial.print(F("Playing track: "));
    Serial.println(track);
  }
}

void initSD() {
  //Initialize the SdCard.
  if(!sd.begin(SD_SEL, SPI_FULL_SPEED)) sd.initErrorHalt();
  // depending upon your SdCard environment, SPI_HAVE_SPEED may work better.
  if(!sd.chdir("/")) sd.errorHalt("sd.chdir");
}

void initMP3Player() {
  uint8_t result = MP3player.begin();
  if(result != 0) {
    Serial.print(F("Error code: "));
    Serial.print(result);
    Serial.println(F(" when trying to start MP3 player"));
    // if( result == 6 ) {
    //   Serial.println(F("Warning: patch file not found, skipping.")); // can be removed for space, if needed.
    // }
  }
  MP3player.setVolume(volume, volume);
}
