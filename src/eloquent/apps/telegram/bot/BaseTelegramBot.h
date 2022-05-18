//
// Created by Simone on 11/04/2022.
//

#pragma once

#ifndef NO_TELEGRAM

#include "./witnessmenow/UniversalTelegramBot.h"
#include "./Errors.h"


namespace Eloquent {
    namespace Apps {
        namespace Telegram {

            /**
             * Client-independent Telegram bot
             * @tparam Client
             */
            //template<class Client>
            class BaseTelegramBot {
            public:

                /**
                 * Constructor
                 * @param token
                 */
                BaseTelegramBot(Client *client, const char *token) :
                    _bot(token, *client),
                    _client(client),
                    _error(TelegramBotError::OK),
                    _connected(false),
                    _beginOk(false) {

                }

                /**
                 * Test if everything is ok
                 * @return
                 */
                bool isOk() {
                    return _error == TelegramBotError::OK;
                }

                /**
                 *
                 * @return
                 */
                String getErrorMessage() {
                    if (isOk())
                        return "OK";

                    if (_error == TelegramBotError::INIT_ERROR)
                        return "INIT ERROR";

                    if (_error == TelegramBotError::CONNECTION_ERROR)
                        return "CONNECTION ERROR";

                    if (_error == TelegramBotError::REQUEST_ERROR)
                        return "REQUEST ERROR";

                    if (_error == TelegramBotError::EMPTY_PAYLOAD_ERROR)
                        return "EMPTY PAYLOAD ERROR";

                    return "UNKNOWN ERROR";
                }

                /**
                 * Allow concrete classes to perform custom initialization
                 * @return
                 */
                virtual bool begin() {
                    return true;
                }

                /**
                 * Connect client
                 * @param timeout
                 * @return
                 */
                bool connect(uint16_t timeout = 10000) {
                    if (!_beginOk && !begin())
                        return error(TelegramBotError::INIT_ERROR);

                    _connected = false;
                    _beginOk = true;
                    _client->connect("api.telegram.org", 443);

                    uint16_t start = millis();

                    while (millis() - start < timeout) {
                        if (_client->connected()) {
                            ok();
                            return (_connected = true);
                        }

                        delay(10);
                    }

                    return error(TelegramBotError::CONNECTION_ERROR);
                }

                /**
                 *
                 * @return
                 */
                bool inline isConnected() {
                    return _connected;
                }

                /**
                 *
                 * @param chatId
                 * @param message
                 * @return
                 */
                bool sendMessageTo(String chatId, String message) {
                    if (!isConnected())
                        connect();

                    if (!isConnected())
                        return error(TelegramBotError::CONNECTION_ERROR);

                    if (_bot.sendMessage(chatId, message, ""))
                        return ok();

                    return error(TelegramBotError::REQUEST_ERROR);
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
                    if (!isConnected())
                        connect();

                    if (!isConnected())
                        return error(TelegramBotError::CONNECTION_ERROR);

                    size_t size = stream.size();

                    if (size == 0)
                        return error(TelegramBotError::EMPTY_PAYLOAD_ERROR);

                    stream.open("rb");

                    String response = _bot.sendPhotoByBinary(
                        chatId,
                        "image/jpeg",
                        size,
                        [&]() { return stream.available(); },
                        [&]() { return stream.read(); }
                    );

                    if (response.indexOf("\"ok\":true") >= 0)
                        return ok();

                    return error(TelegramBotError::REQUEST_ERROR);
                }

            protected:
                UniversalTelegramBot _bot;
                Client *_client;
                TelegramBotError _error;
                bool _connected;
                bool _beginOk;


                /**
                 * Set error
                 * @param error
                 * @return
                 */
                bool error(TelegramBotError error) {
                    _error = error;

                    return false;
                }

                /**
                 * Mark as ok
                 * @return
                 */
                bool ok() {
                    _error = TelegramBotError::OK;

                    return true;
                }
            };
        }
    }
}

#endif