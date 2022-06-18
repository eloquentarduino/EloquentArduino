/**
 * Capture data from VL53L5CX 8x8 Time of Flight sensor
 */
#include <Wire.h>
#include <eloquent.h>
#include <eloquent/modules/vl53l5cx/8x8.h>



void setup() {
    Serial.begin(115200);
    Wire.begin();

    // (optional) turn on high speed communication
    Wire.setClock(1000000);
    vllcx.highFreq();

    // (optional) truncate readings lower than 30 (3 cm) and higher than 500 (50 cm)
    vllcx.truncateLowerThan(30);
    vllcx.truncateHigherThan(500);

    // (optional) rescale distances from millimeters to 0-1 range (aka normalize distances)
    vllcx.scaleToRange(0, 1);

    if (!vllcx.begin())
        eloquent::abort(Serial, "vl53l5cx not found");

    Serial.println("vl53l5cx is ok");
}


void loop() {
    // await for new data
    if (!vllcx.hasNewData() || !vllcx.read())
        return;

    // print readings to Serial
    vllcx.printTo(Serial);
    delay(100);
}
