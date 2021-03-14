#pragma once
#include <Arduino.h>
//#include "WS2812.h"
#define D_println(x) Serial.print(F(#x " => '")); Serial.print(x); Serial.println("'");

// liste des couleurs virtuelles
enum e_rvb { rvb_white, rvb_red, rvb_green, rvb_blue, rvb_yellow, rvb_pink, rvb_brun, rvb_orange, rvb_black, MAX_e_rvb };

// couleur virtuelle
struct  rvb_t {
  uint8_t Red;
  uint8_t Green;
  uint8_t Blue;
  void  setcolor(const e_rvb color, const uint8_t level);
  rvb_t() : Red(0), Green(0), Blue(0) {};
  rvb_t(const uint8_t red, const uint8_t green, const uint8_t blue) : Red(red),Green(green),Blue(blue) {};
  rvb_t(const rvb_t& rvb) : Red(rvb.Red),Green(rvb.Green),Blue(rvb.Blue) {};
  virtual void  write() {};
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



struct animLed_t : rvb_t {
  bool enable = false;
  uint16_t pos1;
  uint16_t pos2;
  uint16_t pos3;
  uint16_t delay1;
  uint16_t delay2;
  uint16_t delay3;
  e_rvb color;
  byte level;
  //rvb_t led;
  animLed_t(const rvb_t led) : rvb_t(led) {};
  void set( const uint16_t delay1, const uint16_t delay2, const uint16_t delay3, const e_rvb color, const uint8_t level);
  void step(const uint8_t nstep);
  void step();
};
