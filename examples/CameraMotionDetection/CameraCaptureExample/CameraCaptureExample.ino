/**
 * Camera capture example
 */

#include "eloquent.h"

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


void setup() {
    delay(4000);
    Serial.begin(115200);

    // turn on high frequency capturing
    // in the case of OV767x camera, highFreq = 5 fps instead of 1 fps
    // in the case of Esp32 camera, highFreq clock = 20 MHz instead of 10 MHz
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
}

void loop() {
    if (!camera.capture()) {
        Serial.println(camera.getErrorMessage());
        delay(1000);
        return;
    }

    // resize for faster transmission over Serial port
    camera.image.resize<40, 30>();
    camera.image.printAsJsonTo(Serial);
}