#include "iris.h"


void setup() {
    Serial.begin(115200);
}


void loop() {
    if (Serial.available()) {
        double features[4];

        for (int i = 0; i < 4; i++) {
            String feature = Serial.readStringUntil(',');

            features[i] = atof(feature.c_str());
        }

        Serial.print("Detected species: ");
        Serial.println(classIdxToName(predict(features)));
    }

    delay(10);
}