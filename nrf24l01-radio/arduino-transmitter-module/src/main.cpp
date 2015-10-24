#include  <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

// it prints the details of the nRF24 board
// to not use it just comment out "printf_begin()"
#include "printf.h"

#define CE_PIN   9
#define CSN_PIN 10

int msg[1];
RF24 txRadio(CE_PIN,CSN_PIN);
const uint64_t pipe = 0xE8E8F0F0E1LL;

// the transmitter should send a message every 3 seconds
const int TRANSMISSION_INTERVAL_MS = 3000;

void setup(void){
  Serial.begin(9600);
  // the following needs the Printf.h file
  printf_begin();
  txRadio.begin();
  txRadio.openWritingPipe(pipe);
  // print the configuration of the transmitter unit
  txRadio.printDetails();
}

void loop(void){
  int message = 111;
  msg[0] = message;
  txRadio.write(msg, 1);
  Serial.println("Transmitted: " + String(message));
  delay(TRANSMISSION_INTERVAL_MS);
}
