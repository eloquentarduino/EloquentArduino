#include <EloquentLogging.h>
#include <EloquentPin.h>

/**
 * The Pin class lets you manipulate a pin like a number.
 * You can assign a value to it and use arithmetic and boolean operators.
 * Plus it implements utility methods to test and update the pin state.
 * Each pin keeps track of its previous value, so an input pin can determine
 * if its value changed, is rising or is falling, for example.
 */


using namespace Eloquent;


Pin analogOut(9, OUTPUT, PinMode::ANALOG);
Pin analogIn(A0, INPUT, PinMode::INPUT);


void setup() {
    Serial.begin(9600);
    delay(1000);

    analogOut.turnOff();
    assert("Pin value should be 0", analogOut == 0);
    delay(1000);

    analogOut.turnOn();
    assert("Pin value should be 255", analogOut == 255);
    delay(1000);

    analogOut -= 100;
    assert("Pin value should be 155", analogOut == 155);
    assert("Pin delta should be -100", analogOut.delta() == -100);
    assert("Pin value should be falling", analogOut.falling());
    delay(1000);

    // Here pin value is 155, so it's ON
    analogOut.toggle();
    assert("Pin should be off", analogOut.isOff());
    delay(1000);

    // fade in
    while (analogOut < 255) {
        analogOut += 10;
        delay(20);
    }

    // fade out
    while (analogOut > 0) {
        analogOut -= 10;
        delay(20);
    }

    delay(1000);
    analogOut.blink(5, 1000);
}


void loop() {
    uint16_t read = analogIn.read();

    Serial.print("Read: ");
    Serial.println(read);
    delay(1000);
}