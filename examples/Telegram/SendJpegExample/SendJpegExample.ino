#define TELEGRAM_TOKEN "xxxxxxxxxx:yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy"
#define CHAT_ID "0123456789"
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"

#include <WiFi.h>
#include <eloquent.h>
#include <eloquent/fs/spiffs.h>
#include <eloquent/networking/wifi.h>
#include <eloquent/apps/telegram/bot/wifi.h>


void setup() {
    Serial.begin(115200);
    filesystem.begin(true);
    delay(2000);

    // list files on filesystem
    filesystem.listTo(Serial);
    wifi.connectTo(WIFI_SSID, WIFI_PASSWORD);

    Serial.println("Connected to WiFi. Attempting to connect to Telegram API...");

    if (!telegramBot.connect()) {
        eloquent::abort(Serial, "Cannot connect to Telegram API");
    }

    Serial.println("Connected!");
    Serial.println("Type a jpeg filename to send to Telegram Bot");
}

void loop() {
    if (Serial.available()) {
        String filename = Serial.readStringUntil('\n');

        Serial.print("Sending file: ");
        Serial.println(filename);

        auto jpeg = filesystem.readBinary(filename);
        bool jpegStatus = telegramBot.sendJpegTo(CHAT_ID, jpeg);

        Serial.println(jpegStatus ? "Jpeg sent" : "Jpeg error");
    }
}