//
// Created by Simone on 12/04/2022.
//

#pragma once
#include "./MultipartRequest.h"


namespace Eloquent {
    namespace Apps {
        namespace Telegram {
            namespace Requests {

                /**
                 * Send photo from an input stream (e.g file)
                 */
                template<typename Client, typename InputStream>
                class SendJpegRequest {
                public:

                    /**
                     *
                     * @param MIME
                     */
                    SendJpegRequest(Client *client, const char *token, InputStream *stream) :
                        _client(client),
                        _token(token),
                        _stream(stream) {

                    }

                    /**
                     *
                     * @param chatId
                     * @return
                     */
                    bool sendTo(const String &chatId) {
                        MultipartRequest<Client> request(_client, _token);

                        request.open("sendPhoto");
                        request.setContentLength(_stream->size());
                        request.setChatId(chatId);
                        request.setBinaryPropertyName("photo");
                        request.setFilename("img.jpg");
                        request.setContentType("image/jpeg");
                        request.startBody();
                        request.pipe(_stream);

                        return request.isOk();
                    }

                protected:
                    const char *_token;
                    Client *_client;
                    InputStream *_stream;
                };
            }
        }
    }
}