#include <Wire.h>
#include <eloquent.h>
#include <eloquent/modules/vl53l5cx/stream.h>

#define RESOLUTION 8*8
#define NUM_FRAMES 16


Eloquent::Modules::VL53L5CXStream<RESOLUTION, NUM_FRAMES> stream;



void setup() {
    Serial.begin(115200);
    Wire.begin();

    // turn on high speed communication
    stream.highFreq();

    // truncate readings further than 2 meters
    stream.truncateAt(2000);

    // you may optionally rescale to a given range
    stream.setRange(0, 1);

    // emit the "queue" event once every 4 frames
    stream.throttle(4);

    if (!stream.begin())
        eloquent::abort(Serial, "vl53l5cx not found");

    Serial.println("vl53l5cx is ok");
}


void loop() {
    if (stream.queue()) {
        stream.printTo(Serial);
        delay(100);
    }
}
