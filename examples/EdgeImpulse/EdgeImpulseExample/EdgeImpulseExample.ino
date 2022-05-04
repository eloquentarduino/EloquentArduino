/**
 * This example shows how to use the Eloquent library
 * to perform inference using the EdgeImpulse generated library
 */
#include <replace_with_edge_impulse_inferencing.h>
#include <eloquent.h>
#include <eloquent/tinyml/edgeimpulse.h>


Eloquent::TinyML::EdgeImpulse::Impulse impulse;


void setup() {
    Serial.begin(115200);
    delay(3000);
    Serial.println("Starting EdgeImpulse inference");
    Serial.println("Paste your feature vector in the Serial Monitor and get the predicted value");
    Serial.print("(expecting ");
    Serial.print(EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE);
    Serial.println(" comma-separated features)");
}


void loop() {
    float features[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE] = {0};

    if (!Serial.available())
        return;

    for (int i = 0; i < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; i++)
        features[i] = Serial.readStringUntil(',').toFloat();

    Serial.print("Predicted class: ");
    Serial.println(impulse.predict(features));
    Serial.print("Predicted label: ");
    Serial.println(impulse.getLabel());

    // debug class probabilities and timing
    impulse.printTo(Serial);
}