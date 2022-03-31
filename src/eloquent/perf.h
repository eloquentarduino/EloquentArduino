//
// Created by Simone on 23/03/2022.
//

#pragma once


/**
 * An ugly hack to override the micros function
 * @shame
 * @return
 */
uint32_t _________micros() {
    return micros();
}


namespace eloquent {
    namespace perf {

        template<typename Function>
        uint32_t micros(Function function) {
            uint32_t start = _________micros();

            function();

            return _________micros() - start;
        }
    }
}
