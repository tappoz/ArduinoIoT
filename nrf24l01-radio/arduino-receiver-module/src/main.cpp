#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

// it prints the details of the nRF24 board
// to not use it just comment out "printf_begin()"
#include "printf.h"

#define CE_PIN   9
#define CSN_PIN 10

int msg[1];
RF24 rxRadio(CE_PIN,CSN_PIN);
const uint64_t pipe = 0xE8E8F0F0E1LL;
const int LED1 = 3;

// the receiver should sample every 1 second
const int SAMPLING_INTERVAL_MS = 1000;

void setup(void){
  Serial.begin(9600);
  rxRadio.begin();
  rxRadio.openReadingPipe(1,pipe);
  rxRadio.startListening();
  pinMode(LED1, OUTPUT);
  // print the configuration of the receiver unit
  rxRadio.printDetails();
}

void loop(void) {
  digitalWrite(LED1, LOW);
  if (rxRadio.available()) {
    while (rxRadio.available()) {
      rxRadio.read(msg, 1);
      int message = msg[0];
      if (message == 111){
        delay(10);
        Serial.println("Received this message: " + String(message));
        digitalWrite(LED1, HIGH);
      } else {
        Serial.println("Received not sure what: " + String(message));
        digitalWrite(LED1, LOW);
      }
      delay(SAMPLING_INTERVAL_MS);
      }
    }
  else {
    Serial.println("No radio available");
  }
}
