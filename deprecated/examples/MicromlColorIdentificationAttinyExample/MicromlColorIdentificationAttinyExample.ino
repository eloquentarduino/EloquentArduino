// On Attiny we can only do classification
// since there's no Serial
// We'll light a led based on the detected color

#include "model.h"

#define S2 2
#define S3 3
#define sensorOut 4
#define LED 0

double features[3];


void setup() {
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(sensorOut, INPUT);
}

void loop() {
    readRGB();
    classify();
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

void classify() {
    uint8_t classIdx = predict(features);

    if (classIdx == 0)
        return;

    for (uint8_t i = 0; i < classIdx; i++) {
        digitalWrite(LED, HIGH);
        delay(10);
        digitalWrite(LED, LOW);
        delay(10);
    }
}