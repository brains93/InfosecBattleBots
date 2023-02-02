#include <FastLED.h>

#define LED_PIN     7 //data pin to LEDs
#define NUM_LEDS    10 //Number of LED in the strip
#define  BUTTONPIN  2  // the number of the pushbutton pin

CRGB leds[NUM_LEDS];

void setup() {

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(buttonPin, INPUT);
  
}

//Function to flash or pulse the LED, the first input is the colour you want Red, Blue, Green, White, Black(off)
//count is how many times to loop (roughly used to control time could be improved with a time librey when my brain is working)
//Speed of the flash in milliseconds. play with this to get the puls/flash you want
void flash(colour, count, speed){

     for (int i = 0; i <= count; i++)  {  
        for (int i = 0; i <= NUM_LEDS; i++) {
            leds[i] = CRGB::colour);
            FastLED.show();
            
        }
        delay(speed)
        for (int i = 0; i <= NUM_LEDS; i++) {
            leds[i] = CRGB::Black;
            FastLED.show();
            
        }
        delay(speed)
     }
}

//carrys out the sequince,  using the flashing function above and setting the colour for the solid colour blocks

void lightshow(){
    flash(Red, 4, 50);
    flash(Green, 1, 50);


    //sets to white for 30 seconds
    for (int i = 0; i <= count; i++)  {  
            for (int i = 0; i <= NUM_LEDS; i++) {
                leds[i] = CRGB::White);
                FastLED.show();
                
            }
    delay(30000);

    flash(Red, 3, 30);

    //sets to white for 140 seconds
    for (int i = 0; i <= count; i++)  {  
            for (int i = 0; i <= NUM_LEDS; i++) {
                leds[i] = CRGB::White);
                FastLED.show();
                
            }
    delay(140000);


    flash(Red, 4, 50);

    //finally sets to Red, this will stay red, if you want the LED to turn off copy this and change the colour to Black 
    for (int i = 0; i <= count; i++)  {  
            for (int i = 0; i <= NUM_LEDS; i++) {
                leds[i] = CRGB::Red);
                FastLED.show();
                
            }
    delay(15000);
    }

void loop() {

    if (buttonState == HIGH) {
        lightshow()
    }
  
}
