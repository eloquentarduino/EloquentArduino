#pragma once


namespace Eloquent {
    namespace DataStructures {

        /**
         * A key: value data structure
         * Not really an "hash" map, but works the same
         */
         template<typename K, typename V, uint8_t size>
        class HashMap {
        public:
            /**
             *
             */
            HashMap() :
                i(0) {

            }

            /**
             * Set key value
             * @param key
             * @param value
             */
            void put(K key, V value) {
                if (i >= size)
                    return;

                keys[i] = key;
                values[i] = value;
                i++;
            }

            /**
             * Get key's value
             * @param key
             * @return
             */
            V get(K key) {
                int16_t index = indexOf(key);

                return index >= 0 ? values[index] : 0;
            }

            /**
             * Check if key exists.
             * @param key
             * @return
             */
            bool exists(K key) {
                return indexOf(key) >= 0;
            }

            /**
             * Get keys buffer
             * @return
             */
            K* getKeys() {
                return this->keys;
            }

            /**
             * Get values buffer
             * @return
             */
            V* getValues() {
                return this->values;
            }

        protected:
            uint8_t i;
            K keys[size];
            V values[size];

            /**
             * Get index of key.
             * Returns -1 if not found.
             * @param key
             * @return
             */
            int16_t indexOf(K key) {
                for (uint8_t j = 0; j < i; j++)
                    if (keys[j] == key)
                        return j;

                return -1;
            }
        };
    }
}