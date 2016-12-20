#include <FastLED.h>
#include <ClickEncoder.h>
#include <TimerOne.h>

#include "states.h"
#include "leds.h"
#include "encoders.h"
#include "switches.h"


// --------------- game logic bits ----------

// reactor puzzle game state
State gameState = STATE_INVALID;

// serial handling
char buffer[10]; // serial buffer
byte bufPtr = 0;

int damageTimer = 0;

void setup() {
  setupLEDs();
  setupAirlock();
  setupSwitches();
  setupEncoders();

  // serial shit
  Serial.begin(9600);
  reset();
}

void setState(State state) {
  if (gameState == state) {
    return;
  }
  gameState = state;

  switch (gameState) {
    case STATE_DEAD:
      return setStateDead();
    case STATE_OFF:
      return setStateOff();
    case STATE_WARMUP:
      return setStateWarmup();
    case STATE_POWERING:
      return setStatePowering();
    case STATE_PREON:
      return setStatePreOn();
    case STATE_BOOTUP:
      return setStateBootup();
    case STATE_ON:
      return setStateOn();
  }
}

void reset() {
  resetLEDs();
  resetSwitches();

  *ledReactor = BrightRed;

  setState(STATE_OFF);
}

void processBuffer() {
  switch (buffer[0]) {
    case 'r': // reset the game states
      reset();
      break;
    case 'R': // Reactor is now on, end startup sequence
      setState(STATE_ON);
      break;
    case 'k': // ship was killed, turn off all the bling
      setState(STATE_DEAD);
      break;
    case 'D': // set dial value, format is D<dial num + 65><value + 65>
      // +65 is so that its readable in serial monitor A=0, B=1 etc
      break;
    case 'd': // Damage
      damageTimer = 60;
      break;
    case 'p': // Power off
      setState(STATE_OFF);
      break;
    case 'P': // Power on
      setState(STATE_ON);
      break;
  }
}

void readSerial() {
  // -------------------- serial reads --------------
  while ( Serial.available() > 0) {  // If data is available,
    char c = Serial.read();
    if (c == ',') {
      processBuffer();
      bufPtr = 0;
    }
    else {
      buffer[bufPtr] = c;
      if (bufPtr + 1 < 5) {
        bufPtr++;
      }
      else {
        bufPtr = 0;
      }
    }
  }
}

void loop() {
  readEncoders();
  updatePowerRings();

  readSerial();

  if (gameState != STATE_DEAD) {
    readSwitches();
    readAnalog();
    readAirlock();

    if (damageTimer > 0) {
      damageTimer --;
    }
  }

  LEDBlinkThink();

  switch (gameState) {
    case STATE_DEAD:
      stateDead();
      break;
    case STATE_OFF:
      stateOff();
      break;
    case STATE_WARMUP:
      stateWarmup();
      break;
    case STATE_POWERING:
      statePowering();
      break;
    case STATE_PREON:
      statePreOn();
      break;
    case STATE_BOOTUP:
      return stateBootup();
    case STATE_ON:
      stateOn();
      break;
  }

  // flicker everything if the damage timer is > 0
  if (damageTimer > 0) {
    for (int i = 0; i < NUMPIXELS; i++) {
      if (random(255) > 128) {
        leds[i] = CRGB::Black;
      }
    }
  }

  // leds
  showLEDs();
}
