#include "iris.h"

double features[4];

void setup() {
    Serial.begin(115200);
}

void loop() {
    if (Serial.available()) {
        for (int i = 0; i < 4; i++) {
            String feature = Serial.readStringUntil(',');

            features[i] = atof(feature.c_str());
        }

        printFeatures();
        Serial.print("Detected species: ");
        Serial.println(classIdxToName(predict(features)));
    }

    delay(10);
}

void printFeatures() {
    const uint16_t numFeatures = sizeof(features) / sizeof(double);

    Serial.print("You entered: ");

    for (int i = 0; i < numFeatures; i++) {
        Serial.print(features[i]);
        Serial.print(i == numFeatures - 1 ? '\n' : ',');
    }
}