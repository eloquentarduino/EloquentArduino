#pragma once

#include "eKVStore.h"

namespace Eloquent {

    /**
     * Store key-value pairs in the EEPROM
     * Here the key is the address in the EEPROM
     * @tparam V
     */
    template<class V>
    class EEPROMKVStore : public KVStore<uint16_t, V*> {

    };
}