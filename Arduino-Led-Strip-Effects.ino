#include "FastLED.h"
#define NUM_LEDS 30
#define DATA_PIN 5
#define DELAY_TIME 50

CRGB leds[NUM_LEDS];

CRGB setLed(CRGB led, int r, int g, int b){
  led.setRGB(g, r, b);
  return led;
}

void setup() {
  FastLED.addLeds<WS2812, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(160);
}

// HELPERS
void setAllOn(int r, int g, int b) {
  FastLED.clear();
  for(int i = 0; i < NUM_LEDS; i++)
    leds[i] = setLed(leds[i], r, g, b);
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
void flashing(int times, int delays, int r, int g, int b) {
  for(int i = 0; i < times; i++) {
    setAllOn(r, g, b);
    FastLED.delay(delays);
    setAllOff();
    FastLED.delay(delays);
  }
}

void snake(int len, int times, int r, int g, int b) {
  int start = 0;
  for(int i = 0; i <= times; i++) {
    FastLED.clear();
    for(int i = start; i < start + len; i++) {
      int num = getCircleIndex(i);
      leds[num] = setLed(leds[num], r, g, b);
    }
    FastLED.show();
    start++;
    if(start >= NUM_LEDS) start = 0;

    FastLED.delay(DELAY_TIME);
  }
}

void snake_reverse(int len, int times, int r, int g, int b) {
  int start = 0;
  for(int i = 0; i <= times; i++) {
    FastLED.clear();
    for(int i = start; i > start - len; i--) {
      int num = getCircleIndex(i);
      leds[num] = setLed(leds[num], r, g, b);
    }
    FastLED.show();
    start--;
    if(start <= -NUM_LEDS) start = 0;

    FastLED.delay(DELAY_TIME);
  }  
}


void loop() {
  snake(17, 30 * 5, 255, 0, 0);
  flashing(30, 100, 255, 0, 0);
  snake_reverse(10, 30 * 5, 255, 0, 0);
  flashing(30, 100, 255, 0, 0);
}
