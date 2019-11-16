#pragma once

#include "Transformer.h"

namespace Eloquent {
    namespace InputStream {

        /**
         * Round, ceil, floor
         */
        enum class RoundStrategy { ROUND, FLOOR, CEIL};

        /**
         * Round, ceil, floor a value
         */
        class Round : public Transformer {
        public:
            Round(RoundStrategy strategy = RoundStrategy::ROUND) :
                    _strategy(strategy) {

            }

        protected:
            RoundStrategy _strategy;

            /**
             *
             * @param value
             * @return
             */
            virtual float transform(float value) override {
                switch (_strategy) {
                    case RoundStrategy::CEIL:
                        return ceil(value);
                    case RoundStrategy::FLOOR:
                        return floor(value);
                    default:
                        return round(value);
                }
            }
        };
    }
}