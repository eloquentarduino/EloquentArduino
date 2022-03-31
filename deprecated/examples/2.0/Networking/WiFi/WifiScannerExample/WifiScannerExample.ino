#include <WiFi.h>
#include "eloquent.h"
#include "eloquent/networking/wifi/WifiScanner.h"


String location;


void setup() {
    Serial.begin(115200);
    delay(2000);
    Serial.println("Instructions:");
    Serial.println("\tEnter the name of the location to start scanning");
    Serial.println("\tEnter 'stop' to stop scanning");
}

void loop() {
    // await user to input his current location or "stop" to abort scanning
    if (Serial.available()) {
        location = Serial.readStringUntil('\n');
    }

    // if a location is set, perform scan
    if (location != "" && location != "stop") {
        // expected line format is `$location : $access_points_as_json`
        Serial.print(location);
        Serial.print(": ");
        wifiScanner.scan();
        wifiScanner.printAsJson(Serial);
        delay(3000);
    }
}
