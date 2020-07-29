#define CAMERA_MODEL_M5STACK_WIDE

#include <esp_camera.h>
#include "camera_pins.h"
//#include "color_image_model.h"

#define FRAME_SIZE FRAMESIZE_QQVGA
#define WIDTH 160
#define HEIGHT 120
#define BLOCK_SIZE 20
#define W (WIDTH / BLOCK_SIZE)
#define H (HEIGHT / BLOCK_SIZE)


uint16_t prev_frame[H][W] = { 0 };
uint16_t current_frame[H][W] = { 0 };
uint16_t rgb_frame[H][W][3] = { 0 };
double features[H*W*3] = { 0 };


bool setup_camera(framesize_t);
bool capture_still();
void convert_to_rbg(uint8_t*, size_t);
void linearize_features();
void print_features();
void classify();


/**
 *
 */
void setup() {
    Serial.begin(115200);
    Serial.println(setup_camera(FRAME_SIZE) ? "OK" : "ERR INIT");
}

/**
 *
 */
void loop() {
    if (!capture_still()) {
        Serial.println("Failed capture");
        delay(2000);

        return;
    }

    linearize_features();
    print_features();
    //classify();
    delay(3000);
}


/**
 *
 */
bool setup_camera(framesize_t frameSize) {
    camera_config_t config;

    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_RGB565;
    config.frame_size = frameSize;
    config.jpeg_quality = 12;
    config.fb_count = 1;

    bool ok = esp_camera_init(&config) == ESP_OK;

    sensor_t *sensor = esp_camera_sensor_get();
    sensor->set_framesize(sensor, frameSize);

    return ok;
}


/**
 * Convert RGB565 to RGB888
 */
void convert_to_rgb(uint8_t *buf, size_t len) {
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            rgb_frame[y][x][0] = 0;
            rgb_frame[y][x][1] = 0;
            rgb_frame[y][x][2] = 0;
        }
    }

    for (size_t i = 0; i < len; i += 2) {
//        uint16_t pix = *(uint16_t*) buf[i];
//        pix = __builtin_bswap16(pix);
        const uint8_t high = buf[i];
        const uint8_t low  = buf[i+1];
        const uint16_t pixel = (high << 8) | low;

        const uint8_t r = (pixel & 0b1111100000000000) >> 11;
        const uint8_t g = (pixel & 0b0000011111100000) >> 6;
        const uint8_t b = (pixel & 0b0000000000011111);

        const size_t j = i / 2;
        const uint16_t x = j % WIDTH;
        const uint16_t y = floor(j / WIDTH);
        const uint8_t block_x = floor(x / BLOCK_SIZE);
        const uint8_t block_y = floor(y / BLOCK_SIZE);

        // average pixels in block (accumulate)
        rgb_frame[block_y][block_x][0] += r;
        rgb_frame[block_y][block_x][1] += g;
        rgb_frame[block_y][block_x][2] += b;
    }
}

/**
 * Capture image and do down-sampling
 */
bool capture_still() {
    camera_fb_t *frame = esp_camera_fb_get();

    if (!frame)
        return false;

    convert_to_rgb(frame->buf, frame->len);

    return true;
}


/**
 * Convert image to features vector
 */
void linearize_features() {
    size_t i = 0;

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            features[i++] = rgb_frame[y][x][0];
            features[i++] = rgb_frame[y][x][1];
            features[i++] = rgb_frame[y][x][2];
        }
    }
}


/**
 *
 */
void print_features() {
    for (size_t i = 0; i < H*W*3; i++) {
        Serial.print(features[i]);
        Serial.print('\t');
    }
}

/**
 * Run the inference
 */
void classify() {
    Serial.print("Object: ");
    //Serial.println(classIdxToName(predict(features)));
}