#include "FastLED.h"

#define LED_PIN 2
#define BUTTON_PIN 3
#define NUM_LEDS 30
#define BRIGHTNESS 255
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(buttonPin, INPUT);

}

void lightshow() {
  // Pulse Red
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j <= NUM_LEDS; j++) {
      leds[j] = CRGB::Red;
    }
    FastLED.show();
    delay(500);
    for(int j = 0; j <= NUM_LEDS; j++) {
      leds[j] = CRGB::Black;
    }
    FastLED.show();
    delay(500);
    delay(1000);
  }

  // Pulse Green
  for(int j = 0; j <= NUM_LEDS; j++) {
    leds[j] = CRGB::Green;
  }
  FastLED.show();
  delay(1500);
  for(int j = 0; j <= NUM_LEDS; j++) {
    leds[j] = CRGB::Black;
  }
  FastLED.show();

  // Solid White
  for(int j = 0; j <= NUM_LEDS; j++) {
    leds[j] = CRGB::White;
  }
  FastLED.show();
  delay(30000);

  // Flash Red
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j <= NUM_LEDS; j++) {
      leds[j] = CRGB::Red;
    }
    FastLED.show();
    delay(100);
    for(int j = 0; j <= NUM_LEDS; j++) {
      leds[j] = CRGB::Black;
    }
    FastLED.show();
    delay(100);
  }

  // Solid White
  for(int j = 0; j <= NUM_LEDS; j++) {
    leds[j] = CRGB::White;
  }
  FastLED.show();
  delay(140000);

  for(int i = 0; i < 4; i++) {
    for(int j = 0; j <= NUM_LEDS; j++) {
      leds[j] = CRGB::Red;
    }
    FastLED.show();
    delay(500);
    for(int j = 0; j <= NUM_LEDS; j++) {
      leds[j] = CRGB::Black;
    }
    FastLED.show();
    delay(500);
    delay(1000);
  }

  // Solid RED
  for(int j = 0; j <= NUM_LEDS; j++) {
    leds[j] = CRGB::Red;
  }
  FastLED.show();
  delay(15000);
   for(int j = 0; j <= NUM_LEDS; j++) {
      leds[j] = CRGB::Black;
    }
    FastLED.show();
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH) {
    lightshow()
  }
}
