#include <Arduino.h>

#include "../lib/rc-switch/RCSwitch.h"
#include "state.h"

// #define NO_DEVICE
// #define GARAGE_RIGHT
#define NO_DEVICE

#if defined NO_DEVICE
#define openCode 0x000001
#define closedCode 0x000002
#elif defined GARAGE_RIGHT
#define openCode 0x9981B8
#define closedCode 0x480539
#elif defined GARAGE_LEFT
#define openCode 0x4E2070
#define closedCode 0x22C3F7
#endif

#define sendPin 3
#define ledPin 13
#define sensorPin 10
#define pollIntMin 400000L
#define pollIntMax 600000L

RCSwitch mySwitch = RCSwitch();
StableState state = StableState();
uint32_t lastSent;

uint32_t getCode(int state) {
  if (state == HIGH) {
    return closedCode;  // High is closed
  }
  return openCode;  // Low is open
}

void acknowledge(uint8_t led) {
  uint8_t state = LOW;
  digitalWrite(led, state);
  for (int i = 0; i < 3; i++) {
    state = state == LOW ? HIGH : LOW;
    digitalWrite(led, state);
    delay(500);
  }
  digitalWrite(led, LOW);
}

void setup() {
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LOW);

  mySwitch.enableTransmit(sendPin);
  mySwitch.setProtocol(1);

  lastSent = millis();
}

void loop() {
  if (state.add(digitalRead(sensorPin)) || millis() - lastSent > random(pollIntMin, pollIntMax)) {
    uint32_t code = getCode(state.get());
    mySwitch.send(code, 24);
    lastSent = millis();
    acknowledge(ledPin);
  }

  delay(250);
}
