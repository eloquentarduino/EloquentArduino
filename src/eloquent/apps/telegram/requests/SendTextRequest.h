//
// Created by Simone on 12/04/2022.
//

#define TELEGRAM_HOST "api.telegram.org"


namespace Eloquent {
    namespace Apps {
        namespace Telegram {
            namespace Requests {

                /**
                 * 
                 * @tparam Client 
                 */
                template<typename Client>
                class SendTextRequest {
                public:

                    /**
                     * 
                     * @param client 
                     * @param token 
                     */
                    SendTextRequest(Client *client, const char *token) :
                    _client(client),
                    _token(token) {

                    }
                    
                    /**
                     * 
                     * @param chatId 
                     * @param text 
                     * @return 
                     */
                    bool sendTo(String chatId, String text) {
                        Request request(_client);
                        QueryString queryString(request);

                        Serial.println("Request start");
                        delay(1000);

                        request.print("GET bot", _token, "/sendMessage?");
                        request.then(queryString.encode("chat_id", chatId));
                        request.then(queryString.append("text", text));
                        request.then(queryString.append("parse_mode", ""));
                        request.http11();
                        request.host(TELEGRAM_HOST);
                        request.acceptJson();
                        request.noCache();
                        request.end();

                        _client->print(F("GET "));
                        _client->print(F("bot"));
                        _client->print(_token);
                        _client->print(F("/sendMessage?chat_id="));
                        _client->print(chatId);
                        _client->print(F("&text="));
                        _client->print(text);
                        _client->println(F("&parse_mode= HTTP/1.1"));
                        _client->println(F("Host:" TELEGRAM_HOST));
                        _client->println(F("Accept: application/json"));
                        _client->println(F("Cache-Control: no-cache"));
                        _client->println();

                        Serial.println("Request done");
                        delay(1000);

                        while (_client->available())
                            Serial.print(_client->read());

                        Serial.println("CLient DONE");
                    }

                protected:
                    const char *_token;
                    Client *_client;
                };
            }
        }
    }
}