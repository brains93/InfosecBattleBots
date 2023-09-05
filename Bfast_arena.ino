#include <Stepper.h>
#include <FastLED.h>

// Control pins
const int Button_Start = 53;
const int Button_Stop = 52;
const int Button_Pit_Up = 51;

// Outputs
const int Spinner_1_out = 22;
const int Spinner_2_out = 24;
const int Spinner_3_out = 26;
const int FLipper_Out = 28;

// Stepper motor
const int STEPS_PER_REV = 32;
const int GEAR_RED = 64;
const int StepsRequired = 2048;
Stepper Pit_Stepper(STEPS_PER_REV, 8, 10, 9, 11);

// LED Setup
#define NUM_LEDS 30       // Number of LEDs in your LED strip
#define DATA_PIN 6        // Define the data pin for your LED strip
CRGB leds[NUM_LEDS];  

// Variables
bool Active = false;
bool Weapons_Enabled = false;
bool Flipper_Fire = false;
unsigned long StartMillis = 0;

// FastLED variables
bool ledAnimationActive = false;
unsigned long animationStartTime = 0;


void setup() {

  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  pinMode(Button_Start, INPUT_PULLUP);
  pinMode(Button_Stop, INPUT_PULLUP);
  pinMode(Button_Pit_Up, INPUT_PULLUP);

  pinMode(Spinner_1_out, OUTPUT);
  pinMode(Spinner_2_out, OUTPUT);
  pinMode(Spinner_3_out, OUTPUT);
  pinMode(FLipper_Out, OUTPUT);
}

void loop() {
  if (digitalRead(Button_Start) == LOW && !Active) {
    Active = true;
    StartMillis = millis();
    Weapons_Enabled = false; // Reset weapons flag
    ledAnimationActive = true;
    animationStartTime = millis();
  }

  if (Active) {
    // Start the timer
    unsigned long elapsedTime = millis() - StartMillis;
    if (elapsedTime >= 130000) {
      // Lower the pit and set weapons flag to high
      Pit_Stepper.setSpeed(1);
      Pit_Stepper.step(StepsRequired);
      Weapons_Enabled = true;
    }

    if (elapsedTime >= 330000) {
      // Stop the timer
      Active = false;
      Weapons_Enabled = false;
      ledAnimationActive = false;
    }
  }

  if (digitalRead(Button_Stop) == LOW) {
    Active = false; // Stop the timer
    Weapons_Enabled = false;
    ledAnimationActive = false; // Turn off LED animation
  }

  if (digitalRead(Button_Pit_Up) == LOW && Weapons_Enabled) {
    // Raise the pit
    Pit_Stepper.setSpeed(1);
    Pit_Stepper.step(-StepsRequired);
  }
    // Update LEDs
  if (ledAnimationActive) {
    updateLEDs();
  } else {
    // Turn all LEDs red when the timer is not active
    fill_solid(leds, NUM_LEDS, CRGB::Red);
    FastLED.show();
  }


  // Your Flipper function goes here
  Flipper();
}

// Your Flipper function remains the same
void Flipper() {
  if (Flipper_Fire && Weapons_Enabled) {
    digitalWrite(FLipper_Out, HIGH);
    delay(50);
    digitalWrite(FLipper_Out, LOW);
  }
}

void updateLEDs() {
  unsigned long currentTime = millis();
  unsigned long animationDuration = currentTime - animationStartTime;

  if (animationDuration < 3000) {
    // Flash red once per second for 3 seconds
    if (animationDuration % 1000 < 500) {
      fill_solid(leds, NUM_LEDS, CRGB::Red);
    } else {
      fill_solid(leds, NUM_LEDS, CRGB::Black);
    }
  } else if (animationDuration < 5000) {
    // Display green for 2 seconds
    fill_solid(leds, NUM_LEDS, CRGB::Green);
  } else {
    // Display white while the timer is on
    fill_solid(leds, NUM_LEDS, CRGB::White);
  }

  FastLED.show();
}
