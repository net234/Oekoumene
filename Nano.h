#pragma once

#define __BOARD__NANO RF__
#define D_println(x) Serial.print(F(#x " => '")); Serial.print(x); Serial.println("'");

//   Nano RF
//#define TX1     //!TXD        17  //!RXLED
//#define RX0     //!RXD        30  //!TXLED
#define D2     2 //!HI2C_SDA   WS812
#define D3      //!HI2C_SCL
#define D4      // 
#define D5      //
#define D6      //
#define D7      //           BP1  
#define D8      //           BP0   
#define D9      //!RF24_CSN
#define D10     //!RF24_CE
#define D11     //!SPI_MOSI
#define D12     //!SPI_MISO 
#define D13   13  //!SPI_CLK   !LED
//---------------------

#define LED_LIFE  D13
#define LED_ON  HIGH

#define pinBP0 8 // D2
#define PIN_WS2812 2 // D8
