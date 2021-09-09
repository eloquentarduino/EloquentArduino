/**
 * Example on how to use the YUVHistogram class.
 * It computes the (binned) frequency histogram of Y, U, V values in an image.
 */
#define CAMERA_MODEL_M5STACK_WIDE
#define FRAME_SIZE FRAMESIZE_QVGA
#define NUM_BINS 32

#include <EloquentArduino.h>
#include <eloquentarduino/vision/camera/ESP32Camera.h>
#include <eloquentarduino/vision/processing/YUVHistogram.h>


Eloquent::Vision::Camera::ESP32Camera camera(PIXFORMAT_YUV422);
Eloquent::Vision::Processing::YUVHistogram<NUM_BINS> hist;


/**
 * Function prototype
 */
void printHistogram(uint16_t *hist, char bar = '|', uint8_t divisor = 10);


/**
 *
 */
void setup() {
    Serial.begin(115200);
    camera.begin(FRAME_SIZE);
    delay(4000);
}


/**
 *
 */
void loop() {
    camera_fb_t *frame = camera.capture();

    // actually compute histogram
    hist.update(frame->buf, frame->len);

    // YUVHistogram can tell if an image looks very dark or very bright
    Serial.println(hist.looksDark()   ? "Image looks dark"   : "Image doesn't look dark");
    Serial.println(hist.looksBright() ? "Image looks bright" : "Image doesn't look bright");


    // the hist object has the attributes yHistogram, uHistrogram, vHistogram
    // that contain the calculated histograms
    printHistogram(hist.yHistogram);
    delay(4000);
}


/**
 * Print histogram on the serial monitor
 */
void printHistogram(uint16_t *hist, char bar, uint8_t divisor) {
    // for each bin
    for (uint8_t i = 0; i < NUM_BINS; i++) {
        Serial.printf("%-2d ", i);

        // print row proportional to its height
        for (uint16_t j = hist[i] / divisor; j > 0; j--) {
            Serial.print(bar);
        }

        Serial.println();
    }
}