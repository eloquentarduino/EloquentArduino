//
// Created by Simone on 11/04/2022.
//

#pragma once

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "../../macros.h"
#include "./BaseTelegramBot.h"


namespace Eloquent {
    namespace Apps {
        namespace Telegram {
            WiFiClientSecure _client;

            /**
             *
             */
            class WiFiTelegramBot : public BaseTelegramBot<WiFiClientSecure> {
            public:

                /**
                 * Constructor
                 * @param token
                 */
                WiFiTelegramBot(const char *token) :
                    BaseTelegramBot<WiFiClientSecure>(_client, token) {

                }
            };
        }
    }
}

#ifdef TELEGRAM_TOKEN
ELOQUENT_SINGLETON(Eloquent::Apps::Telegram::WiFiTelegramBot telegramBot(TELEGRAM_TOKEN));
#endif