//
// Created by Simone on 12/04/2022.
//

#pragma once

#include <WiFi.h>
#include "../macros.h"


namespace Eloquent {
    namespace Networking {
        class WiFiHelper {
        public:

            /**
             *
             * @param ssid
             * @param password
             * @return
             */
            bool connectTo(const char *ssid, const char *password, uint16_t timeout = 10000) {
                WiFi.mode(WIFI_STA);
                WiFi.begin(ssid, password);

                uint16_t start = millis();

                while (millis() - start < timeout) {
                    if (WiFi.status() == WL_CONNECTED)
                        return true;
                }

                return false;
            }
        };
    }
}

ELOQUENT_SINGLETON(Eloquent::Networking::WiFiHelper wifi);