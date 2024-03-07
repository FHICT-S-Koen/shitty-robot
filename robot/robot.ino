#include <Stepper.h>

#include <SPI.h>

//Add the SdFat Libraries
#include <SdFat.h>
#include <SdFatUtil.h>

//and the MP3 Shield Library
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

const uint8_t volume = 0; // MP3 Player volume 0=max, 255=lowest (off)

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

const int STEPS = 200;
const int RPM = 60;
Stepper stepper(STEPS, 4, 5, 6, 7);

void setup()
{
  Serial.begin(115200);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

  stepper.setSpeed(RPM);

  initSD();
  initMP3Player();
}

void loop()
{
  bool started = false;

  // Start game
  if (!started) {
    // Zijn jullie ready?
    playTrack(1);

    while(!started) {
      int reading = analogRead(buttonPin);

      if (reading != lastButtonState) {
        lastDebounceTime = millis();  // Reset debounce timer
      }

      if ((millis() - lastDebounceTime) > debounceDelay) {

        if (reading != buttonState) {
          buttonState = reading;

          if (buttonState > 0) {
            started = true;
            break;
          }
        }
      }
      lastButtonState = reading;
      // return;
    }
  }
	Serial.println(F("STARTED"));

  // Het spel gaat starten!! 3,2,1 GO! 
  playTrack(2);

  for (int i = 0; i <= 10; i++) {
    shoot(3000);
    stepper.step(STEPS);
  }

  bool stop = true;
  
  // Tijdens het spel 
  while(stop) {
    int reading = analogRead(buttonPin);

    if (reading != lastButtonState) {
      lastDebounceTime = millis();  // Reset debounce timer
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {

      if (reading != buttonState) {
        buttonState = reading;

        if (buttonState > 0) {
          stop = false;
        }
      }
    }
    lastButtonState = reading;

    // Music
    // playTrack(9);
    delay(10000);
    // MP3player.stopTrack();
    // Go Go Go! 
    // Sneller! 
    // Kan je ze allemaal vinden?
    playTrack(random(3, 6));
    delay(1000);
  }

  delay(1000);
  // Eind spel 

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
  //PWM Speed Control
  analogWrite(E1, 255);
  analogWrite(E2, 255);
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
    if( result == 6 ) {
      Serial.println(F("Warning: patch file not found, skipping.")); // can be removed for space, if needed.
    }
  }
  MP3player.setVolume(volume, volume);
}
