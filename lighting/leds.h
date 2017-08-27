#pragma once

#define LEDS_PER_SIDE 99
// Pray, seatbelt
#define EXTRA_LEDS 2

// Locations in extra set
#define SEATBELT   0
#define PRAY       1

const unsigned int AIRLOCK_FLASH_TIME = 500;

CRGBArray<LEDS_PER_SIDE> rightLEDs;
CRGB leftLEDs_[LEDS_PER_SIDE + EXTRA_LEDS];
CPixelView<CRGB> leftLEDs(leftLEDs_, LEDS_PER_SIDE);
CPixelView<CRGB> extraLEDs(&leftLEDs_[LEDS_PER_SIDE], EXTRA_LEDS);

#define MAX_BRIGHT 30
CRGB RedAlertColour(MAX_BRIGHT, 0, 0);
CRGB WarpColour(0, 0, MAX_BRIGHT);
CRGB IdleColour(0, 0, MAX_BRIGHT);
CRGB BriefingColour = CRGB::White;
