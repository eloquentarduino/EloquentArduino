//
// Created by Simone on 15/04/2022.
//

#pragma once


namespace Eloquent {
    namespace TinyML {
        namespace EdgeImpulse {
            /**
             * Eloquent interface to the EdgeImpulse library
             */
            class Impulse {
            public:

                /**
                 *
                 * @param features
                 * @return
                 */
                uint8_t predict(float *features) {
                    return 0;
                }

                String predictLabel(float *features) {
                    predict(features);

                    return getLabel();
                }

                String getLabel() {
                    return "";
                }

            protected:
            };
        }
    }
}