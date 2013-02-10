# IntervalTimer

## Timer library for Teensy 3.0

### Overview and usage

Start a timer by creating a new `IntervalTimer` object and then calling it's `begin()` function, passing it the name of the function you'd like it to execute periodically (this is known as its _callback_ function), as well as its _period_ in seconds as a floating-point value:

    IntervalTimer timer0;
    timer0.begin(timerCallback0, 5.0);

Once started, the specified callback function will be called at a regular interval. You can change a callback function simply by stopping the timer and restarting it. Your callback routines should have no return value nor any arguments, and they should contain as little code as necessary. Any external variables they modify should be marked as volatile. For example:

    volatile uint32_t timerCounter0;
    void timerCallback0() {
      timerCounter0++;
    }

Stop a timer by calling its `end()` function:

    timer0.end();

### Details and limitations

Timers are dynamically allocated to hardware resources. A call to the `begin()` function will return `true` if the timer was able to be allocated and started, whereas it will return `false` if all hardware resources are already being used. A resource in use will become available to other timers after the timer using it has been stopped. At present you can have up to __three__ `IntervalTimer` objects operating at any given time. Further development will increase this number.

Currently, this library utilizes the PIT (Periodic Interrupt Timer) modules, of which there are four. However, only three are available for general use because one is being used by the built-in `tone()` functionality. The first timer to be allocated to a PIT module will enable the PIT clock and the last timer using a PIT module to be stopped will disable the PIT clock.

Invalid period values will be _silently_ fixed. For example, assuming the default bus speed of 48 MHz, a specified period of 100 seconds will be shortened to about 89.48 seconds, which is the __absolute maximum__ period. The valid range for period at this bus speed is `0.000013312` to `89.478485312` (approximately 14 microseconds to 89 seconds).

### Contact and copyright

- Copyright 2013 Daniel Gilbert, loglow@gmail.com
- MIT License, http://opensource.org/licenses/MIT
