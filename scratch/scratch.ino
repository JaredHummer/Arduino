#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 50
#define LAST_OUTSIDE 23 // <24 in loops
#define BORDER_SPEED 20
#define BORDER_BRIGHTNESS 16

#define DATA_PIN 3

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
}

void loop() {
  int bright = 0;
  for (int cycle=0; cycle < BORDER_BRIGHTNESS; cycle++){
    leds[24] = CRGB(bright++,0,0);
    FastLED.show();
    delay(100);
  }
  for (int cycle=0; cycle < BORDER_BRIGHTNESS; cycle++){
    leds[24] = CRGB(bright--,0,0);
    FastLED.show();
    delay(100);
  }
  leds[0] = CRGB(0,0,0);
  FastLED.show();
}
