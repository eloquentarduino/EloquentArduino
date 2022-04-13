/**
 * Camera motion detection demo
 */

#include "eloquent.h"
#include "eloquent/vision/motion/naive.h"


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


Eloquent::Vision::Motion::Naive<THUMB_WIDTH, THUMB_HEIGHT> detector;


void setup() {
    delay(4000);
    Serial.begin(115200);

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

    // wait for at least 10 frames to be processed before starting to detect
    // motion (false triggers at start)
    // then, when motion is detected, don't trigger for the next 10 frames
    detector.startSinceFrameNumber(10);
    detector.debounceMotionTriggerEvery(10);

    // or, in one call
    detector.throttle(10);

    // trigger motion when at least 10% of pixels change intensity by
    // at least 15 out of 255
    detector.setPixelChangesThreshold(0.1);
    detector.setIntensityChangeThreshold(15);
}


void loop() {
    if (!camera.capture()) {
        Serial.println(camera.getErrorMessage());
        delay(1000);
        return;
    }

    // perform motion detection on resized image for fast detection
    camera.image.resize<THUMB_WIDTH, THUMB_HEIGHT>();
    camera.image.printAsJsonTo(Serial);
    detector.update(camera.image);

    // if motion is detected, print coordinates to serial in JSON format
    if (detector.isMotionDetected()) {
        detector.printAsJsonTo(Serial);
    }

    // release memory
    camera.free();
}