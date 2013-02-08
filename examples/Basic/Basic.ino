#include "PITimer.h"

void timerCallback0() {
  // runs every second
  Serial.print("Timer 0: ");
  Serial.print(PITimer0.count());
  Serial.print("\t");
  Serial.print("Timer 1: ");
  Serial.print(PITimer1.count());
  Serial.print("\t");
  Serial.print("Timer 2: ");
  Serial.println(PITimer2.count());
}

void timerCallback1() {
  // runs every 5 seconds
  PITimer2.zero();
}

void timerCallback2() {
  // runs 2000 times per second
}

void setup() {
  Serial.begin(true);
  PITimer1.period(5);
  PITimer2.frequency(2000);
  PITimer2.start(timerCallback2); // 2 kHz
  PITimer1.start(timerCallback1); // 5 seconds
  PITimer0.start(timerCallback0); // 1 second
}

void loop() {
}
