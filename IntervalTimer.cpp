/*

Copyright (c) 2013 Daniel Gilbert, loglow@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/



#include "IntervalTimer.h"
#include <mk20dx128.h>
#include <stdint.h>
#include <math.h>



// ------------------------------------------------------------
// these are the pre-defined timer objects corresponding
// to the 4 internal Periodic Interrupt Timers (PITs).
// PIT3 is disabled because it conflicts with tone()
// ------------------------------------------------------------
IntervalTimer Timer0(0);
IntervalTimer Timer1(1);
IntervalTimer Timer2(2);
//IntervalTimer Timer3(3);



// ------------------------------------------------------------
// these are the ISRs (Interrupt Service Routines)
// that get called by each timer when it fires.
// they're defined here a) so that they can auto-clear
// themselves and b) so the user can specify a custom
// ISR of their own, and even reassign it as needed
// ------------------------------------------------------------
void pit0_isr() { PIT_TFLG0 = 1; Timer0.myISR(); }
void pit1_isr() { PIT_TFLG1 = 1; Timer1.myISR(); }
void pit2_isr() { PIT_TFLG2 = 1; Timer2.myISR(); }
//void pit3_isr() { PIT_TFLG3 = 1; Timer3.myISR(); }



// ------------------------------------------------------------
// initializer for the PITimer class, mostly used to forward our
// generic pointers to a specific set of regs. we also need to
// enable the overall clock access to the PIT module, both via the
// SIM (System Integration Module) and the PIT's own MCR (Module
// Control Register). enabling these global controls for each timer
// isn't necessary, but it doesn't do any harm either.
// ------------------------------------------------------------
IntervalTimer::IntervalTimer(uint8_t ID) {
       if (ID == 0) { PIT_LDVAL = &PIT_LDVAL0; PIT_TCTRL = &PIT_TCTRL0; IRQ_PIT_CH = IRQ_PIT_CH0; }
  else if (ID == 1) { PIT_LDVAL = &PIT_LDVAL1; PIT_TCTRL = &PIT_TCTRL1; IRQ_PIT_CH = IRQ_PIT_CH1; }
  else if (ID == 2) { PIT_LDVAL = &PIT_LDVAL2; PIT_TCTRL = &PIT_TCTRL2; IRQ_PIT_CH = IRQ_PIT_CH2; }
  else if (ID == 3) { PIT_LDVAL = &PIT_LDVAL3; PIT_TCTRL = &PIT_TCTRL3; IRQ_PIT_CH = IRQ_PIT_CH3; }
  SIM_SCGC6 |= SIM_SCGC6_PIT;
  PIT_MCR = 0;
}



// ------------------------------------------------------------
// this function inits and starts the timer, using the specified
// function as a callback and the period provided. must be passed
// the name of a function taking no arguments and returning void.
// make sure this function can complete within the time allowed
// ------------------------------------------------------------
void IntervalTimer::begin(void (*newISR)(), float newPeriod) {
  uint32_t newValue = floor(F_BUS * newPeriod + 0.5) - 1;
  if (newValue == UINT32_MAX) newValue = UINT32_MAX - 1;
  else if (newValue < valueMin) newValue = valueMin;
  *PIT_LDVAL = newValue;
  *PIT_TCTRL = 3;
  myISR = newISR;
  NVIC_ENABLE_IRQ(IRQ_PIT_CH);
}



// ------------------------------------------------------------
// stops the timer and disables its interrupts
// ------------------------------------------------------------
void IntervalTimer::end() {
  NVIC_DISABLE_IRQ(IRQ_PIT_CH);
  *PIT_TCTRL = 0;
}



// EOF