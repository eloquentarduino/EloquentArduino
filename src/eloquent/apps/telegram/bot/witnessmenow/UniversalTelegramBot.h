/*
Copyright (c) 2018 Brian Lough. All right reserved.

UniversalTelegramBot - Library to create your own Telegram Bot using
ESP8266 or ESP32 on Arduino IDE.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef UniversalTelegramBot_h
#define UniversalTelegramBot_h

//#define TELEGRAM_DEBUG 1
#define ARDUINOJSON_DECODE_UNICODE 1
#define ARDUINOJSON_USE_LONG_LONG 1
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Client.h>
#include "./TelegramCertificate.h"

#define TELEGRAM_HOST "api.telegram.org"
#define TELEGRAM_SSL_PORT 443
#define HANDLE_MESSAGES 1

//unmark following line to enable debug mode
//#define _debug

//typedef bool (*MoreDataAvailable)();
//typedef byte (*GetNextByte)();
//typedef byte* (*GetNextBuffer)();
//typedef int (GetNextBufferLen)();

struct telegramMessage {
  String text;
  String chat_id;
  String chat_title;
  String from_id;
  String from_name;
  String date;
  String type;
  String file_caption;
  String file_path;
  String file_name;
  bool hasDocument;
  long file_size;
  float longitude;
  float latitude;
  int update_id;
  int message_id;  

  int reply_to_message_id;
  String reply_to_text;
  String query_id;
};

class UniversalTelegramBot {
public:
  UniversalTelegramBot(const String& token, Client &client);
  void updateToken(const String& token);
  String getToken();
  String sendGetToTelegram(const String& command);
  String sendPostToTelegram(const String& command, JsonObject payload);

  /**
   *
   * @tparam MoreDataAvailable
   * @tparam GetNextByte
   * @param command
   * @param binaryPropertyName
   * @param fileName
   * @param contentType
   * @param chat_id
   * @param fileSize
   * @param moreDataAvailableCallback
   * @param getNextByteCallback
   * @return
   */
  template<typename MoreDataAvailable, typename GetNextByte>
  String
  sendMultipartFormDataToTelegram(const String& command, const String& binaryPropertyName,
                                  const String& fileName, const String& contentType,
                                  const String& chat_id, int fileSize,
                                  MoreDataAvailable moreDataAvailableCallback,
                                  GetNextByte getNextByteCallback) {
      String body;
      String headers;

      const String boundary = F("------------------------b8f610217e83e29b");

      // Connect with api.telegram.org if not already connected
      if (!client->connected()) {
          if (!client->connect(TELEGRAM_HOST, TELEGRAM_SSL_PORT)) {
          }
      }
      if (client->connected()) {
          String start_request;
          String end_request;


          start_request += F("--");
          start_request += boundary;
          start_request += F("\r\ncontent-disposition: form-data; name=\"chat_id\"\r\n\r\n");
          start_request += chat_id;
          start_request += F("\r\n" "--");
          start_request += boundary;
          start_request += F("\r\ncontent-disposition: form-data; name=\"");
          start_request += binaryPropertyName;
          start_request += F("\"; filename=\"");
          start_request += fileName;
          start_request += F("\"\r\n" "Content-Type: ");
          start_request += contentType;
          start_request += F("\r\n" "\r\n");

          end_request += F("\r\n" "--");
          end_request += boundary;
          end_request += F("--" "\r\n");

          client->print(F("POST /"));
          client->print(buildCommand(command));
          client->println(F(" HTTP/1.1"));
          // Host header
          client->println(F("Host: " TELEGRAM_HOST)); // bugfix - https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot/issues/186
          client->println(F("User-Agent: arduino/1.0"));
          client->println(F("Accept: */*"));

          int contentLength = fileSize + start_request.length() + end_request.length();

          client->print(F("Content-Length: "));
          client->println(String(contentLength));
          client->print(F("Content-Type: multipart/form-data; boundary="));
          client->println(boundary);
          client->println();
          client->print(start_request);

          while (moreDataAvailableCallback()) {
              client->write(getNextByteCallback());
          }

          client->print(end_request);
          readHTTPAnswer(body, headers);
      }

      closeClient();
      return body;
  }

  bool readHTTPAnswer(String &body, String &headers);
  bool getMe();

  bool sendSimpleMessage(const String& chat_id, const String& text, const String& parse_mode);
  bool sendMessage(const String& chat_id, const String& text, const String& parse_mode = "", int message_id = 0);
  bool sendMessageWithReplyKeyboard(const String& chat_id, const String& text,
                                    const String& parse_mode, const String& keyboard,
                                    bool resize = false, bool oneTime = false,
                                    bool selective = false);
  bool sendMessageWithInlineKeyboard(const String& chat_id, const String& text,
                                     const String& parse_mode, const String& keyboard, int message_id = 0);

  bool sendChatAction(const String& chat_id, const String& text);

  bool sendPostMessage(JsonObject payload, bool edit = false); 
  String sendPostPhoto(JsonObject payload);

  /**
   *
   * @tparam MoreDataAvailable
   * @tparam GetNextByte
   * @param chat_id
   * @param contentType
   * @param fileSize
   * @param moreDataAvailableCallback
   * @param getNextByteCallback
   * @return
   */
  template<typename MoreDataAvailable, typename GetNextByte>
  String sendPhotoByBinary(const String& chat_id, const String& contentType, int fileSize,
                           MoreDataAvailable moreDataAvailableCallback,
                           GetNextByte getNextByteCallback) {
      return sendMultipartFormDataToTelegram(
              "sendPhoto",
              "photo",
              "img.jpg",
              contentType,
              chat_id,
              fileSize,
              moreDataAvailableCallback,
              getNextByteCallback);
  }


  String sendPhoto(const String& chat_id, const String& photo, const String& caption = "",
                   bool disable_notification = false,
                   int reply_to_message_id = 0, const String& keyboard = "");

  bool answerCallbackQuery(const String &query_id,
                           const String &text = "",
                           bool show_alert = false,
                           const String &url = "",
                           int cache_time = 0);

  bool setMyCommands(const String& commandArray);

  String buildCommand(const String& cmd);

  int getUpdates(long offset);
  bool checkForOkResponse(const String& response);
  telegramMessage messages[HANDLE_MESSAGES];
  long last_message_received;
  String name;
  String userName;
  int longPoll = 0;
  unsigned int waitForResponse = 1500;
  int _lastError;
  int last_sent_message_id = 0;
  int maxMessageLength = 1500;

private:
  // JsonObject * parseUpdates(String response);
  String _token;
  Client *client;
  void closeClient();
  bool getFile(String& file_path, long& file_size, const String& file_id);
  bool processResult(JsonObject result, int messageIndex);
};

#endif
