//
// Created by Simone on 11/04/2022.
//

#pragma once

#ifndef NO_TELEGRAM

#include <WiFiClientSecure.h>
#include "../../../macros.h"
#include "./BaseTelegramBot.h"
#include "./witnessmenow/TelegramCertificate.h"

static WiFiClientSecure _telegramBotWifiSecureClient;


namespace Eloquent {
    namespace Apps {
        namespace Telegram {

            /**
             *
             */
            class WiFiTelegramBot : public BaseTelegramBot {
            public:

                /**
                 * Constructor
                 * @param token
                 */
                WiFiTelegramBot(const char *token) :
                    BaseTelegramBot(&_telegramBotWifiSecureClient, token) {

                }

                /**
                 *
                 * @return
                 */
                bool begin() override {
                    _telegramBotWifiSecureClient.setCACert(TELEGRAM_CERTIFICATE_ROOT);

                    return true;
                }
            };
        }
    }
}

#ifdef TELEGRAM_TOKEN
ELOQUENT_SINGLETON(Eloquent::Apps::Telegram::WiFiTelegramBot telegramBot(TELEGRAM_TOKEN));
#endif

#endif