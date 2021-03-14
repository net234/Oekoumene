/************************************
    Ws2812  rgb serial led driver
*/

#pragma once
#include <Arduino.h>
#include "Nano.h"
#include "ledSet.h"

#define PIN_WS2812 D2



struct WS2812rvb_t : rvb_t {
  void  reset();
  virtual void  write() override;
  private:
  void shift(uint8_t color);
  //void  WS2812Write(const rvbw_t &color);
  //void  setcolor(rvbw_t &rbv_s, const e_rvb color, const int level);
};
