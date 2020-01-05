#include "iris.h"

double features[4];

void setup() {
//    Serial.begin(115200);
}

void loop() {
    double features[] = {1, 2, 3, 4};
    digitalWrite(1, predict(features));

    delay(10);
}