#pragma once

#include <avr/sleep.h>
#include <avr/wdt.h>

#define SLEEP_1S 0b000110
#define SLEEP_2S 0b000111
#define SLEEP_4S 0b100000
#define SLEEP_8S 0b100001


ISR(WDT_vect) {
    wdt_disable();
}

void deepSleep(const byte interval) {
    wdt_reset();

    MCUSR = 0;
    WDTCSR |= 0b00011000;
    WDTCSR =  0b01000000 | interval;
    ADCSRA &= ~_BV(ADEN);

    set_sleep_mode (SLEEP_MODE_PWR_DOWN);
    sleep_bod_disable();
    sei();
    sleep_mode();

    ADCSRA |= _BV(ADEN);
}