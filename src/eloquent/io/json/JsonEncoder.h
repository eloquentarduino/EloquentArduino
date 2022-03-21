//
// Created by Simone on 17/03/2022.
//

#pragma once


namespace Eloquent {
    namespace IO {
        namespace Json {
            
            /**
             * Encode data to JSON to the given stream
             * 
             * @tparam Stream 
             */
            template<class Stream>
            class JsonEncoder {
            public:
                
                /**
                 * 
                 * @param stream 
                 */
                JsonEncoder(Stream &stream) : _stream(&stream) {
                    
                }

                /**
                 * Print object opening
                 */
                void openObject() {
                    print('{');
                }

                /**
                 * Print object closing
                 *
                 * @param addNewLine
                 */
                void closeObject(bool addNewLine = true) {
                    print('}');

                    if (addNewLine)
                        print('\n');
                }

                /**
                 * Print attributes separator
                 */
                void then() {
                    print(',');
                }

                /**
                 * Encode float
                 * 
                 * @param key 
                 * @param value 
                 * @param precision 
                 */
                void encode(const char *key, float value, uint8_t precision = 3) {
                    encode_key(key);
                    print(value, precision);
                }

                /**
                 * Encode int
                 * 
                 * @param key 
                 * @param value 
                 */
                void encode(const char *key, int value) {
                    encode_key(key);
                    print(value);
                }

                /**
                 * Encode string
                 * 
                 * @param key 
                 * @param value 
                 */
                void encode(const char *key, String value) {
                    encode_key(key);
                    quote(value);
                }

                /**
                 *
                 * @tparam T
                 * @param key
                 * @param array
                 * @param length
                 */
                template<typename T>
                void encode(const char *key, T *array, uint16_t length) {
                    encode_key(key);
                    print('[');

                    for (uint16_t i = 0; i < length - 1; i++) {
                        print(array[i]);
                        print(',');
                    }

                    print(array[length - 1]);
                    print(']');
                }

                /**
                 *
                 * @tparam T
                 * @param key
                 * @param array
                 * @param length
                 * @param precision
                 */
                template<typename T>
                void encode(const char *key, T *array, uint16_t length, uint8_t precision) {
                    encode_key(key);
                    print('[');

                    for (uint16_t i = 0; i < length - 1; i++) {
                        print(array[i], precision);
                        print(',');
                    }

                    print(array[length - 1], precision);
                    print(']');
                }

            protected:
                Stream *_stream;

                /**
                 * Print to stream
                 * 
                 * @tparam T 
                 * @param value 
                 */
                template<typename T>
                void print(T value) {
                    _stream->print(value);
                }

                /**
                 * Print to stream with given precision
                 *
                 * @tparam T
                 * @param value
                 */
                template<typename T>
                void print(T value, uint8_t precision) {
                    _stream->print(value, precision);
                }
                
                /**
                 * Encode key
                 * 
                 * @param key 
                 */
                void encode_key(const char *key) {
                    quote(key);
                    print(':');
                }

                /**
                 * Quote value
                 * 
                 * @tparam T 
                 * @param value 
                 */
                template<typename T>
                void quote(T value) {
                    print('"');
                    print(value);
                    print('"');
                }

                /**
                 * Quote string
                 * 
                 * @param value 
                 */
                void quote(String value) {
                    value.replace("\"", "\\\"");

                    print('"');
                    print(value);
                    print('"');
                }
            };
        }
    }
}