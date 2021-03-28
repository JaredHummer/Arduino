#include "FastLED.h"

#define NUM_LEDS 150
#define NUM_COLORS 5
#define DATA_PIN 3
CRGB leds[NUM_LEDS];
int colorList[][3] = {{16,0,0}, {0,16,0}, {16,16,0}, {0,16,16}, {0,0,16}};
int* color;
boolean needsManipulated[NUM_LEDS];



void setup() { 
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    
}

/*
  flash(speed, loops)
  glow(loops, speed (sin+x))
  runToLight(rate (delay), spacing, loops)
  runtoBlack(rate (delay), spacing, loops)
  sparkle(rate (mod), loops)
  shootingStar(delay)
  twinkle(time (~seconds), prominence (1-10))
  shiftColors(rate (delay), loops, boolean reverse)
  shootingStarSparkleTail(spd (delay)
*/


void loop() {
  mainLoop();
}

void mainLoop(){
  flash(200,2000);
  
  /*
  glow(1500,.15);
  runToLight(100, random(8,32), random(20, 100)); 
  randomContinuousSparkle(200, 200); 
  runToBlack(random(100,200), random(8,32), random(20,200));
  sparkle(random(10, 20), random(25, 150));
  shiftColors(random(200, 500), random(20, 100), false);
  runToLight(100, random(8,32), random(20,200));
  sparkle(random(5, 10),random(25,200));
  sparkle(random(10,20), random(25, 150));
  twinkle(random(25,50), random(4,6));
  */
}

void demo(){

}

void flash (int spd, int loops){
  int numberOfFlashes;
  
  for (int i=0; i<loops; i++){
    numberOfFlashes = random(1,10);
    if (i%spd==0) for (int j=0; j<numberOfFlashes; j++) leds[random(0, NUM_LEDS)] = CRGB(24,24,24);
    int color = random(0,3);
    for (int j=0; j<NUM_LEDS; j++){
       if (color<1) dimRGB(j,1,2,4);
       else if (color>=1 && color<2) dimRGB(j,2,4,1);
       else dimRGB(j,4,1,2);        
      }        
  
  FastLED.show();
  delay(100);
  }
  for (int i=0; i<16; i++) dimAll(1);
  




  
}



void glow(int loops, double spd){
  double x[NUM_LEDS]; //x translation on sin
  for (int i=0; i<NUM_LEDS; i++) x[i] = random(0,6.28);
  
  
  for (int i=0; i<loops; i++){
  
    //mainloop
    for (int j=0; j<NUM_LEDS; j++){
     leds[j]=CRGB(
       colorOf(j)[0] * (sin(x[j])+1) / 2,
       colorOf(j)[1] * (sin(x[j])+1) / 2,
       colorOf(j)[2] * (sin(x[j])+1) / 2);
     x[j]=x[j]+spd;
    }
     
      FastLED.show();
      delay(100);
    }
    
  
}


void randomContinuousSparkle(int loops, int spd){
  int lastLED = -1, flickerLED = 0;
  
  for (int j=0; j<loops; j++){
    light(flickerLED);
    flickerLED = random(0, NUM_LEDS);
    leds[flickerLED] = CRGB(24,24,24);
    
    dimAll(1);
    
    FastLED.show();
    delay(spd);
    
  }

}

void shootingStarSparkleTail(int spd){
  for (int i=0; i<NUM_LEDS; i++) needsManipulated[i] = false;
  
  for (int i=0; i<NUM_LEDS; i++) {
    leds[i] = CRGB::White;
    whitenRandom(i-20, i-4); 
    FastLED.show();
    dimAll(32);   
    delay(spd);
  }
} void whitenRandom(int first, int last){
  if (first>=0) light(random(first, last)); //leds[random(first,last)] = CRGB(128,128,128);
}


void shiftColors(int spd, int loops, boolean reverse){
  //loops -= loops%(NUM_COLORS+1);
  for (int i=0; i<loops; i++){
    if (reverse){
      for (int j=0; j<NUM_COLORS; j++){
        for (int k=0; k<NUM_LEDS; k++) {
          light(k, j);
        }
        FastLED.show();
        delay(spd);
      }
    } else {
        for (int j=NUM_COLORS-1; j>=0; j--){
        for (int k=0; k<NUM_LEDS; k++) {
          light(k, j);
        }
        FastLED.show();
        delay(spd);
        }
    }
  }
}

void twinkleSparkle(int time, int prominence){
  int limit = time*1000;
  normalizeAll(6);
  for (int i=0; i<time*1000; i++){
    for (int j=0; j<random(NUM_LEDS/2); j++)
      dim(random(0,NUM_LEDS-1), random(0, 3*log(prominence+1)));
    for (int j=0; j<random(NUM_LEDS/2); j++) light(random(NUM_LEDS));
    if (i%((300-(29*(prominence))))==0) whiten(random(0, NUM_LEDS-1));
    FastLED.show();
    
  }
}

void twinkle(int time, int prominence){
  int limit = time*1000;
  for (int i=0; i<time*1000; i++){
    for (int j=0; j<random(NUM_LEDS/2); j++)
      dim(random(0, NUM_LEDS-1), random(0, prominence));
    for (int j=0; j<random(NUM_LEDS/2); j++) light(random(NUM_LEDS));
    FastLED.show(); 
  }
}


void runToBlack(int rate, int spacing, int loops){
    //setup
  for (int i=0; i<NUM_LEDS; i++) {
      dimAllBefore(96/spacing, i);
      for (int j=i; j>i-NUM_LEDS; j=j-spacing) light(j);
      FastLED.show();
      delay(rate);
  }
  
  //loop
  for (int h=0; h<loops; h++){
    for (int i=NUM_LEDS-spacing; i<NUM_LEDS; i++){
      dimAll(96/spacing);
      for (int j=i; j>0; j=j-spacing) light(j);
      FastLED.show();
      delay(rate);
    }
  }
  //end run
  for (int i=spacing-1; i<NUM_LEDS; i++) {
      dimAll(96/spacing);
      for (int j=i; j<NUM_LEDS; j=j+spacing) light(j);
      FastLED.show();
      delay(rate);
  }
  for (int i=0; i<spacing; i++) {
    dimAll(96/spacing);
    FastLED.show();
  }
  
}

void runToLight(int rate, int spacing, int loops){
  //setup
  for (int i=0; i<NUM_LEDS; i++) {
      dimAllBefore(96/spacing, i);
      for (int j=i; j>i-NUM_LEDS; j=j-spacing) light(j);
      FastLED.show();
      delay(rate);
  }
  
  //loop
  for (int h=0; h<loops; h++){
    for (int i=NUM_LEDS-spacing; i<NUM_LEDS; i++){
      dimAll(96/spacing);
      for (int j=i; j>0; j=j-spacing) light(j);
      FastLED.show();
      delay(rate);
    }
  }
  
  //end fill
  for (int i=0; i<NUM_LEDS; i++) {
      dimAllAfter(96/spacing, i);
      for (int j=i; j<NUM_LEDS; j=j+spacing) light(j);
      FastLED.show();
      delay(rate);
  }

}


void shootingStar(int spd){
  for (int i=0; i<NUM_LEDS; i++){
    whiten(i);
    for (int j=i; j>=0; j--) fadeTo(4, j);
    FastLED.show();
    delay(spd);
  }
  for (int i=0; i<16; i++){
    for (int j=0; j<NUM_LEDS; j++) fadeTo(4, j);
    FastLED.show();
  }
}

void shootingStarToBlack(int spd){
  for (int i=0; i<NUM_LEDS; i++){
    whiten(i);
    dimAllBefore(16, i);
    FastLED.show();
    delay(spd);
  }
  for (int i=0; i<16; i++) {
    dimAll(16);
    FastLED.show();
    delay(spd);
  }
}

void sparkle(int rate, int loops){ 
  for (int h=0; h<loops; h++){ 
    for (int i=0; i<NUM_LEDS; i++) needsManipulated[i] = false;
    
    int* list = shuffled();
    int i=0, j=0;
    while (i<NUM_LEDS && loops>0){
      if (++j%rate==0){
        whiten(list[i]);
        i++;
        loops--;
      }
      for (int j=0; j<i; j++)
        fadeTo(4, list[j]);
      FastLED.show();
      delay(25);
    }
    
    for (int i=0; i<16; i++){
      for (int j=0; j<NUM_LEDS; j++) fadeTo(6, j);
      FastLED.show();
      delay(25);
    }
  }
} int* shuffled() {
  static int ret[NUM_LEDS];
  for (int i=0; i<NUM_LEDS; i++) ret[i] = i;
  for (int i=0; i<NUM_LEDS; i++){
    int rand = (int) random(0, NUM_LEDS-1);
    int temp = ret[i];
    ret[i] = ret[rand];
    ret[rand] = temp;
  } 
  return ret;
}



///////////////////////////////////////////////////
void whiten(int index){
  leds[index] = CRGB::White;
  needsManipulated[index] == true;
}

void fadeTo(int amount, int index){
   if (!needsManipulated[index]){
     int* target = colorOf(index);
     int difference[] = {leds[index][0] - target[0], leds[index][1] - target[1], leds[index][2] - target[2]}; 
     for (int i=0; i<3; i++) leds[index][i] -= difference[i]/amount;
     if (difference[0]==0 && difference[1]==0 && difference[2]==0)
      needsManipulated[index]=false; 
   }
}

int* colorOf(int index) {
  return colorList[index%5];
}

void dimAll(int amount){
  for (int i=0; i<NUM_LEDS; i++) leds[i]-= CRGB(amount, amount, amount);
}

void dimAllBefore(int amount, int index){
  for (int i=0; i<index; i++) leds[i]-= CRGB(amount, amount, amount);
}

void dimAllAfter(int amount, int index){
  for (int i=index; i<NUM_LEDS; i++) leds[i] -= CRGB(amount, amount, amount); 
}


void dimRGB(int index, int mask1, int mask2, int mask3){
  leds[index] -= CRGB(mask1,mask2,mask3);
}

void lightAll(){
   for (int i=0; i<NUM_LEDS; i++) light(i);
}

void light(int index, int offset){
  if (index>=0){
    int* color = colorList[(index+offset)%NUM_COLORS];
    leds[index] = CRGB(color[0], color[1], color[2]);
  } 
}
void light(int index){
  if (index>=0){
    int* color = colorList[index%NUM_COLORS];
    leds[index] = CRGB(color[0], color[1], color[2]);
  }
}

void dim(int index, int amount){
 leds[index] -= CRGB(amount, amount, amount); 
 needsManipulated[index] = true;
}

void normalizeAll(int amount){
  for (int i=0; i<NUM_LEDS; i++) fadeTo(amount, i);
}
