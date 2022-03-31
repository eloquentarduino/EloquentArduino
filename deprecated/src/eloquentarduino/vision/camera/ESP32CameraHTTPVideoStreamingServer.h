#pragma once

#include <esp_http_server.h>


namespace Eloquent {
    namespace Vision {
        namespace Camera {

            class HTTPVideoStreamingServer {
            public:

                /**
                 *
                 * @param port
                 */
                HTTPVideoStreamingServer(uint16_t port = 81) :
                _isPlaying(false) {
                    _config = HTTPD_DEFAULT_CONFIG();
                    _config.server_port = port;
                }

                /**
                *
                * @return
                */
                bool start() {
                    if (_isPlaying)
                        return true;

                    if (httpd_start(&_httpd, &_config) != ESP_OK)
                        return false;

                    _isPlaying = true;

                    httpd_uri_t stream_uri = {
                        .uri       = "/",
                        .method    = HTTP_GET,
                        .handler   = [](httpd_req_t *req) {
                            esp_err_t res = ESP_OK;
                            char *part[64];

                            if (httpd_resp_set_type(req, "multipart/x-mixed-replace;boundary=123456789000000000000987654321") != ESP_OK)
                                return ESP_FAIL;

                            httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");

                            while (true) {
                                size_t contentTypeHeaderLength;
                                camera_fb_t *fb = esp_camera_fb_get();

                                if (!fb)
                                    return ESP_FAIL;

                                contentTypeHeaderLength = snprintf((char *) part, 64,
                                                "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n", fb->len);

                                if (httpd_resp_send_chunk(req, (const char *) part, contentTypeHeaderLength) != ESP_OK)
                                    return ESP_FAIL;

                                if (httpd_resp_send_chunk(req, (const char *) fb->buf, fb->len) != ESP_OK) {
                                    esp_camera_fb_return(fb);

                                    return ESP_FAIL;
                                }

                                esp_camera_fb_return(fb);
                                res = httpd_resp_send_chunk(req, "\r\n--123456789000000000000987654321\r\n", 37);
                                fb = NULL;
                            }

                            return ESP_OK;
                        },
                        .user_ctx  = NULL
                    };

                    httpd_register_uri_handler(_httpd, &stream_uri);

                    return true;
                }

                /**
                 * Stop the webserver
                 */
                void stop() {
                    _isPlaying = false;
                    httpd_unregister_uri(_httpd, "/");
                    httpd_stop(_httpd);
                }

            protected:
                bool _isPlaying;
                httpd_config_t _config;
                httpd_handle_t _httpd;
            };
        }
    }
}