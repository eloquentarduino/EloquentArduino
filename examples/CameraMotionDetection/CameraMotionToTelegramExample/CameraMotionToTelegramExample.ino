/**
 * Camera motion detection + JPEG capture + Telegram Bot demo
 */

// this is required to include the TelegramBot class
#define ELOQUENT_TELEGRAM

// replace with your own values
#define TELEGRAM_TOKEN "xxxxxxxxxx:yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy"
#define CHAT_ID "0123456789"
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"

#include <WiFi.h>
#include <eloquent.h>
#include <eloquent/vision/image/gray/custom.h>
#include <eloquent/vision/motion/naive.h>
#include <eloquent/fs/spiffs.h>
#include <eloquent/networking/wifi.h>
#include <eloquent/apps/telegram/bot/wifi.h>


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

    if (!camera.begin())
        eloquent::abort(Serial, "Camera init error");

    if (!wifi.connectTo(WIFI_SSID, WIFI_PASSWORD))
        eloquent::abort(Serial, "Cannot connect to WiFi");

    if (!telegramBot.connect()) {
        eloquent::abort(Serial, "Cannot connect to Telegram API");
    }

    Serial.println("Camera init OK");
    Serial.println("WiFi connected OK");
    Serial.println("Telegram API connected OK");

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
        Serial.println("Motion detected");

        auto file = filesystem.writeBinary("/capture_best.jpg");
        auto jpeg = camera.image.jpeg().bestQuality();

        if (jpeg.writeTo(file)) {
            Serial.println("Jpeg written");

            // send to Telegram
            file.reopenAs("rb");

            bool messageOk = telegramBot.sendMessageTo(CHAT_ID, "Motion detected");
            Serial.println(messageOk ? "Message sent OK" : "Message send error");

            bool jpegOk = telegramBot.sendJpegTo(CHAT_ID, file);
            Serial.println(jpegOk ? "Jpeg sent OK" : "Jpeg send error");

            if (!jpegOk) {
                Serial.print("Telegram error: ");
                Serial.println(telegramBot.getErrorMessage());
            }
        }
        else {
            Serial.print("Jpeg encoding error: ");
            Serial.println(jpeg.getErrorMessage());
        }
    }

    // release memory
    camera.free();
}