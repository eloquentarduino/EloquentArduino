#include <EloquentEvery.h>

int interval = 3000;


void setup() {
    Serial.begin(9600);

    // await 1 second for Serial to be available
    bool serialAvailable = await(Serial, 1 * Second);
    Serial.println(serialAvailable ? "SERIAL" : "NO SERIAL");
}

void loop() {
    every(1000) {
        Serial.println("Every 1 second");
    }

    every(2 * Seconds) {
        Serial.println("Every 2 seconds");
    }

    every(interval)
        Serial.println("Every 3 seconds");

    // This doesn't work
    //every(interval + 1000)
    //    Serial.println("Every 4 seconds")
}