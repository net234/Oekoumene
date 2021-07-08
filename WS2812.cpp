/************************************
    Ws2812  rgb serial led driver

    A reset is issued as early as at 9 µs???, contrary to the 50 µs mentioned in the data sheet. Longer delays between transmissions should be avoided.
    On tested componant 50µs reset is a mandatory
    The cycle time of a bit should be at least 1.25 µs, the value given in the data sheet, and at most ~50 µs, the shortest time for a reset.
    A “0” can be encoded with a pulse as short as 62.5 ns, but should not be longer than ~500 ns (maximum on WS2812).
    A “1” can be encoded with pulses almost as long as the total cycle time, but it should not be shorter than ~625 ns (minimum on WS2812B).
    from https://cpldcpu.wordpress.com/2014/01/14/light_ws2812-library-v2-0-part-i-understanding-the-ws2812/

    https://roboticsbackend.com/arduino-fast-digitalwrite/



*/


#include "WS2812.h"
// 10 µsec pulse

#define MSK_WS2812 (1 << PIN_WS2812)

inline  void WS2812_LOW() __attribute__((always_inline));
inline  void WS2812_HIGH() __attribute__((always_inline));

void WS2812_LOW() {
  PORTD &= !MSK_WS2812;
}

void WS2812_HIGH() {
  PORTD |= MSK_WS2812;
}


void  WS2812rvb_t::reset() {
  interrupts();
  pinMode(PIN_WS2812, OUTPUT);
  WS2812_LOW();
  delayMicroseconds(10);
}

//   Arduino Nano
//   Cycle = 1,7µs
//    0 = 0,3µs + 1,4µs
//    1 = 0,95µs + 0,75µs




void WS2812rvb_t::shift( uint8_t shift) {
  static uint8_t delay1 = 0;
  static uint16_t delay2 = 0;

  for (byte n = 8; n > 0; n--, shift = shift << 1) {
    if (shift & 0x80)  {
      WS2812_HIGH();  //0,3µs
      delay2++;       //0,65µs
      WS2812_LOW();
    } else {
      WS2812_HIGH();  //0,3µs
      WS2812_LOW();
      delay2++;
    }
    //delay1++;
  }

}

void  WS2812rvb_t::write() {
  noInterrupts();
  this->shift(this->Green);
  this->shift(this->Red);
  this->shift(this->Blue);
}


void  rvb_t::setcolor( const e_rvb color, const uint8_t level)  {
  this->Red =   (uint16_t)map_color[color].Red * level / 100;
  this->Green = (uint16_t)map_color[color].Green * level / 100;
  this->Blue =  (uint16_t)map_color[color].Blue * level / 100;
}
