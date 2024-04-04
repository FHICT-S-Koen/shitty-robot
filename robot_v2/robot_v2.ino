const int buttonPin = A2;
int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // Previous state of the button
unsigned long lastDebounceTime = 0;  // Time of the last button state change
unsigned long debounceDelay = 30;  // Debounce time in milliseconds

// Motors
#include <Servo.h>
#include <AFMotor.h>

Servo servo;

AF_DCMotor dc_motor_1(1);
AF_DCMotor dc_motor_2(2);
// DC motors PWM speed control
const int SPEED = 200;

// MP3/SD
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>

SdFat sd;
SFEMP3Shield MP3player;
// MP3 Player volume 0=max, 255=lowest (off)
const uint8_t volume = 0;

void setup() {
  Serial.begin(115200);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);

	servo.attach(10);

	dc_motor_1.setSpeed(SPEED);
  dc_motor_2.setSpeed(SPEED);

	// initSD();
  // initMP3Player();
}

void loop()
{
  dc_motor_1.run(RELEASE);
  dc_motor_2.run(RELEASE);

  bool started = false;

  Serial.println("START GAME?");
  while(true) {
    int reading = digitalRead(buttonPin);
    if (reading == 0) {
      break;
    }
  }
	Serial.println("STARTED");

	dc_motor_1.run(FORWARD);
	dc_motor_2.run(FORWARD);

	while (true)
	{
    int reading = digitalRead(buttonPin);
    if (reading == 0) {
      break;
    }
	  dc_motor_1.setSpeed(0);
	  dc_motor_2.setSpeed(0);
		servo.write(90);
		delay(500);
   int reading = digitalRead(buttonPin);
    if (reading == 0) {
      break;
    }
    dc_motor_1.setSpeed(SPEED);
	  dc_motor_2.setSpeed(SPEED);
		delay(4000);
   int reading = digitalRead(buttonPin);
    if (reading == 0) {
      break;
    }
	  dc_motor_1.setSpeed(0);
	  dc_motor_2.setSpeed(0);
		servo.write(-90);
		delay(500);
   int reading = digitalRead(buttonPin);
    if (reading == 0) {
      break;
    }
    dc_motor_1.setSpeed(SPEED);
	  dc_motor_2.setSpeed(SPEED);
		delay(4000);
	}
  dc_motor_1.run(RELEASE);
  dc_motor_2.run(RELEASE);
  delay(10000);
}

void initSD() {
  // Initialize the SD card.
  if(!sd.begin(SD_SEL, SPI_FULL_SPEED)) sd.initErrorHalt();
  // Depending upon your SD card environment, SPI_HAVE_SPEED may work better.
  if(!sd.chdir("/")) sd.errorHalt("sd.chdir");
}

void initMP3Player() {
  uint8_t result = MP3player.begin();
  if(result != 0) {
    Serial.print("Error code: ");
    Serial.print(result);
    Serial.println(" when trying to start MP3 player");
  }
  MP3player.setVolume(volume, volume);
}

void playTrack(uint8_t track)
{
  uint8_t result = MP3player.playTrack(track);

  if(result != 0) {
    Serial.print("Error code: ");
    Serial.print(result);
    Serial.println(" when trying to play track");
  } else {
    Serial.print("Playing track: ");
    Serial.println(track);
  }
}
