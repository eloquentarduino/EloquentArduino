#include "model.h"

void setup() {
    Serial.begin(115200);
    pinMode(IN, INPUT_PULLUP);
}

void loop() {
    if (digitalRead(IN) == 0) {
        recordButtonStatus();
        Serial.print("Detected letter: ");
        Serial.println(classIdxToName(predict(features)));
        delay(1000);
    }

    delay(10);
}