#include <FastLED.h>

CRGBArray<256> leds;

void setup() {
  FastLED.addLeds<NEOPIXEL, 14>(leds.leds, leds.len);
  leds.fill_solid(CRGB::White);
}

void loop() {
  FastLED.show(10);
}
