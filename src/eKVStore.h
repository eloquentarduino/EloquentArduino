#pragma once


namespace Eloquent {

    /**
     * Abstract interface for a storage capable of working
     * with key-value pairs
     * @tparam K
     * @tparam V
     */
    template<class K, class V>
    class KVStore {
    public:

        /**
         * Get value by key
         * @param key
         * @return
         */
        virtual V get(K key) = 0;

        /**
         * Set key value
         * @param key
         * @param val
         */
        virtual void set(K key, V val) = 0;

        /**
         * Delete key
         * @param key
         */
        virtual void remove(K key) = 0;
    };
}