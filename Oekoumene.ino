/*******************************
  Oekoumene V1.0  Animation lumioneuse avec WS2812

   (C) net234 Pierre HENRY 03/2021



*/

#include <Arduino.h>
#include "Nano.h"




#define APP_VERSION   "Oekoumene V1.1"

//enum typeEvent { evNill=0, ev100Hz, ev10Hz, ev1Hz, ev24H, evInChar,evInString,evUser=99 };
enum myEvent  {
  evBP0 = 100,
  evLed0,
  evNewLed,
};

// Gestionaire d'evenemnt
#include <BetaEvents.h>
#include "WS2812.h"
#include  "ledSet.h"




animLed_t animLed1 ;
animLed_t animLed2 ;
animLed_t animLed3 ;
animLed_t animLed4 ;
animLed_t animLed5 ;
animLed_t animLed6 ;
animLed_t animLed7 ;
animLed_t animLed8 ;
animLed_t animLed9 ;


animLed_t* ledSet[9] {&animLed1, &animLed2, &animLed3, &animLed4, &animLed5, &animLed6, &animLed7, &animLed8, &animLed9 };
int clockStep = -1;







uint8_t BP0Multi = 0;
e_rvb baseColor = rvb_orange;



void setup() {
  // Initialisation Hard des IO
  //  pinMode(LED_LIFE, OUTPUT);
  //  pinMode(BP0, INPUT_PULLUP);

  // Serial
  Serial.begin(115200);
  Serial.println(F(APP_VERSION));

  // init event
  MyEvents.begin();
  MyEvents.pushDelayEvent(1000, evNewLed);

}

int N = 1;
//bool BP0Down = HIGH;





void loop() {
  MyEvents.getEvent();       // get standart event
  MyEvents.handleEvent();      // handle standart event

  switch (MyEvents.currentEvent.code)
  {

    case ev100Hz:
      // refresh led
      animLed1.led.write();
      animLed2.led.write();
      animLed3.led.write();
      animLed4.led.write();
      animLed5.led.write();
      animLed6.led.write();
      animLed7.led.write();
      animLed8.led.write();
      animLed9.led.write();
      animLed1.led.reset();
      animLed1.step(MyEvents.currentEvent.ext);
      animLed2.step(MyEvents.currentEvent.ext);
      animLed3.step(MyEvents.currentEvent.ext);
      animLed4.step(MyEvents.currentEvent.ext);
      animLed5.step(MyEvents.currentEvent.ext);
      animLed6.step(MyEvents.currentEvent.ext);
      animLed7.step(MyEvents.currentEvent.ext);
      animLed8.step(MyEvents.currentEvent.ext);
      animLed9.step(MyEvents.currentEvent.ext);


      break;


    case  evNewLed: {
        MyEvents.pushDelayEvent(1500 + random(0, 2000), evNewLed);
        int aLed = random(0, 9);
        while (ledSet[aLed]->enable ) aLed = random(0, 9);
        D_println(aLed);
        ledSet[aLed]->set(250, 50, 250, baseColor, 100);
      }
      break;


    case evBP0:
      D_println(MyEvents.currentEvent.ext);
      switch (MyEvents.currentEvent.ext) {




        case evxBPUp:
          Serial.println(F("BP0 Up"));

          break;
        case evxBPDown:
          randomSeed(micros());
          BP0Multi++;
          Serial.println(F("BP0 Down"));
          baseColor = (e_rvb)(baseColor + 1);
          if (baseColor == rvb_black) baseColor = rvb_white;
          animLed1.set(200, 10, 200, baseColor, 100);
          break;

        case evxBPLongDown:
          Serial.println(F("BP0 Long Down"));

          break;

        case evxBPLongUp:
          BP0Multi = 0;
          Serial.println(F("BP0 Long Up"));
          break;

      }
      break; // evBP0

    // eventuelles commande via le port serie
    case evInString:
      //      Serial.print(F("evInString '"));
      //      Serial.print(MyEvent.inputString);
      //      Serial.println("'");


      if (MyKeyboard.inputString.equals(F("RESET"))) {
        Serial.println("resetting");
        delay(500);
        helperReset();
        Serial.println("--?-?--");
      }

      if (MyKeyboard.inputString.equals(F("A"))) {
        D_println(animLed1.enable);
        D_println(animLed2.enable);
        D_println(animLed3.enable);
      }
      break;
  }
}
