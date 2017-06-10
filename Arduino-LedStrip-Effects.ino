#include "FastLED.h"
#define NUM_LEDS 30
#define DATA_PIN 5
#define DELAY_TIME 50

CRGB leds[NUM_LEDS];

CRGB setLed(CRGB led, int color[]){
  // error with ledstrip, r is g, g is r
  led.setRGB(
    color[1],
    color[0],
    color[2]
  );
  return led;
}

void setup() {
  FastLED.addLeds<WS2812, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(160);
}


// HELPERS
void setAllOn(int color[]) {
  FastLED.clear();
  for(int i = 0; i < NUM_LEDS; i++)
    leds[i] = setLed(leds[i], color);
  FastLED.show();
}

void setAllOff() {
  FastLED.clear();
  for(int i = 0; i < NUM_LEDS; i++)
    leds[i] = CRGB::Black;
  FastLED.show();
}

int getCircleIndex(int index) {
  if(index >=0) return index % NUM_LEDS;
  else return NUM_LEDS + (index % NUM_LEDS);
}


// EFFECTS
void flashing(int times, int delays, int color[]) {
  for(int i = 0; i < times; i++) {
    setAllOn(color);
    FastLED.delay(delays);
    setAllOff();
    FastLED.delay(delays);
  }
}

void snake_reverse(int len, int times, int color[]) {
  int start = 0;
  for(int i = 0; i <= times; i++) {
    FastLED.clear();
    for(int i = start; i > start - len; i--) {
      int num = getCircleIndex(i);
      leds[num] = setLed(leds[num], color);
    }
    FastLED.show();
    start--;
    if(start <= -NUM_LEDS) start = 0;

    FastLED.delay(DELAY_TIME);
  }  
}

void sectors(int times, int len, int space, int count, int color[]) {
  int start = 0;
  
  for(int i = 0; i < times; i++) {
    FastLED.clear();
    for(int j = 0; j < (space * count + len * count); j++) {
       int ledIndex = getCircleIndex(j + start);
       int sector = j % (len + space);
       
       if(sector < len) leds[ledIndex] = setLed(leds[ledIndex], color);
       else leds[ledIndex] = CRGB::Black;
    }
    FastLED.show();
    start++;
    if(start >= NUM_LEDS) start = 0;
    FastLED.delay(DELAY_TIME);
  }
}

void megaBoom(int times, int color1[], int color2[]) {
  
}

// MAIN LOOP
void loop() {
  int color[3] = {255, 0, 0};
  
//  flashing(30, 100, color);
//  snake_reverse(10, 30 * 5, color);                                  
//  flashing(30, 100, color);
  sectors(30, 14, 2, 2, color);
  sectors(30, 7, 3, 3, color);
  sectors(30, 5, 2, 4, color);
  sectors(30, 3, 3, 5, color);
  sectors(30, 2, 3, 6, color);
  sectors(30, 1, 3, 7, color);
  sectors(30, 1, 2, 10, color);
  sectors(30, 1, 1, 15, color);
}
