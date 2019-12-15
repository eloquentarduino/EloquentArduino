#define IN 4
#define NUM_SAMPLES 30
#define INTERVAL 100


double features[NUM_SAMPLES];


void recordButtonStatus() {
    for (int i = 0; i < NUM_SAMPLES; i++) {
        features[i] = digitalRead(IN);
        delay(INTERVAL);
    }
}

#include "record.h"
//#include "classify.h"
