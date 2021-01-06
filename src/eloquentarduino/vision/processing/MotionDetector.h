#pragma once


namespace Eloquent {
    namespace Vision {
        namespace Processing {

            /**
             * Eloquent API to detect motion in a stream of images
             *
             * @tparam sourceWidth width of the source image
             * @tparam sourceHeight height of the source image
             */
            template<uint16_t sourceWidth, uint16_t sourceHeight>
            class MotionDetector {
            public:
                /**
                 *
                 * @param smooth transition smoothing factor
                 * @param diffThreshold how much a pixel's value should change to be detected as different
                 * @param motionThreshold how many pixels (in percent) should change to be detected as motion
                 */
                MotionDetector(float smooth = 0.25, float diffThreshold = 0.2, float motionThreshold = 0.2) {

                    _isFirst = true;

                    setSmoothing(smooth);
                    setDiffThreshold(diffThreshold);
                    setMotionThreshold(motionThreshold);
                    setDebounceFrames(0);

                    for (uint16_t i = 0; i < pixels(); i++) {
                        _curr[i] = 0;
                        _prev[i] = 0;
                    }
                }

                /**
                 * Get number of pixels
                 * @return
                 */
                inline const uint16_t pixels() {
                    return sourceWidth * sourceHeight;
                }

                /**
                 * Push new frame into the detector
                 * @param image
                 */
                void update(uint8_t *image) {
                    if (_debouncing > 0)
                        _debouncing -= 1;

                    for (uint16_t i = 0; i < pixels(); i++) {
                        _prev[i] = _smoothCurr * _curr[i] + _smoothPrev * _prev[i];
                        _curr[i] = image[i];
                    }
                }

                /**
                 * Update pixel diff threshold value
                 * @param threshold if in range [0, 1[, it is considered as relative, else absolute
                 * @deprecated
                 */
                void setDiffThreshold(float threshold) {
                    _diffThreshold = threshold;
                }

                /**
                 * Update motion threshold value
                 * @param threshold
                 * @deprecated
                 */
                void setMotionThreshold(float threshold) {
                    _motionThreshold = threshold;
                }

                /**
                 * Set frame transition smoothing factor
                 * (set to 0 for no smoothing)
                 * @param smooth in the range [0, 1[
                 */
                void setSmoothing(float smooth) {
                    smooth = constrain(smooth, 0, 1);
                    _smoothPrev = smooth;
                    _smoothCurr = 1 - smooth;
                }

                /**
                 * Triggers will be disabled for the given consecutive frames
                 * after a motion event
                 * @param frames
                 */
                void setDebounceFrames(uint8_t frames) {
                    _debounce = frames;
                    _debouncing = 0;
                }

                /**
                 * Detect how many pixels changed by at least a given threshold
                 * @param image
                 * @return
                 */
                uint16_t detect(uint8_t *image = NULL) {
                    _changes = 0;

                    if (image != NULL)
                        update(image);

                    // relative threshold
                    if (_diffThreshold < 1) {
                        for (uint16_t i = 0; i < pixels(); i++) {
                            float current = _curr[i];
                            float prev = _prev[i];
                            float delta = ((float) abs(current - prev)) / (prev != 0 ? prev : 1);

                            if (delta >= _diffThreshold)
                                _changes += 1;
                        }
                    } else {
                        // absolute threshold
                        for (uint16_t i = 0; i < pixels(); i++) {
                            float current = _curr[i];
                            float prev = _prev[i];
                            float delta = abs(current - prev);

                            if (delta >= _diffThreshold)
                                _changes += 1;
                        }
                    }

                    if (_isFirst) {
                        _isFirst = false;

                        return 0;
                    }

                    return _changes;
                }

                /**
                 * Get number of pixels that changed
                 * @return
                 */
                inline uint16_t changes() {
                    return _changes;
                }

                /**
                 * Get the ratio of pixels that changed in the last frame
                 * @return
                 */
                inline float ratio() {
                    return ((float) _changes) / pixels();
                }

                /**
                 * Test if motion happened based on the config
                 * @return
                 */
                bool triggered() {
                    // absolute threshold
                    bool triggered = changes() >= _motionThreshold;

                    // apply debouncing
                    if (_debouncing > 0)
                        return false;

                    // relative threshold
                    if (_motionThreshold < 1) {
                        triggered = ratio() >= _motionThreshold;
                    }

                    // reset debounce on motion
                    if (triggered) {
                        _debouncing = _debounce;
                    }

                    return triggered;
                }


            protected:
                uint8_t _curr[sourceWidth * sourceHeight];
                uint8_t _prev[sourceWidth * sourceHeight];
                float _smoothCurr;
                float _smoothPrev;
                float _diffThreshold;
                float _motionThreshold;
                uint8_t _debounce;
                uint8_t _debouncing;
                uint8_t _changes;
                bool _isFirst;
            };
        }
    }
}