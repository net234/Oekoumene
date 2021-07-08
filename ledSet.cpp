

#include "ledSet.h"

void animLed_t::set( const uint16_t delay1, const uint16_t delay2, const uint16_t delay3, const e_rvb color, const uint8_t level) {
  uint8_t aLevel = level;
  if (aLevel>100) aLevel=100;
  this->color = color;
  this->level = aLevel;
  this->delay1 = delay1;
  this->delay2 = delay2;
  this->delay3 = delay3;
  this->pos1 = 0;
  this->pos2 = 0;
  this->pos3 = 0;
  this->enable = true;
 //D_println(this->enable);
}

void  animLed_t::step(uint8_t nstep) {
  if (this->enable) while (nstep--) step();
}

void  animLed_t::step() {
 //    D_println(this->pos1);
  if (this->pos1 < this->delay1) {
    this->pos1++;
    int cLevel = (int)this->level * this->pos1 / this->delay1;
    this->led.setcolor(this->color, cLevel);

    return;
  }
  if (this->pos2 < this->delay2) {
  //  D_println(this->pos2);
    this->pos2++;
    return;
  }
  if (this->pos3 < this->delay3) {
    this->pos3++;
    //    D_println(this->pos3);
    int cLevel = (int)this->level - ((int)this->level * this->pos3 / this->delay3);
    this->led.setcolor(this->color, cLevel);
    return;
  }
  this->enable = false;
}
