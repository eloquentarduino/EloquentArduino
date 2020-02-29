#include "EloquentAsciiArt.h"
#include "EloquentMLX90640.h"


using namespace Eloquent::Sensors;
using namespace Eloquent::ImageProcessing;

float buffer[768];
uint8_t bufferBytes[768];
MLX90640 camera;
// we need to specify width and height of the image
AsciiArt<32, 24> art(bufferBytes);


void setup() {
    Serial.begin(115200);
    delay(3000);

    if (!camera.begin()) {
        Serial.println("Init error");
        delay(50000);
    }
}


void loop() {
    camera.read(buffer);

    // convert float image to uint8
    for (size_t i = 0; i < 768; i++) {
        // assumes readings are in the range 0-40 degrees
        // change as per your need
        bufferBytes[i] = map(buffer[i], 0, 40, 0, 255);
    }

    // print to Serial with a border of 2 characters, to distinguish one image from the next
    art.print(&Serial, 2);
    delay(2000);
}