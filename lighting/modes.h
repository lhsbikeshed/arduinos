#pragma once
#include "leds.h"

const unsigned int RED_ALERT_FLASH_TIME = 800;

enum LightingMode {
  Idle,
  RedAlert,
  Warp,
  Briefing,
};

LightingMode mode;
