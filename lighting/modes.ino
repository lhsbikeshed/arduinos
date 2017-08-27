#include "modes.h"

void setModeIdle() {}

void modeIdleThink() {
  ledSet(IdleColour);
}

void setModeBriefing() {}

void modeBriefingThink() {
  ledSet(BriefingColour);
}

unsigned long redAlertTimer;
bool redAlertState;
void setModeRedAlert() {
  redAlertTimer = 0;
  redAlertState = false;
}

void modeRedAlertThink() {
  auto now = millis();
  if (redAlertTimer < now) {
    redAlertState = !redAlertState;
    redAlertTimer = now + RED_ALERT_FLASH_TIME;
    if (redAlertState) {
      ledSet(RedAlertColour);
    } else {
      ledSet(CRGB::Black);
    }
  }
}

void setModeWarp() {}

void modeWarpThink() {
  // //apply sin wave over the top of the base colour
  // if (lastWarpUpdate + 25 < millis()) {
  //   sinCount++;
  //   sinCount %= 628;
  //   lastWarpUpdate = millis();
  // }
  auto now = millis();
  auto sinCount = (now / 25) % 682;

  for (auto i = 0; i < LEDS_PER_SIDE; i++) {
    float sinMod = sin(sinCount / 3 + i);
    if (sinMod < 0) {
      sinMod = 0;
    }
    // Copy the warp colour
    CRGB colour = WarpColour;
    colour.nscale8(floor(255.0 * sinMod));
    ledSet(i, colour);
  }
}


///////////////

void setMode(LightingMode newMode) {
  mode = newMode;
  if (mode == LightingMode::Idle) {
    setModeIdle();
  } else if (mode == LightingMode::RedAlert) {
    setModeRedAlert();
  } else if (mode == LightingMode::Warp) {
    setModeWarp();
  } else if (mode == LightingMode::Briefing) {
    setModeBriefing();
  }
}

void modeThink() {
  if (mode == LightingMode::Idle) {
    modeIdleThink();
  } else if (mode == LightingMode::RedAlert) {
    modeRedAlertThink();
  } else if (mode == LightingMode::Warp) {
    modeWarpThink();
  } else if (mode == LightingMode::Briefing) {
    modeBriefingThink();
  }
}
