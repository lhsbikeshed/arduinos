#include "effects.h"
#include "leds.h"

unsigned long effectEnd;

unsigned long damageFlickerTimer;
bool damageFlickerState;
void setEffectDamage() {
  effectEnd = millis() + EFFECT_DAMAGE_LENGTH;
  damageFlickerTimer = 0;
  damageFlickerState = false;
}

void effectDamageThink() {
  auto now = millis();
  if (damageFlickerTimer < now) {
    damageFlickerState = !damageFlickerState;
    damageFlickerTimer = now + EFFECT_DAMAGE_FLICKER_LENGTH + random(EFFECT_DAMAGE_FLICKER_VARIATION);
  }
  if (damageFlickerState) {
    // Set the LEDs to 30% of normal brightness
    leftLEDs.nscale8(76);
    rightLEDs.nscale8(76);
    extraLEDs.nscale8(76);
  }
}


void setEffectHeartbeat() {
  effectEnd = millis() + EFFECT_HEARTBEAT_LENGTH;
}

void effectHeartbeatThink() {
  ledSet(CRGB::Black);
  extraLEDs.fill_solid(CRGB::Black);
}


void setEffect(LightingEffect newEffect) {
  effect = newEffect;
  if (effect == LightingEffect::Damage) {
    setEffectDamage();
  } else if (effect == LightingEffect::Heartbeat) {
    setEffectHeartbeat();
  }
}

void effectThink() {
  if (effectEnd < millis()) {
    effect = LightingEffect::None;
    return;
  }

  if (effect == LightingEffect::Damage) {
    effectDamageThink();
  } else if (effect == LightingEffect::Heartbeat) {
    effectHeartbeatThink();
  }
}
