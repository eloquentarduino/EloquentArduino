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
                 * Identify networks by SSID
                 */
                void identifyBySSID() {
                    useMac = false;
                }

                /**
                 * Identify networks by MAC address
                 */
                void identifyByMAC() {
                    useMac = true;
                }

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
                 * Get SSID of current network
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
                virtual String ssidAt(uint8_t i) {
                    return WiFi.SSID(i);
                }

                /**
                 * Get MAC address of current network
                 * @return
                 */
                String mac() {
                    if (hasNext())
                        return macAt(i);

                    return "";
                }

                /**
                 * Get Mac address of given network
                 * @param i
                 * @return
                 */
                virtual String macAt(uint8_t i) {
                    uint8_t *bssid = WiFi.BSSID(i);

                    return  this->hex(bssid[0]) + ":" +
                            this->hex(bssid[1]) + ":" +
                            this->hex(bssid[2]) + ":" +
                            this->hex(bssid[3]) + ":" +
                            this->hex(bssid[4]) + ":" +
                            this->hex(bssid[5]) + ":" +
                            this->hex(bssid[6]);
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
                virtual int rssiAt(uint8_t i) {
                    return WiFi.RSSI(i);
                }

                /**
                 * Get identifier of current network
                 * @return
                 */
                virtual String id() {
                    return idAt(i);
                }

                /**
                 * Get identifier of given network
                 * @param i
                 * @return
                 */
                virtual String idAt(uint8_t i) {
                    return useMac ? macAt(i) : ssidAt(i);
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
                        stream.print(idAt(i));
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
                bool useMac = false;

                /**
                 * Convert byte to hex string
                 * @param byte
                 * @return
                 */
                String hex(uint8_t byte) {
                    String alphabet = "0123456789ABCDEF";
                    char hex[3] = {
                        alphabet.charAt(byte >> 4),
                        alphabet.charAt(byte & 0b1111),
                        '\0'
                    };

                    return String(hex);
                }
            };
        }
    }
}

static Eloquent::Networking::Wifi::WifiScanner wifiScanner;