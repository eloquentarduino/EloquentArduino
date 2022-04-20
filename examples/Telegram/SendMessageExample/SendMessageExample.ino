#define TELEGRAM_TOKEN "xxxxxxxxxx:yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy"
#define CHAT_ID "0123456789"
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"

#include <WiFi.h>
#include <eloquent.h>
#include <eloquent/networking/wifi.h>
#include <eloquent/apps/telegram/bot/wifi.h>


void setup() {
    Serial.begin(115200);
    delay(2000);

    wifi.connectTo(WIFI_SSID, WIFI_PASSWORD);
    Serial.println("Connected to WiFi. Attempting to connect to Telegram API...");

    if (!telegramBot.connect()) {
        eloquent::abort(Serial, "Cannot connect to Telegram API");
    }

    Serial.println("Connected!");
    Serial.println("Type a message to send to Telegram Bot");
}

void loop() {
    if (Serial.available()) {
        String message = Serial.readStringUntil('\n');

        Serial.print("Sending message: ");
        Serial.println(message);

        bool messageStatus = telegramBot.sendMessageTo(CHAT_ID, message);

        Serial.println(messageStatus ? "Message sent" : "Message error");
    }
}