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
    float *features = positioning.getFeatures();

    for (int i = 0; i < 9; i++) {
        Serial.print(features[i]);
        Serial.print(", ");
    }

    Serial.print("\nYou're in ");
    Serial.println(classifier.predictLabel(features));
}