//
// Created by Simone on 01/04/2022.
//

#pragma once

#include "./BaseMotionDetector.h"
#include "../../io/json/JsonEncoder.h"


using Eloquent::IO::Json::JsonEncoder;


namespace Eloquent {
    namespace Vision {
        namespace Motion {
            /**
             * Naive motion detection
             * @tparam width
             * @tparam height
             */
            template<uint16_t width, uint16_t height>
            class Naive : public BaseMotionDetector {
            public:

                /**
                 * Constructor
                 */
                Naive() :
                        BaseMotionDetector(),
                        _intensityThreshold(10),
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
                 * Update background model
                 * @tparam Image
                 * @param image
                 */
                template<class Image>
                void update(Image &image) {
                    step(
                        image,
                        [this](Image &image) { this->setupBackgroundModel(image); },
                        [this](Image &image) { this->updateBackgroundModel(image); }
                    );
                }

                /**
                 * Update background model and detect motion
                 * @tparam Image
                 * @param image
                 * @return
                 */
                template<class Image>
                bool updateAndDetect(Image &image) {
                    update(image);

                    return isMotionDetected();
                }

                /**
                 * Print as Json
                 * @tparam Printer
                 * @param printer
                 */
                template<class Printer>
                void printAsJsonTo(Printer &printer) {
                    JsonEncoder<Printer> jsonEncoder(printer);

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

                /**
                 * Setup background model
                 * @tparam Image
                 * @param image
                 */
                template<class Image>
                void setupBackgroundModel(Image &image) {
                    for (uint16_t i = 0, length = image.getWidth() * image.getHeight(); i < length; i++) {
                        this->_old[i] = image.at(i);
                    }
                }

                /**
                 * Update background model
                 * @tparam Image
                 * @param image
                 */
                template<class Image>
                void updateBackgroundModel(Image &image) {
                    this->_numChanges = 0;

                    for (uint16_t i = 0, length = image.getWidth() * image.getHeight(); i < length; i++) {
                        int16_t pixel = image.at(i);
                        int16_t diff = pixel - this->_old[i];
                        bool changed = abs(diff) >= this->_intensityThreshold;

                        this->_changes[i] = changed;
                        this->_old[i] = _decay == 1 ? pixel : _decay * pixel + (1 - _decay) * this->_old[i];

                        if (changed)
                            this->_numChanges += 1;
                    }
                }

                /**
                 * Test if motion is detected
                 * @return
                 */
                bool detectMotion() {
                    return this->_numChanges >= this->_changesThreshold;
                }
            };
        }
    }
}