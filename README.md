# PITimer

## PIT (Periodic Interrupt Timer) library for Teensy 3.0

### Overview and setup

Four built-in timers are available, numbered 0-3: `PITimer0`, `PITimer1`, `PITimer2`, and `PITimer3`. Note that `PITimer3` is disabled by default because it conflicts with the existing `tone()` functionality. Each timer's period defaults to one second. Change this with the `value()`, `period()`, or `frequency()` functions. If they're called without arguments, these functions will instead return their respective values. Period is specified in seconds, and frequency is specified in hertz. Floating-point values are fine for either. You can update these values on-the-fly, while a timer is running, if you want to.

### Limitations

Invalid values will be _silently_ fixed. For example, a period of 100 (seconds) will be changed to about 89.48 which is the __absolute maximum__. Likewise, only __specific__ higher frequencies are available. For example, a frequency of 74000 (74 kHz) will be changed to about 73959.94 because of the granularity between cycle counts. Use `period()` and `frequency()` to check the actual values of your timers if you're setting them close to the extremes. Also keep in mind that the `value()` function returns/requires __1 less__ than the actual/desired bus cycle count.

### Valid ranges (at 48 MHz bus)

- __Value:__ `639` to `4294967294` (2^32 - 2) bus clocks
- __Period:__ `0.000013312` to `89.478485312` seconds (14 ns to 89 s)
- __Frequency:__ `0.011175871` to `75000` hertz (12 mHz to 75 kHz)

### Starting and stopping

Start a timer by calling it's `start()` function, and passing it the name of the function you'd like it to execute periodically (this is known as its _callback_ function). Stop a timer by calling its `stop()` function. Once started, the periodic interrupts will call their specified callback functions whenever they expire. You can change a callback function simply by stopping a timer and restarting it. Your callback routines should have no return value. The `reset()` function will reset the timer's countdown so that one full period will elapse from when it's called, thereby delaying when the next interrupt is to be generated.

### Checking status

The `current()` function will return the remaining countdown value of the current timer cycle. This value is measured in individual bus clock cycles. The default bus speed for the Teensy 3.0 is 48 MHz (aka 48,000,000 cycles). Likewise, `remains()` will return the remaining time on the counter (in seconds) as a floating-point value. Calling the `count()` function will return the number of times the timer has executed, while calling `zero()` will reset this counter. Last but not least, you can use `running()` to check whether the timer is active or not.

### Contact

- Daniel Gilbert
- loglow@gmail.com
