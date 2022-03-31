#include <WiFi.h>
#include "Converter.h"
#include "Classifier.h"


Eloquent::Projects::WifiIndoorPositioning positioning;
Eloquent::ML::Port::DecisionTree classifier;


void setup() {
    Serial.begin(115200);
    WiFi.disconnect();
}


void loop() {
    positioning.scan();
    Serial.print("You're in ");
    Serial.println(classifier.predictLabel(positioning.features));
    delay(3000);
}