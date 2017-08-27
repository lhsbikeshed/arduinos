#include "leds.h"

#define PIN_LEFT_LEDS 9
#define PIN_RIGHT_LEDS 8
#define PIN_AIRLOCK_LED 2

void setupLEDs() {
  pinMode(PIN_AIRLOCK_LED, OUTPUT);
  // TODO: These are probably OK to just be plain NEOPIXELs
  // The lefthand side is complicated by being all big.
  FastLED.addLeds<WS2811, PIN_LEFT_LEDS, GRB>(leftLEDs_, LEDS_PER_SIDE + EXTRA_LEDS);
  FastLED.addLeds<WS2811, PIN_RIGHT_LEDS, GRB>(rightLEDs.leds, rightLEDs.size());
}

bool seatbeltEnabled = false;
void setSeatbelt(bool state) {
  seatbeltEnabled = state;
}

bool prayEnabled = false;
void setPray(bool state) {
  prayEnabled = state;
}

void extraThink() {
  extraLEDs[SEATBELT] = seatbeltEnabled ? CRGB::White : CRGB::Black;
  extraLEDs[PRAY] = prayEnabled ? CRGB::White : CRGB::Black;
}

bool airLockFlashing = false;
unsigned long airLockFlashTimer;
bool airLockFlashState;
void setAirlock(bool state) {
  airLockFlashing = state;
  airLockFlashState = false;
  airLockFlashTimer = 0;
}

void airlockThink() {
  if (!airLockFlashing) return;
  auto now = millis();
  if (airLockFlashTimer < now) {
    airLockFlashState = !airLockFlashState;
    airLockFlashTimer = now + AIRLOCK_FLASH_TIME;
  }
  digitalWrite(PIN_AIRLOCK_LED, airLockFlashState);
}

void ledReset() {
  setAirlock(false);
  ledSet(CRGB::Black);
  extraLEDs.fill_solid(CRGB::Black);
}

void ledSet(CRGB colour) {
  leftLEDs.fill_solid(colour);
  rightLEDs.fill_solid(colour);
}

void ledSet(uint8_t num, CRGB colour) {
  leftLEDs[num] = colour;
  rightLEDs[num] = colour;
}
