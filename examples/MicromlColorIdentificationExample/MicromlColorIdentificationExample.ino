// uncomment when you have a model.h
// to tun the classification
// #define CLASSIFY

#define S2 2
#define S3 3
#define sensorOut 4

double features[3];

#if defined(CLASSIFY)
    #include "model.h"

    void classify() {
        Serial.print("Detected color: ");
        Serial.println(classIdxToName(predict(features)));
    }
#endif

void setup() {
    Serial.begin(115200);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(sensorOut, INPUT);
}

void loop() {
    readRGB();
    printFeatures();
#if defined(CLASSIFY)
     classify();
#endif
    delay(100);
}

int readComponent(bool s2, bool s3) {
    delay(10);
    digitalWrite(S2, s2);
    digitalWrite(S3, s3);

    return pulseIn(sensorOut, LOW);
}

void readRGB() {
    features[0] = readComponent(LOW, LOW);
    features[1] = readComponent(HIGH, HIGH);
    features[2] = readComponent(LOW, HIGH);
}

void printFeatures() {
    const uint16_t numFeatures = sizeof(features) / sizeof(double);

    for (int i = 0; i < numFeatures; i++) {
        Serial.print(features[i]);
        Serial.print(i == numFeatures - 1 ? '\n' : ',');
    }
}