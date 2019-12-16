// uncomment when you have a model.h
// to tun the classification
// #define CLASSIFY

#define IN 4
#define NUM_SAMPLES 30
#define INTERVAL 100

double features[NUM_SAMPLES];

#if defined(CLASSIFY)
    #include "model.h"

    void classify() {
        Serial.print("Detected letter: ");
        Serial.println(classIdxToName(predict(features)));
    }
#endif

void setup() {
    Serial.begin(115200);
    pinMode(IN, INPUT_PULLUP);
}

void loop() {
    if (digitalRead(IN) == 0) {
        recordButtonStatus();
        printFeatures();
#if defined(CLASSIFY)
        classify();
#endif
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