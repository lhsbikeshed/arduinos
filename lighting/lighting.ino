#include <FastLED.h>
#include "leds.h"
#include "modes.h"
#include "effects.h"

bool lightsOn;

void setup() {
  Serial.begin(9600);
  setupLEDs();
  ledReset();
  setMode(LightingMode::Idle);
  setEffect(LightingEffect::None);
  FastLED.show();
}

void lightThink() {
  // Mr Blinkums
  airlockThink();
  // Main LED gruntwork
  modeThink();
  // Secondary LED work
  extraThink();
  // Damage flicker etc on top of prev work
  effectThink();
  FastLED.show();
}

void loop() {
  handleSerialCommands();

  if (lightsOn) {
    lightThink();
  }
}

void handleSerialCommands() {
  if (Serial.available() == 0) {
    return;
  }
  char c = Serial.read();
  switch (c) {
  case 'k':
    ledReset();
    lightsOn = false;
    break;
  case 'o':
    lightsOn = true;
    break;
  case 'r':
    setMode(LightingMode::RedAlert);
    break;
  case 'w':
    setMode(LightingMode::Warp);
    break;
  case 'd':
    setEffect(LightingEffect::Damage);
    break;
  case 'h':
    setEffect(LightingEffect::Heartbeat);
    break;
  case 'b':
    setMode(LightingMode::Briefing);
    break;
  case 'R':
    ledReset();
    setMode(LightingMode::Idle);
    setEffect(LightingEffect::None);
    lightsOn = false;
    break;
  case 'i':
    setMode(LightingMode::Idle);
    break;
  case 'S':
    setSeatbelt(true);
    break;
  case 's':
    setSeatbelt(false);
    break;
  case 'P':
    setPray(true);
    break;
  case 'p':
    setPray(false);
    break;
  case 'A':  //airlock light
    setAirlock(true);
    break;
  case 'a':
    setAirlock(false);
    break;
  case '\n':
  case '\r':
    return;
  default:
    Serial.write("Unknown,");
    return;
  }
  Serial.write("OK,");
}
