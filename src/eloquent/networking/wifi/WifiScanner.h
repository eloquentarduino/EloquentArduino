#pragma once


namespace Eloquent {
    namespace Networking {
        namespace Wifi {
            /**
             * Abstract implementation of WiFi scanner
             */
            class WifiScanner {
            public:

                /**
                 * Perform scan
                 */
                void scan() {
                    i = 0;
                    numNetworks = WiFi.scanNetworks();
                }

                /**
                 * Reset iterator
                 */
                void reset() {
                    i = 0;
                }

                /**
                 * Test if we can iterate over the networks
                 * @return
                 */
                bool hasNext() {
                    return i < numNetworks;
                }

                /**
                 * Advance iterator
                 */
                void next() {
                    i += 1;
                }

                /**
                 * Get SID of current network
                 * @return
                 */
                String ssid() {
                    if (hasNext())
                        return ssidAt(i);

                    return "";
                }

                /**
                 * Get SSID of given network
                 * @param i
                 * @return
                 */
                String ssidAt(uint8_t i) {
                    return WiFi.SSID(i);
                }

                /**
                 * Get RSSI of current network
                 * @return
                 */
                int rssi() {
                    if (hasNext())
                        return rssiAt(i);

                    return 0;
                }

                /**
                 * Get RSSI of given network
                 * @param i
                 * @return
                 */
                int rssiAt(uint8_t i) {
                    return WiFi.RSSI(i);
                }

                /**
                 * Print scan results as JSON
                 * @tparam Stream
                 * @param stream
                 */
                template<typename Stream>
                void printAsJson(Stream& stream) {
                    stream.print('{');

                    for (uint8_t i = 0; i < numNetworks; i++) {
                        stream.print('"');
                        stream.print(ssidAt(i));
                        stream.print('"');
                        stream.print(':');
                        stream.print(rssiAt(i));

                        if (i < numNetworks - 1)
                            stream.print(',');
                    }

                    stream.print('}');
                    stream.print('\n');
                }

            protected:
                uint8_t i = 0;
                uint8_t numNetworks;
            };
        }
    }
}

static Eloquent::Networking::Wifi::WifiScanner wifiScanner;