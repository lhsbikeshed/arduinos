#pragma once
// http://stackoverflow.com/a/18159078/823542
enum State {
  STATE_INVALID = -1,
  STATE_DEAD,
  STATE_OFF,
  STATE_WARMUP,
  STATE_POWERING,
  STATE_PREON,
  STATE_BOOTUP,
  STATE_ON,
};
