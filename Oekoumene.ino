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
                  evNewLed,
              };




animLed_t animLed1 ;
animLed_t animLed2 ;
animLed_t animLed3 ;
animLed_t animLed4 ;
animLed_t animLed5 ;

animLed_t* ledSet[5] {&animLed1, &animLed2, &animLed3, &animLed4, &animLed5 };
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
e_rvb baseColor = rvb_orange;



void setup() {
  // Initialisation Hard des IO
  pinMode(LED_LIFE, OUTPUT);
  pinMode(BP0, INPUT_PULLUP);

  // Serial
  Serial.begin(115200);
  Serial.println(F(APP_VERSION));

  // init event
  MyEvent.begin();
  MyEvent.pushDelayEvent(1000, evNewLed);

}

int N = 1;
bool BP0Down = HIGH;





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


    case  evNewLed: {
        MyEvent.pushDelayEvent(1500 + random(0, 2000), evNewLed);
        int aLed = random(0, 5);
        while (ledSet[aLed]->enable ) aLed = random(0, 5);
        ledSet[aLed]->set(250, 50, 250, baseColor, 100);
      }


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
      }
      break;








    case evBP0Up:
      Serial.println(F("BP0 Up"));

      break;
    case evBP0Down:
      randomSeed(micros());
      BP0Multi++;
      Serial.println(F("BP0 Down"));
      baseColor = (e_rvb)(baseColor + 1);
      if (baseColor == rvb_black) baseColor = rvb_white;
      animLed2.set(200, 10, 200, baseColor, 100);
      break;

    case evBP0LongDown:
      Serial.println(F("BP0 Long Down"));

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

      if (MyEvent.inputString.equals(F("A"))) {
        D_println(animLed1.enable);
        D_println(animLed2.enable);
        D_println(animLed3.enable);
      }

  }
}
