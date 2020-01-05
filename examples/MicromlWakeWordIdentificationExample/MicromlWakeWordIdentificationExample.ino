#include <arduinoFFT.h>
// uncomment when doing classification
 #include "model.h"

#define MIC A0
#define NUM_SAMPLES 64
#define SAMPLING_FREQUENCY 1024
#define INTERVAL 5
#define SOUND_THRESHOLD 3

unsigned int samplingPeriod;
unsigned long microSeconds;

int32_t backgroundSound;
double features[NUM_SAMPLES];
arduinoFFT fft;


void setup() {
    Serial.begin(115200);
    pinMode(MIC, INPUT);

    samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY));
    calibrate();
}

void loop() {
    if (!soundDetected()) {
        delay(10);
        return;
    }

    captureWord();
    printFeatures();

    // uncomment when doing classification
     Serial.print("You said ");
     Serial.println(classIdxToName(predict(features)));

    delay(1000);
}

/**
 * Get analog readings
 * @return
 */
int16_t readMic() {
    return analogRead(MIC);
    return  (analogRead(MIC) - 512) >> 2;
}

/**
 * Get "ambient" volume
 */
void calibrate() {
    for (int i = 0; i < 200; i++)
        backgroundSound += readMic();

    backgroundSound /= 200;

    Serial.print("Threshold set at ");
    Serial.println(backgroundSound);
}

bool soundDetected() {
    return abs(readMic() - backgroundSound) >= SOUND_THRESHOLD;
}

void captureWord() {
    for (uint16_t i = 0; i < NUM_SAMPLES; i++) {
        microSeconds = micros();
        features[i] = readMic();

        while(micros() < (microSeconds + samplingPeriod));
    }

    fft.Windowing(features, NUM_SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
}

void printFeatures() {
    const uint16_t numFeatures = sizeof(features) / sizeof(double);

    for (int i = 0; i < numFeatures; i++) {
        Serial.print(features[i]);
        Serial.print(i == numFeatures - 1 ? '\n' : ',');
    }
}