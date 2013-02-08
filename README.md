# IntervalTimer

## Timer library for Teensy 3.0

### Overview and usage

Four built-in timers are available, numbered 0-3: `Timer0`, `Timer1`, `Timer2`, and `Timer3`. Note that `Timer3` is disabled by default because it conflicts with the existing `tone()` functionality. Start a timer by calling it's `begin()` function, and passing it the name of the function you'd like it to execute periodically (this is known as its _callback_ function), as well as its _period_ in seconds as a floating-point value. For example:

    Timer0.begin(timerCallback0, 5.0);

Once started, the periodic interrupts will call their specified callback functions whenever they expire. You can change a callback function simply by stopping a timer and restarting it. Your callback routines should have no return value nor any arguments:

    void timerCallback0() {}

Stop a timer by calling its `end()` function:

    Timer0.end();

### Limitations

Invalid period values will be _silently_ fixed. For example, a period of 100 (seconds) will be changed to about 89.48 which is the __absolute maximum__. Assuming a 48 MHz bus, the valid range for period is `0.000013312` to `89.478485312` (this translates to about 14 ns to 89 s).

### Contact

- Daniel Gilbert
- loglow@gmail.com
