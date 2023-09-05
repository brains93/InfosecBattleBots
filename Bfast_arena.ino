#include <Stepper.h>

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

// Variables
bool Active = false;
bool Weapons_Enabled = false;
bool Flipper_Fire = false;
unsigned long StartMillis = 0;

void setup() {
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
    }
  }

  if (digitalRead(Button_Stop) == LOW) {
    Active = false; // Stop the timer
    Weapons_Enabled = false;
  }

  if (digitalRead(Button_Pit_Up) == LOW && Weapons_Enabled) {
    // Raise the pit
    Pit_Stepper.setSpeed(1);
    Pit_Stepper.step(-StepsRequired);
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
