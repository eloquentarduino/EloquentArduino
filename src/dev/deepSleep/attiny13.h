#pragma once


#ifdef __AVR_ATtiny13__

#include <avr/sleep.h>

#define SLEEP_FOREVER  128
#define SLEEP_016MS    (period_t)0
#define SLEEP_125MS    (1<<WDP1) | (1<<WDP0)
#define SLEEP_250MS    (1<<WDP2)
#define SLEEP_500MS    (1<<WDP2) | (1<<WDP0)
#define SLEEP_1SEC     (1<<WDP2) | (1<<WDP1)
#define SLEEP_2SEC     (1<<WDP2) | (1<<WDP1) | (1<<WDP0)
#define SLEEP_4SEC     (1<<WDP3)
#define SLEEP_8SEC     (1<<WDP3) | (1<<WDP0)


// without that empty declaration, I got some problems with my other code. Maybe you don't need that.
//ISR(WDT_vect) {
//}


void deepSleep(byte b) {
    {
        ACSR |= (1 << ACD); //Analog comparator off
        ACSR = ADMUX = ADCSRA = 0;
    }

    if (b != SLEEP_FOREVER) {
        WDTCR |= b;    //Watchdog
        // Enable watchdog timer interrupts
        WDTCR |= (1 << WDTIE);
    }
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    cli(); // No interrupts; timed sequence
    sei(); // Enable global interrupts or we never wake
    sleep_mode();
    sleep_disable();
}

#endif