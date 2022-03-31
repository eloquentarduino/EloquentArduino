#pragma once

#include "Transformer.h"

namespace Eloquent {
    namespace InputStream {

        /**
         * Map a value from one range to another
         */
        class Map : public Transformer {
        public:
            Map(float fromMin, float fromMax, float toMin, float toMax, bool constrain = false) :
                    _fromMin(fromMin),
                    _fromMax(fromMax),
                    _toMin(toMin),
                    _toMax(toMax),
                    _constrain(constrain) {

            }

        protected:
            bool _constrain;
            float _fromMin;
            float _fromMax;
            float _toMin;
            float _toMax;

            /**
             *
             * @param value
             */
            virtual float transform(float value) override {
                if (_constrain)
                    value = constrain(value, _fromMin, _fromMax);
                
                return map(value, _fromMin, _fromMax, _toMin, _toMax);
            }
        };
    }
}