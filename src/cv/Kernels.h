#pragma once

namespace Eloquent {
    namespace CV {
        namespace Kernels {

            class Kernel {
            public:
                /**
                 * Apply kernel function to next pixel in ROI
                 * @param reduced
                 * @param pixel
                 * @return
                 */
                virtual uint16_t apply(uint16_t reduced, uint8_t pixel) = 0;

                /**
                 * Transform result of kernel
                 * @param reduced
                 * @return
                 */
                virtual uint8_t map(uint16_t reduced) {
                    return (uint8_t) reduced;
                }
            };

            /**
             * Apply max function as kernel
             */
            class KernelMax : public Kernel {
            public:
                uint16_t apply(uint16_t reduced, uint8_t pixel) {
                    return reduced > pixel ? reduced : pixel;
                }
            };
        }
    }
}