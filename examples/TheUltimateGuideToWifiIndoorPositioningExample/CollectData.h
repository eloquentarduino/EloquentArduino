#include <WiFi.h>

#define print(string) Serial.print(string);
#define quote(string) print('"'); print(string); print('"');


String location = "";


/**
 *
 */
void setup() {
    Serial.begin(115200);
    delay(3000);
    WiFi.disconnect();
    print("Enter 'scan {location}' to start the scanning and 'stop' to stop scanning\n");
}

/**
 *
 */
void loop() {
    // look for new command
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');

        if (input.indexOf("scan ") == 0) {
            location = input.substring(5);
            print("Started scanning...");
            print(location);
            print("\n");
        }
        else {
            print("Command not found. Enter 'scan {location}' to start the scanning\n");
            location = "";
        }
    }

    // if location is set, scan networks
    if (location != "") {
        int numNetworks = WiFi.scanNetworks();

        // print location
        print('{');
        quote("__location");
        print(": ");
        quote(location);
        print(", ");

        // print each network SSID and RSSI
        for (int i = 0; i < numNetworks; i++) {
            quote(WiFi.SSID(i));
            print(": ");
            print(WiFi.RSSI(i));
            print(i == numNetworks - 1 ? "}\n" : ", ");
        }

        delay(1000);
    }
}