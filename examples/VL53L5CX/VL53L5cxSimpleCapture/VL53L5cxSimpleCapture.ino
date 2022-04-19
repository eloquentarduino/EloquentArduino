/**
 * Capture data from VL53L5CX 8x8 Time of Flight sensor
 */
#include <Wire.h>
#include <eloquent.h>
#include <eloquent/modules/vl53l5cx.h>



void setup() {
    Serial.begin(115200);
    Wire.begin();

    // turn on high speed communication
    tof8x8.highFreq();

    // truncate readings at 2 meters
    tof8x8.truncateAt(2000);

    // you may optionally rescale to a given range
    tof8x8.scale(0, 1);

    if (!tof8x8.begin())
        eloquent::abort(Serial, "vl53l5cx not found");

    Serial.println("vl53l5cx is ok");
}


void loop() {
    if (tof8x8.read()) {
        tof8x8.printTo(Serial);
        delay(100);
    }
}
