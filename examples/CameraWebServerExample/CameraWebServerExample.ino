#include "eloquent.h"
#include "eloquent/networking/wifi.h"
#include "eloquent/vision/camera/esp32/webserver.h"
// replace according to your own camera
#include "eloquent/vision/camera/esp32/m5wide/jpeg/qqvga.h"



void setup() {
    Serial.begin(115200);

    while (!wifi.connectTo("Abc", "12345678"))
        Serial.println("Cannot connect to WiFi");

    while (!camera.begin())
        Serial.println("Cannot connect to camera");

    Serial.println("WiFi connected");
    Serial.println("Camera connected");

    webServer.start();
    Serial.print("Camera web server started at http://");
    Serial.println(WiFi.localIP());
}

void loop() {

}