#include "IntervalTimer.h"

uint32_t timerCount0;
uint32_t timerCount1;
uint32_t timerCount2;

void printTimers() {
  Serial.print("Timer0: ");
  Serial.print(timerCount0);
  Serial.print("\t");
  Serial.print("Timer1: ");
  Serial.print(timerCount1);
  Serial.print("\t");
  Serial.print("Timer2: ");
  Serial.println(timerCount2);
}

void timerCallback0() {
  timerCount0++;
}

void timerCallback1() {
  timerCount1++;
  timerCount0 = 0;
}

void timerCallback2() {
  timerCount2++;
  printTimers();
}

void setup() {
  Serial.begin(true);
  Timer0.begin(timerCallback0, 1.0 / 2000);
  Timer1.begin(timerCallback1, 5.0);
  Timer2.begin(timerCallback2, 1.0);
}

void loop() {
}
