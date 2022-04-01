//
// Created by Simone on 17/03/2022.
//

#pragma once

#include "../image/BaseImage.h"


namespace Eloquent {
    namespace Vision {
        namespace Motion {
            /**
             * Base class for motion detectors
             *
             */
            class BaseMotionDetector {
            public:
                BaseMotionDetector() :
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
                    _throttle = frames;
                }

                /**
                 * Throttle motion triggering to 1 eveny n frames
                 * @param frames
                 */
                void throttle(uint32_t frames) {
                    startSinceFrameNumber(frames);
                    debounceMotionTriggerEvery(frames);
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
                 * Test if motion happened
                 * @return 
                 */
                bool isMotionDetected() {
                    if (_numFrames < _skipFrames + 1)
                        return false;

                    if (_numFrames - _motionAt < _throttle)
                        return false;

                    if (!_updated)
                        return _motion;

                    _updated = false;

                    bool motion = detectMotion();

                    if (motion)
                        _motionAt = _numFrames;

                    return (_motion = motion);
                }


            protected:
                bool _updated;
                bool _motion;
                uint32_t _motionAt;
                uint32_t _skipFrames;
                uint32_t _numFrames;
                uint32_t _throttle;

                /**
                 * Test if motion is detected
                 * @return
                 */
                 virtual bool detectMotion() = 0;

                 /**
                  *
                  * @tparam Image
                  * @tparam OnSetup
                  * @tparam OnUpdate
                  * @param image
                  * @param onSetup
                  * @param onUpdate
                  */
                template<class Image, typename OnSetup, typename OnUpdate>
                 void step(Image &image, OnSetup onSetup, OnUpdate onUpdate) {
                     _numFrames == 0 ? onSetup(image) : onUpdate(image);
                     _numFrames += 1;
                     _updated = true;
                 }
            };
        }
    }
}