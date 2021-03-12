/*******************************
  Oekoumene V1.0  Animation lumioneuse avec WS2812

   (C) net234 Pierre HENRY 03/2021



*/

#include <Arduino.h>
#include "Nano.h"
#include <betaEvents.h>
#include "WS2812.h"
#include  "ledSet.h"

// Gestionaire d'evenemnt
EventTracker MyEvent(LED_LIFE);   // le gestionaire d'event local a ce stretch



#define APP_VERSION   "Oekoumene V1.0"

//enum typeEvent { evNill=0, ev100Hz, ev10Hz, ev1Hz, ev24H, evDepassement1HZ,evInChar,evInString,evUser=99 };
enum myEvent  {   evBP0Down = 100,    // BP0 est appuyé
                  evBP0Up,            // BP0 est relaché
                  evBP0LongDown,      // BP0 est maintenus appuyé plus de 3 secondes
                  evBP0LongUp,        // BP0 est relaché plus de 3 secondes
              };




animLed_t animLed1 ;
animLed_t animLed2 ;
animLed_t animLed3 ;
animLed_t animLed4 ;
animLed_t animLed5 ;

int clockStep = -1;

#include <avr/wdt.h>

void reset()
{
  wdt_enable(WDTO_15MS);

  while (1)
  {

  }
};





uint8_t BP0Multi = 0;

void setup() {
  // Initialisation Hard des IO
  pinMode(LED_LIFE, OUTPUT);
  pinMode(BP0, INPUT_PULLUP);

  // Serial
  Serial.begin(115200);
  Serial.println(F(APP_VERSION));

  // init event
  MyEvent.begin();

}

int N = 1;
bool BP0Down = HIGH;



//void  animLed(animLed_s& aled, rvbw_t& arvb) {
//  if (!aled.inited) {
//    setcolor(arvb, aled.color, aled.level);
//    aled.inited = true;
//  }
//  if (aled.delay) {
//    aled.delay--;
//  } else {
//    if (aled.level) {
//      aled.level--;
//      setcolor(arvb, aled.color, aled.level);
//    } else {
//      aled.enable = false;
//    }
//  }
//}


void loop() {
  MyEvent.getEvent();       // get standart event
  MyEvent.handleEvent();      // handle standart event

  switch (MyEvent.currentEvent.code)
  {

    case ev100Hz:
      // refresh led
      animLed1.led.write();
      animLed2.led.write();
      animLed3.led.write();
      animLed4.led.write();
      animLed5.led.write();
      animLed1.led.reset();
      animLed1.step(MyEvent.currentEvent.param);
      animLed2.step(MyEvent.currentEvent.param);
      animLed3.step(MyEvent.currentEvent.param);
      animLed4.step(MyEvent.currentEvent.param);
      animLed5.step(MyEvent.currentEvent.param);
      break;

    case ev10Hz: {

        if ( BP0Down != (digitalRead(BP0) == LOW)) { // changement d'etat BP0
          BP0Down = !BP0Down;
          if (BP0Down) {
            MyEvent.setMillisecLED(500, 50);
            MyEvent.pushEvent(evBP0Down);
            MyEvent.pushDelayEvent(3000, evBP0LongDown); // arme un event BP0 long down
            MyEvent.removeDelayEvent(evBP0LongUp);
          } else {
            MyEvent.setMillisecLED(1000, 10);
            MyEvent.pushEvent(evBP0Up);
            MyEvent.pushDelayEvent(1000, evBP0LongUp); // arme un event BP0 long up
            MyEvent.removeDelayEvent(evBP0LongDown);
          }
        }



        uint8_t data1 = 0, data2 = 0, data3 = 0;

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

    //    case evClock:
    //      if (clockStep < 0) break;
    //      clockStep++;
    //      switch ( clockStep ) {
    //        case 1:
    //          setAnim(animLed5, 1, rvb_orange, 40);
    //          break;
    //        case 2:
    //          setAnim(animLed3, 1, rvb_orange, 40);
    //          break;
    //        case 3:
    //          setAnim(animLed4, 1, rvb_orange, 40);
    //          break;
    //        case 4:
    //          setAnim(animLed1, 1, rvb_orange, 40);
    //          clockStep = 0;
    //          break;
    //      }
    //      MyEvent.pushEventMillisec(300, evClock);
    //      break;
    //    case evConterClock:
    //      if (clockStep < 0) break;
    //      clockStep++;
    //      switch ( clockStep ) {
    //        case 1:
    //          setAnim(animLed5, 1, rvb_brun, 50);
    //          break;
    //        case 2:
    //          setAnim(animLed1, 1, rvb_brun, 50);
    //          break;
    //        case 3:
    //          setAnim(animLed4, 1, rvb_brun, 50);
    //          break;
    //        case 4:
    //          setAnim(animLed3, 1, rvb_brun, 50);
    //          clockStep = 0;
    //          break;
    //      }
    //      MyEvent.pushEventMillisec(300, evConterClock);
    //      break;
    //    case evStopClock:
    //      clockStep = -1;
    //      MyEvent.removeDelayEvent(evClock);
    //      MyEvent.removeDelayEvent(evConterClock);
    //      break;
    //         case evBP0Down:
    //      Serial.println(F("BP0 Down"));
    //      break;

    case evBP0Up:
      Serial.println(F("BP0 Up"));
      animLed1.set(100,0,100, rvb_green, 50);
      break;
    case evBP0Down:
      BP0Multi++;
      Serial.println(F("BP0 Down"));
      animLed2.set(100,10,100, rvb_blue, 50);
      break;

    case evBP0LongDown:
      Serial.println(F("BP0 Long Down"));
      //      if (multi == 5) {
      //        Serial.println(F("RESET"));
      //        MyEvent.pushEvent(doReset);
      //      }
      break;

    case evBP0LongUp:
      BP0Multi = 0;
      Serial.println(F("BP0 Long Up"));
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
