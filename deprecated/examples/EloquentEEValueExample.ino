#include <EloquentEEValue.h>

/**
 * eeValue synchronizes a variable to the EEPROM, so it keeps its value
 * even after reboots. It is a template class, so you have to provide a
 * primitive type at definition time.
 * Several shortcuts are available:
 *  - eeUint8
 *  - eeUint16
 *  - eeUint32
 *  - eeInt8
 *  - eeInt16
 *  - eeInt32
 * You can directy access its value via `value()` and `set(newValue)`
 */

using namespace Eloquent;

// The argument is the starting address in EEPROM
// !!! eeValue uses 1 byte for internal use, so you have to allocate
// !!! your addresses accordingly
eeInt32 value(0);

// This is wrong and will produce unexpected behavior
// because eeInt32 size is 4 byte for int32_t + 1 byte for internal use
// eeInt32 value2(4);

// This is fine
eeInt16 value2(5);


void setup() {
    Serial.begin(9600);
    // !!! Never forget to begin. You can set a default value if you want
    value.begin();
    delay(1000);

    Serial.print("At first boot, value should be 0: ");
    Serial.println(value.value());
    Serial.println("On subsequent boots, it should be greater than 0");

    // eeValue implements most common operators
    value = 1;
    value++;
    value--;
    value += 10;
    value -= 5;

    Serial.print("Value should be 1 + 1 - 1 + 10 - 5 = 6: ");
    Serial.println(value.value());

    Serial.print("Value - 3 should be 3: ");
    Serial.println(value - 3);
}


void loop() {
    value++;
    Serial.print("Now value is: ");
    Serial.println(value.value());
    delay(1000);
}