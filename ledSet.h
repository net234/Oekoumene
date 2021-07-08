#pragma once
#include <Arduino.h>
#include "WS2812.h"

struct animLed_t {
  bool enable = false;
  uint16_t pos1;
  uint16_t pos2;
  uint16_t pos3;
  uint16_t delay1;
  uint16_t delay2;
  uint16_t delay3;
  e_rvb color;
  byte level;
  WS2812rvb_t led;
  void set( const uint16_t delay1, const uint16_t delay2, const uint16_t delay3, const e_rvb color, const uint8_t level);
  void step(const uint8_t nstep);
  void step();
};
