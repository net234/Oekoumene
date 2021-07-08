/************************************
    Ws2812  rgb serial led driver
*/

#pragma once
#include <Arduino.h>
#include "Nano.h"

//#define PIN_WS2812 D2

enum e_rvb { rvb_white, rvb_red, rvb_green, rvb_blue, rvb_yellow, rvb_pink, rvb_brun, rvb_orange, rvb_black, MAX_e_rvb };




struct  rvb_t {
  uint8_t Red;
  uint8_t Green;
  uint8_t Blue;
  void  setcolor(const e_rvb color, const uint8_t level);
};

const rvb_t map_color[MAX_e_rvb] = {
  {255, 255, 255}, // rvb_white
  {255,   0,   0}, // rvb_red
  {  0, 255,   0}, // rvb_green
  {  0,   0, 255}, // rvb_blue
  {150, 100,   0}, // rvb_yellow
  {200,  50,  50}, // rvb_pink
  {153,  71,   8}, // rvb_brun
  {200,  50,   0}, // rvb_orange
  {  0,   0,   0}   // rvb_black
};


struct WS2812rvb_t : rvb_t {
  void  reset();
  void  write();
  private:
  void shift(uint8_t color);
  //void  WS2812Write(const rvbw_t &color);
  //void  setcolor(rvbw_t &rbv_s, const e_rvb color, const int level);
};
