/**
 * Camera motion detection + JPEG capture demo
 */

#include "eloquent.h"
#include "eloquent/vision/image/gray/custom.h"
#include "eloquent/vision/motion/naive.h"
#include "eloquent/fs/spiffs.h"


// uncomment based on your camera and resolution

//#include "eloquent/vision/camera/ov767x/gray/vga.h"
//#include "eloquent/vision/camera/ov767x/gray/qvga.h"
//#include "eloquent/vision/camera/ov767x/gray/qqvga.h"
//#include "eloquent/vision/camera/esp32/aithinker/gray/vga.h"
//#include "eloquent/vision/camera/esp32/aithinker/gray/qvga.h"
//#include "eloquent/vision/camera/esp32/aithinker/gray/qqvga.h"
//#include "eloquent/vision/camera/esp32/wrover/gray/vga.h"
//#include "eloquent/vision/camera/esp32/wrover/gray/qvga.h"
//#include "eloquent/vision/camera/esp32/wrover/gray/qqvga.h"
//#include "eloquent/vision/camera/esp32/eye/gray/vga.h"
//#include "eloquent/vision/camera/esp32/eye/gray/qvga.h"
//#include "eloquent/vision/camera/esp32/eye/gray/qqvga.h"
//#include "eloquent/vision/camera/esp32/m5/gray/vga.h"
//#include "eloquent/vision/camera/esp32/m5/gray/qvga.h"
//#include "eloquent/vision/camera/esp32/m5/gray/qqvga.h"
//#include "eloquent/vision/camera/esp32/m5wide/gray/vga.h"
//#include "eloquent/vision/camera/esp32/m5wide/gray/qvga.h"
//#include "eloquent/vision/camera/esp32/m5wide/gray/qqvga.h"


#define THUMB_WIDTH 32
#define THUMB_HEIGHT 24

// allocate memory to store the thumbnail into a new image
Eloquent::Vision::Image::Gray::CustomWithBuffer<THUMB_WIDTH, THUMB_HEIGHT> thumbnail;
Eloquent::Vision::Motion::Naive<THUMB_WIDTH, THUMB_HEIGHT> detector;


void setup() {
    delay(4000);
    Serial.begin(115200);
    filesystem.begin(true);

    // turn on high freq for fast streaming speed
    camera.setHighFreq();

    if (!camera.begin()) {
        while (true)  {
            Serial.println(camera.getErrorMessage());
            delay(1000);
        }
    }
    else {
        Serial.println("Camera init OK");
    }

    detector.throttle(10);
    detector.setIntensityChangeThreshold(15);
    detector.setPixelChangesThreshold(0.1);
}


void loop() {
    if (!camera.capture()) {
        Serial.println(camera.getErrorMessage());
        delay(1000);
        return;
    }

    // perform motion detection on resized image for fast detection
    // but keep original image for capture at full resolution
    camera.image.resizeTo<THUMB_WIDTH, THUMB_HEIGHT>(thumbnail);
    detector.update(thumbnail);

    // if motion is detected, save original image as jpeg
    if (detector.isMotionDetected()) {
        auto file = filesystem.writeBinary("/capture_best.jpg");
        auto jpeg = camera.image.jpeg().bestQuality();

        if (jpeg.writeTo(file)) {
            Serial.print("Best quality jpeg file size in bytes: ");
            Serial.print(file.size());
            Serial.print(". It took ");
            Serial.print(jpeg.getElapsedTime());
            Serial.println(" micros to encode");
        }
        else {
            Serial.print("Jpeg error: ");
            Serial.println(jpeg.getErrorMessage());
        }
    }

    // release memory
    camera.free();
}