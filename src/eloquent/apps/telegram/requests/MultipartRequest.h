//
// Created by Simone on 12/04/2022.
//

#pragma once

#define TELEGRAM_HOST "api.telegram.com"


namespace Eloquent {
    namespace Apps {
        namespace Telegram {
            namespace Requests {
                /**
                 * Send multipart request
                 * @tparam Client
                 */
                template<class Client>
                class MultipartRequest {
                public:
                    /**
                     *
                     * @param client
                     */
                    MultipartRequest(Client *client, const char *token) :
                        _client(client),
                        _token(token),
                        _isClosed(false),
                        _isSent(false) {

                    }
                    
                    /**
                     * Start request
                     */
                    void open(String command) {
                        _client->print(F("POST /"));
                        _client->print(F("bot"));
                        _client->print(_token);
                        _client->print(F("/"));
                        _client->print(command);
                        _client->println(F(" HTTP/1.1"));

                        _client->println(F("Host: " TELEGRAM_HOST)); // bugfix - https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot/issues/186
                        _client->println(F("User-Agent: arduino/1.0"));
                        _client->println(F("Accept: */*"));
                    }

                    /**
                     *
                     * @param contentLength
                     */
                    void setContentLength(uint32_t contentLength) {
                        _client->print(F("Content-Length: "));
                        _client->println(String(contentLength));
                        _client->print(F("Content-Type: multipart/form-data; boundary="));
                        _client->println(F("------------------------b8f610217e83e29b"));
                        _client->println();
                    }

                    /**
                     *
                     * @tparam InputStream
                     * @param stream
                     */
                    template<class InputStream>
                    void setContentLength(InputStream &stream) {
                        setContentLength(stream.size());
                    }

                    /**
                     *
                     * @param chatId
                     */
                    void setChatId(String chatId) {
                        _client->print(F("--"));
                        _client->print(F("------------------------b8f610217e83e29b"));
                        _client->print(F("\r\ncontent-disposition: form-data; name=\"chat_id\"\r\n\r\n"));
                        _client->print(chatId);
                        _client->print(F("\r\n" "--"));
                        _client->print(F("------------------------b8f610217e83e29b"));
                    }

                    /**
                     *
                     * @param name
                     */
                    void setBinaryPropertyName(String name) {
                        _client->print(F("\r\ncontent-disposition: form-data; name=\""));
                        _client->print(name);
                    }

                    /**
                     *
                     * @param filename
                     */
                    void setFilename(String filename) {
                        _client->print(F("\"; filename=\""));
                        _client->print(filename);
                    }

                    /**
                     *
                     * @param contentType
                     */
                    void setContentType(String contentType) {
                        _client->print(F("\"\r\n" "Content-Type: "));
                        _client->print(contentType);
                        _client->print(F("\r\n" "\r\n"));
                    }

                    /**
                     *
                     */
                    void startBody() {

                    }

                    /**
                     *
                     * @tparam InputStream
                     * @param stream
                     */
                    template<class InputStream>
                    void pipe(InputStream *stream) {
                        while (stream->available())
                            _client->write(stream->read());
                    }

                    /**
                     *
                     */
                    void close() {
                        _client->print(F("\r\n" "--"));
                        _client->print(F("------------------------b8f610217e83e29b"));
                        _client->print(F("--" "\r\n"));

                        _isClosed = true;
                    }

                    /**
                     *
                     */
                    void send() {
                        _isSent = true;
                    }

                    /**
                     *
                     * @return
                     */
                    bool isOk() {
                        if (!_isClosed)
                            close();

                        if (_isSent)
                            send();

                        while (_client->available())
                            Serial.print(_client->read());

                        return false;
                    }


                protected:
                    Client *_client;
                    const char *_token;
                    bool _isSent;
                    bool _isClosed;
                };
            }
        }
    }
}
