#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 50
#define BORDER 24 // <24 in loops
#define BORDER_SPEED 20
#define BORDER_BRIGHTNESS 128
#define STAR_BRIGHTNESS 16

#define DATA_PIN 3
// Define the array of leds
CRGB leds[NUM_LEDS];
int hue;

void setup() { 
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
    for (int x= BORDER; x<NUM_LEDS; x++){
      leds[x] = CRGB(STAR_BRIGHTNESS,STAR_BRIGHTNESS,STAR_BRIGHTNESS);
    }
    hue = 0;
}

// >1
void dim_stars(float ratio){
  for (int x =BORDER+1; x<NUM_LEDS; x++){
      leds[x][0] /= ratio;
      leds[x][1] /= ratio;
      leds[x][2] /= ratio;
  }
}

void loop() {
    int change = 0;
    dim_stars(1.02);
    for (int i = 0; i<BORDER; i++){
      leds[i] = CHSV(hue, 255, BORDER_BRIGHTNESS);
    }

  /*
    for (int i = BORDER+1; i<NUM_LEDS; i++){
      change = random(0, 16) - 16;  
      leds[i][0] += change;  
      leds[i][1] += change;  
      leds[i][2] += change;
    }
  */
    //twinkle
    
      int index = random(BORDER+1, NUM_LEDS-1);
      int color = random (172, 255);
      leds[index][0] = color;
      leds[index][1] = color;
      leds[index][2] = color;
   FastLED.show();
   delay(20);
   hue += 1;
  }
