#define CAMERA_MODEL_M5STACK_WIDE

#include <FS.h>
#include <SPIFFS.h>
#include <eloquentarduino.h>
#include <eloquentarduino/io/serial_print.h>
#include <eloquentarduino/vision/camera/ESP32Camera.h>
#include <eloquentarduino/vision/io/writers/JpegWriter.h>

#define FRAME_SIZE FRAMESIZE_QVGA
#define PIXFORMAT PIXFORMAT_RGB565
#define W 320
#define H 240
#define w 32
#define h 24
#define DIFF_THRESHOLD 15
#define MOTION_THRESHOLD 0.15

// delete the second definition if you want to turn on code benchmarking
#define timeit(label, code) { uint32_t start = millis(); code; uint32_t duration = millis() - start; eloquent::io::print_all("It took ", duration, " millis for ", label); }
#define timeit(label, code) code;

using namespace Eloquent::Vision;

camera_fb_t *frame;
Camera::ESP32Camera camera(PIXFORMAT);
//IO::Decoders::GrayscaleRandomAccessDecoder decoder;
IO::Decoders::Red565RandomAccessDecoder decoder;
Processing::Downscaling::Center<W / w, H / h> strategy;
Processing::Downscaling::Downscaler<W, H, w, h> downscaler(&decoder, &strategy);
Processing::MotionDetector<w, h> motion;
IO::Writers::JpegWriter<W, H> jpegWriter;


void capture();
void save();
void stream();


void setup() {
    Serial.begin(115200);
    SPIFFS.begin(true);
    delay(1000);
    Serial.println("Begin");

    camera.begin(FRAME_SIZE);
    // set how much a pixel value should differ to be considered as a change
    motion.setDiffThreshold(DIFF_THRESHOLD);
    // set how many pixels (in percent) should change to be considered as motion
    motion.setMotionThreshold(MOTION_THRESHOLD);
    // prevent consecutive triggers
    motion.setDebounceFrames(5);
}


void loop() {
    capture();
    eloquent::io::print_all(motion.changes(), " pixels changed");

    if (motion.triggered()) {
        Serial.println("Motion detected");

        // uncomment to save to disk
        // save();

        // uncomment to stream to the Python script for visualization
        //stream();

        delay(1000);
    }

    delay(30);
}


void capture() {
    uint32_t start = millis();
    uint8_t downscaled[w * h];

    timeit("capture frame", frame = camera.capture());

    // scale image from size H * W to size h * w
    timeit("downscale", downscaler.downscale(frame->buf, downscaled));

    // detect motion on the downscaled image
    timeit("motion detection", motion.detect(downscaled));

    //eloquent::io::print_all(1000 / (millis() - start), " FPS");
}


void save() {
    File imageFile = SPIFFS.open("/capture.jpg", "wb");
    uint8_t quality = 30;

    eloquent::io::print_all("The image will be saved as /capture.jpg");
    jpegWriter.write(imageFile, frame->buf, PIXFORMAT, quality);
    imageFile.close();
    eloquent::io::print_all("Saved");
}


void stream() {
    eloquent::io::print_all("START OF FRAME");

    jpegWriter.write(Serial, frame->buf, PIXFORMAT, 30);

    eloquent::io::print_all("END OF FRAME");
}