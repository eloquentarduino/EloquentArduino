void printFeatures();


void setup() {
    Serial.begin(115200);
    pinMode(IN, INPUT_PULLUP);
}

void loop() {
    if (digitalRead(IN) == 0) {
        recordButtonStatus();
        printFeatures();
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