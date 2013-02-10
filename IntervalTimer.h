/* Copyright (c) 2013 Daniel Gilbert, loglow@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in the
Software without restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the
following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */



#ifndef __INTERVALTIMER_H__
#define __INTERVALTIMER_H__

#include <stdint.h>



class IntervalTimer {
  public: 
    bool begin(ISR newISR, float newPeriod);
    void end();
    static ISR PIT_ISR[NUM_PIT];
  private:
    typedef void (*ISR)();
    typedef volatile uint32_t* reg;
    enum {TIMER_OFF, TIMER_PIT};
    static const uint8_t NUM_PIT = 3;
    static const uint16_t MIN_VALUE = 639;
    static void enable_PIT();
    static void disable_PIT();
    static bool PIT_enabled;
    static bool PIT_used[NUM_PIT];
    bool allocate_PIT(uint32_t newValue);
    void start_PIT(uint32_t newValue);
    void stop_PIT();
    bool status;
    uint8_t PIT_id;
    reg PIT_LDVAL;
    reg PIT_TCTRL;
    uint8_t IRQ_PIT_CH;
    ISR myISR;
};



#endif



// EOF