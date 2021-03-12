

#include "ledSet.h"

void animLed_t::set( const uint16_t delay1, const uint16_t delay2, const uint16_t delay3, const e_rvb color, const uint8_t level) {
  this->color = color;
  this->level = level;
  this->delay1 = delay1;
  this->delay2 = delay2;
  this->delay3 = delay3;
  this->mode = mdUp;
  this->enable = true;

}

void  animLed_t::step(uint8_t nstep) {
//  if (this->mode == mdInit) {
//    this->led.setcolor(this->color, this->level);
//    this->mode++;
//  }
  if (this->enable) while (nstep--) animLed_t();
}

void  animLed_t::step() {
    switch (this->mode) {
      case mdup:
        if (this->delay1) {
          this->delay1--;
          continue;
        }
        this->led.setcolor(this->color, this->level);
        this->mode++;
        break;


    }
    if (this->level) {
      this->level--;
      this->led.setcolor( this->color, this->level);
      continue;
    }
    this->mode = mdInit;
    break;
  }
}
