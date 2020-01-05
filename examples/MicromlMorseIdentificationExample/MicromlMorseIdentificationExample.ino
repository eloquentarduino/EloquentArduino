// uncomment when doing classification
#include "model.h"

#define IN 4
#define NUM_SAMPLES 30
#define INTERVAL 100

double features[NUM_SAMPLES];


void setup() {
    Serial.begin(115200);
    pinMode(IN, INPUT_PULLUP);
    Serial.println("Begin");
    self_test();
}

void loop() {
    if (digitalRead(IN) == 0) {
        recordButtonStatus();
        printFeatures();

        // uncomment when doing classification
        Serial.print("Detected letter: ");
        Serial.println(classIdxToName(predict(features)));

        delay(1000);
    }

    delay(10);
}

void printFeatures() {
    const uint16_t numFeatures = sizeof(features) / sizeof(double);

    for (int i = 0; i < numFeatures; i++) {
        Serial.print(features[i]);
        Serial.print(i == numFeatures - 1 ? '\n' : ',');
    }
}

void recordButtonStatus() {
    for (int i = 0; i < NUM_SAMPLES; i++) {
        features[i] = digitalRead(IN);
        delay(INTERVAL);
    }
}