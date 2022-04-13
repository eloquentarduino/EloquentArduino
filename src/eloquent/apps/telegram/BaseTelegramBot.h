//
// Created by Simone on 11/04/2022.
//

#pragma once

#include "./requests/SendTextRequest.h"
#include "./requests/SendJpegRequest.h"

using Eloquent::Apps::Telegram::Requests::SendTextRequest;
using Eloquent::Apps::Telegram::Requests::SendJpegRequest;


namespace Eloquent {
    namespace Apps {
        namespace Telegram {

            /**
             * Client-independent Telegram bot
             * @tparam Client
             */
            template<class Client>
            class BaseTelegramBot {
            public:

                /**
                 * Constructor
                 * @param token
                 */
                BaseTelegramBot(Client *client, const char *token) :
                    _client(client),
                    _token(token),
                    _connected(false) {

                }

                /**
                 *
                 * @param timeout
                 * @return
                 */
                bool connect(uint16_t timeout = 10000) {
                    _client->connect("api.telegram.org", 443);

                    uint16_t start = millis();

                    while (millis() - start < timeout) {
                        if (_client->connected())
                            return (_connected = true);
                    }

                    return (_connected = false);
                }

                /**
                 *
                 * @param chatId
                 * @param message
                 * @return
                 */
                bool sendMessageTo(String chatId, String message) {
                    SendTextRequest<Client> request(_client, _token);

                    if (!_connected)
                        connect();

                    if (!_connected)
                        return false;

                    return request.sendTo(chatId, message);
                }

                /**
                 * Send Jpeg to chat
                 * @tparam InputStream
                 * @param chatId
                 * @param stream
                 * @return true on success
                 */
                template<class InputStream>
                bool sendJpegTo(String chatId, InputStream &stream) {
                    SendJpegRequest<Client, InputStream> request(_client, _token, &stream);

                    if (!_connected)
                        connect();

                    if (_connected)
                        return false;

                    return request.sendTo(chatId);
                }

            protected:
                bool _connected;
                Client *_client;
                const char *_token;
            };
        }
    }
}