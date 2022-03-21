//
// Created by Simone on 17/03/2022.
//

#pragma once

#include "./AbstractMotionDetector.h"
#include "../../io/json/JsonEncoder.h"


namespace Eloquent {
    namespace Vision {
        namespace Motion {
            /**
             * Stupid motion detector
             * Detect motion when a given number of pixels
             * change value by a given threshold
             *
             * @tparam width
             * @tparam height
             */
            template<uint16_t width, uint16_t height>
            class NaiveMotionDetector : public AbstractMotionDetector {
            public:

                /**
                 * Constructor
                 */
                NaiveMotionDetector() :
                    AbstractMotionDetector(),
                    _intensityThreshold(5),
                    _changesThreshold(width * height * 0.1),
                    _decay(1),
                    _numChanges(0) {

                }

                /**
                 * Set threshold to detect a pixel as changed
                 *
                 * @param threshold
                 */
                void setIntensityChangeThreshold(uint8_t threshold) {
                    _intensityThreshold = threshold;
                }

                /**
                 * Set threshold to detect image as changed
                 *
                 * @param threshold
                 */
                void setPixelChangesThreshold(float threshold) {
                    if (threshold < 0)
                        threshold = 1;

                    if (threshold < 1)
                        threshold *= width * height;

                    _changesThreshold = threshold;
                }

                /**
                 * Set decay for background update
                 *
                 * @param decay
                 */
                void setUpdateSmoothing(float decay) {
                    _decay = decay < 0 ? 0 : (decay > 1 ? 1 : decay);
                }

                /**
                 * Update background modelling
                 *
                 * @tparam Image
                 * @param image
                 */
                template<class Image>
                void update(Image &image) {
                    step([this](Image &image) {
                        this->_numChanges = 0;

                        // detect changes
                        if (_numFrames > 1) {
                            for (uint16_t i = 0, length = width * height; i < length; i++) {
                                int16_t pixel = image.at(i);
                                int16_t diff = pixel - this->_old[i];
                                bool changed = abs(diff) >= this->_intensityThreshold;

                                this->_changes[i] = changed;
                                this->_old[i] = pixel;

                                if (changed)
                                    this->_numChanges += 1;
                            }
                        }

                        // update frame
                    }, image);
                }

                /**
                 * Test if motion was detected
                 *
                 * @return
                 */
                bool isMotionDetected() {
                    return test([this]() {
                        return this->_numChanges >= this->_changesThreshold;
                    });
                }

                /**
                 *
                 * @tparam Stream
                 * @param stream
                 */
                template<class Stream>
                void printAsJson(Stream &stream) {
                    Eloquent::IO::Json::JsonEncoder<Stream> jsonEncoder(stream);

                    jsonEncoder.openObject();
                    jsonEncoder.encode("motion", isMotionDetected());
                    jsonEncoder.then();
                    jsonEncoder.encode("changes", _changes, width * height);
                    jsonEncoder.closeObject();
                }

            protected:
                bool _changes[width * height];
                uint16_t _numChanges;
                uint8_t _old[width * height];
                uint8_t _intensityThreshold;
                uint16_t _changesThreshold;
                float _decay;
            };
        }
    }
}