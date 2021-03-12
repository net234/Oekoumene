/*******************************
  Oekoumene V1.0  Animation lumioneuse avec WS2812

   (C) net234 Pierre HENRY 03/2021



*/

#include <Arduino.h>
#include "Nano.h"
#include "BetaEvents.h"
#include "WS2812.h"

// Gestionaire d'evenemnt
EventTrack MyEvent(LED_LIFE);   // le gestionaire d'event local a ce stretch



#define APP_VERSION   "Oekoumene V1.0"

//enum typeEvent { evNill=0, ev100Hz, ev10Hz, ev1Hz, ev24H, evDepassement1HZ,evInChar,evInString,evUser=99 };
enum myEvent  { evBP0Down = 50 ,    // (100) pousoir enfoncé
                evBP0Up,             // (101) pousoir relaché
              };

rvb_t led1;  //gauche
rvbw_t led2;  //centre
rvb_t led3;  //droit
rvb_t led4;  //haut
rvb_t led5;  //bas

struct animLed_s {
  bool enable = false;
  bool inited = false;
  int delay;
  e_rvb color;
  byte level;
};

animLed_s animLed1 ;
animLed_s animLed2 ;
animLed_s animLed3 ;
animLed_s animLed4 ;
animLed_s animLed5 ;

int clockStep = -1;

void setAnim( animLed_s& anim, const int delay, const e_rvb color, const byte level) {
  anim.color = color;
  anim.level = level;
  anim.delay = delay;
  anim.inited = false;
  anim.enable = true;

}

void setup() {
  // Initialisation Hard des IO
  pinMode(LED_LIFE, OUTPUT);

  // Serial
  Serial.begin(115200);
  Serial.println(F(APP_VERSION));

  // init event
  MyEvent.begin();

}

int N = 1;
bool BP0Status = HIGH;


void  animLed(animLed_s& aled, rvb_t& arvb) {
  if (!aled.inited) {
    setcolor(arvb, aled.color, aled.level);
    aled.inited = true;
  }
  if (aled.delay) {
    aled.delay--;
  } else {
    if (aled.level) {
      aled.level--;
      setcolor(arvb, aled.color, aled.level);
    } else {
      aled.enable = false;
    }
  }
}

void  animLed(animLed_s& aled, rvbw_t& arvb) {
  if (!aled.inited) {
    setcolor(arvb, aled.color, aled.level);
    aled.inited = true;
  }
  if (aled.delay) {
    aled.delay--;
  } else {
    if (aled.level) {
      aled.level--;
      setcolor(arvb, aled.color, aled.level);
    } else {
      aled.enable = false;
    }
  }
}


void loop() {
  MyEvent.GetEvent();       // get standart event
  MyEvent.HandleEvent();      // handle standart event

  switch (MyEvent.currentEvent.codeEvent)
  {

    case ev100Hz:
      // refresh led
      WS2812Write(led1);
      WS2812Write(led2);
      WS2812Write(led3);
      WS2812Write(led4);
      WS2812Write(led5);
      WS2812Reset();
      if (animLed1.enable) animLed(animLed1, led1);
      if (animLed2.enable) animLed(animLed2, led2);
      if (animLed3.enable) animLed(animLed3, led3);
      if (animLed4.enable) animLed(animLed4, led4);
      if (animLed5.enable) animLed(animLed5, led5);
      break;

    case ev10Hz: {



        uint8_t data1 = 0, data2 = 0, data3 = 0;
        if (paj7620ReadReg(0x6C, 1, &data1) == 0 ) {
          int aproche = data1;  //distance 0..255
          Lcd.setCursor(14, 1);
          Lcd.print("A:");
          LcdPrintf(aproche, 3);


          if (aproche > 0) {
            aproche = (aproche - 56) / 2;
            if (aproche < 1) aproche = 1;
            animLed2.enable = false;
            setcolor(led2, rvb_white, aproche);
            //                Lcd.setCursor(14, 2);
            //                Lcd.print("la:");
            //                LcdPrintf(aproche, 3);
          } else {
            if (!animLed2.enable) setAnim(animLed2, 80, rvb_blue, 20);
          }

        }

        // lecture des gestes
        //        if ( !paj7620ReadReg(0x43, 1, &data1) && !paj7620ReadReg(0x44, 1, &data2)) {
        //          int data = data1 | (data2 << 8);
        //          if ( data > 0) {
        //            clockStep = -1;
        //            MyEvent.removeDelayEvent(evClock);
        //            MyEvent.removeDelayEvent(evConterClock);
        //            Lcd.setCursor(0, 3);
        //            Lcd.print("G:");
        //            Lcd.print(data | 0x1000, BIN);
        //            //#define GES_RIGHT_FLAG        1
        //            //#define GES_LEFT_FLAG       2
        //            //#define GES_UP_FLAG         4
        //            //#define GES_DOWN_FLAG       8
        //            //#define GES_FORWARD_FLAG      16
        //            //#define GES_BACKWARD_FLAG     32
        //            //#define GES_CLOCKWISE_FLAG      64
        //            //#define GES_COUNT_CLOCKWISE_FLAG  128
        //            //#define GES_WAVE_FLAG       256
        //            if (data & GES_RIGHT_FLAG) {
        //              Serial.print("Gauche ");
        //              setAnim(animLed1, 100, rvb_green, 50);
        //            }
        //            if (data & GES_LEFT_FLAG) {
        //              Serial.print("Droite ");
        //              setAnim(animLed3, 100, rvb_green, 50);
        //            }
        //            if (data & GES_UP_FLAG) {
        //              Serial.print("Haut ");
        //              setAnim(animLed4, 100, rvb_green, 50);
        //            }
        //            if (data & GES_DOWN_FLAG) {
        //              Serial.print("Bas ");
        //              setAnim(animLed5, 100, rvb_green, 50);
        //            }
        //            if (data & GES_FORWARD_FLAG) {
        //              Serial.print("Avant ");
        //              setAnim(animLed1, 50, rvb_red, 50);
        //              setAnim(animLed3, 50, rvb_red, 50);
        //              setAnim(animLed4, 50, rvb_red, 50);
        //              setAnim(animLed5, 50, rvb_red, 50);
        //            }
        //            if (data & GES_BACKWARD_FLAG) {
        //              Serial.print("Arriere ");
        //              setAnim(animLed1, 50, rvb_yellow, 50);
        //              setAnim(animLed3, 50, rvb_yellow, 50);
        //              setAnim(animLed4, 50, rvb_yellow, 50);
        //              setAnim(animLed5, 50, rvb_yellow, 50);
        //            }
        //            if (data & GES_CLOCKWISE_FLAG) {
        //              Serial.print("Cercle Horaire ");
        //              MyEvent.pushEvent(evClock);
        //              MyEvent.pushEventMillisec(5000, evStopClock);
        //              clockStep = 0;
        //            }
        //            if (data & GES_COUNT_CLOCKWISE_FLAG) {
        //              Serial.print("Cercle Anti Horaire ");
        //              MyEvent.pushEvent(evConterClock);
        //              MyEvent.pushEventMillisec(5000, evStopClock);
        //              clockStep = 0;
        //            }
        //            if (data & GES_WAVE_FLAG) {
        //              Serial.print("Mouvement ");
        //              setAnim(animLed1, 10, rvb_blue, 50);
        //              setAnim(animLed3, 40, rvb_blue, 50);
        //              setAnim(animLed4, 80, rvb_blue, 50);
        //              setAnim(animLed5, 160, rvb_blue, 50);
        //            }
        //            Serial.println('.');
        //
        //          }
        //   }
      }
      break;


    case ev1Hz: {


      }
      break;

    case evClock:
      if (clockStep < 0) break;
      clockStep++;
      switch ( clockStep ) {
        case 1:
          setAnim(animLed5, 1, rvb_orange, 40);
          break;
        case 2:
          setAnim(animLed3, 1, rvb_orange, 40);
          break;
        case 3:
          setAnim(animLed4, 1, rvb_orange, 40);
          break;
        case 4:
          setAnim(animLed1, 1, rvb_orange, 40);
          clockStep = 0;
          break;
      }
      MyEvent.pushEventMillisec(300, evClock);
      break;
    case evConterClock:
      if (clockStep < 0) break;
      clockStep++;
      switch ( clockStep ) {
        case 1:
          setAnim(animLed5, 1, rvb_brun, 50);
          break;
        case 2:
          setAnim(animLed1, 1, rvb_brun, 50);
          break;
        case 3:
          setAnim(animLed4, 1, rvb_brun, 50);
          break;
        case 4:
          setAnim(animLed3, 1, rvb_brun, 50);
          clockStep = 0;
          break;
      }
      MyEvent.pushEventMillisec(300, evConterClock);
      break;
    case evStopClock:
      clockStep = -1;
      MyEvent.removeDelayEvent(evClock);
      MyEvent.removeDelayEvent(evConterClock);
      break;
    // eventuelles commande via le port serie
    case evInString:
      //      Serial.print(F("evInString '"));
      //      Serial.print(MyEvent.inputString);
      //      Serial.println("'");


      if (MyEvent.inputString.equals(F("RESET"))) {
        Serial.println("resetting");
        delay(500);
        reset();
        Serial.println("--?-?--");
      }

      if (MyEvent.inputString.equals(F("INIT"))) {

      }

  }
}
