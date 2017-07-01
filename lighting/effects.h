#pragma once

enum LightingEffect {
  None,
  Damage,
  Heartbeat,
};

const unsigned int EFFECT_DAMAGE_LENGTH = 1500;
const unsigned int EFFECT_DAMAGE_FLICKER_LENGTH = 30;
const unsigned int EFFECT_DAMAGE_FLICKER_VARIATION = 150;
const unsigned int EFFECT_HEARTBEAT_LENGTH = 400;

LightingEffect effect;
