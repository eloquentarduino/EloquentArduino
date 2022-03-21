//
// Created by Simone on 17/03/2022.
//

#pragma once

#include "../MonoImage.h"


namespace Eloquent {
    namespace Vision {
        namespace Motion {
            /**
             * Base class for motion detectors
             *
             */
            class AbstractMotionDetector {
            public:
                AbstractMotionDetector() :
                    _updated(false),
                    _motion(false),
                    _numFrames(0),
                    _skipFrames(1),
                    _throttle(0),
                    _motionAt(0) {

                }

                /**
                 * Start detecting motion after the given number of frames
                 *
                 * @param frames
                 */
                void startSinceFrameNumber(uint32_t frames) {
                    _skipFrames = frames > 0 ? frames : 1;
                }

                /**
                 * See throttle
                 *
                 * @param frames
                 */
                void debounceMotionTriggerEvery(uint32_t frames) {
                    throttle(frames);
                }

                /**
                 * Throttle motion triggering to 1 eveny n frames
                 *
                 * @param frames
                 */
                void throttle(uint32_t frames) {
                    startSinceFrameNumber(frames);
                    _throttle = frames;
                }


            protected:
                bool _updated;
                bool _motion;
                uint32_t _motionAt;
                uint32_t _skipFrames;
                uint32_t _numFrames;
                uint32_t _throttle;

                /**
                 * Update frame
                 *
                 * @tparam Image
                 * @param image
                 */
                template<typename Callback, typename Image>
                void step(Callback callback, Image &image) {
                    _updated = true;
                    _numFrames += 1;
                    callback(image);
                }

                /**
                 * Test if motion happened
                 *
                 * @return
                 */
                 template<typename Callback>
                 bool test(Callback callback) {
                    if (_numFrames < _skipFrames + 1)
                        return false;

                    if (!_updated)
                        return _motion;

                    if (_numFrames - _motionAt < _throttle)
                        return false;

                    bool motion = callback();

                    _updated = false;

                    if (motion)
                        _motionAt = _numFrames;

                    return (_motion = motion);
                 }
            };
        }
    }
}