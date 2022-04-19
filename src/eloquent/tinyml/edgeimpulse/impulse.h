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
                 * Constructor
                 * @param debugOn
                 */
                Impulse(bool debugOn = false) :
                    _errorCode(0),
                    _debug(debugOn),
                    _idx(-1),
                    _maxAnomaly(1) {

                }

                /**
                 * Check if everything is ok
                 * @return
                 */
                bool isOk() {
                    return _errorCode == 0;
                }

                /**
                 *
                 * @param features
                 * @return
                 */
                int8_t predict(float *features) {
                    _idx = -1;
                    _errorCode = numpy::signal_from_buffer(features, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &_signal);

                    if (!isOk()) {
                        return error("numpy::signal_from_buffer");
                    }

                    _errorCode = run_classifier(&_signal, &_result, _debug);

                    if (!isOk()) {
                        return error("run_classifier");
                    }

#if EI_CLASSIFIER_HAS_ANOMALY == 1
                    if (isAnomaly())
                        return error("anomaly");
#endif

                    // find argmax of scores
                    _idx = 0;
                    float proba = _result.classification[0].value;

                    for (size_t ix = 1; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
                        float p = _result.classification[ix].value;

                        if (p > proba) {
                            _idx = ix;
                            proba = p;
                        }

                        if (proba >= 0.5) {
                            break;
                        }
                    }

                    return _idx;
                }

                /**
                 * Predict class label
                 * @param features
                 * @return
                 */
                String predictLabel(float *features) {
                    return getLabelOf(predict(features));
                }

                /**
                 * Get label of current prediction
                 * @return
                 */
                String getLabel() {
                    return getLabelOf(_idx);
                }

                /**
                 * Get probability of current prediction
                 * @return
                 */
                float getProba() {
                    return getProbaOf(_idx);
                }

                /**
                 * Get label of given class id
                 * @param idx
                 * @return
                 */
                String getLabelOf(int8_t idx) {
                    if (idx < 0)
                        return "";

                    if (idx >= EI_CLASSIFIER_LABEL_COUNT)
                        return "OUT OF RANGE";

                    return _result.classification[idx].label;
                }

                /**
                 * Get probability of given class id
                 * @param idx
                 * @return
                 */
                float getProbaOf(int8_t idx) {
                    if (idx < 0)
                        return 0;

                    if (idx >= EI_CLASSIFIER_LABEL_COUNT)
                        return 0;

                    return _result.classification[idx].value;
                }

                /**
                 * Get time spent on DSP
                 * @return
                 */
                uint16_t getDspTiming() {
                    return _result.timing.dsp;
                }

                /**
                 * Get time spent on classification
                 * @return
                 */
                uint16_t getClassificationTiming() {
                    return _result.timing.classification;
                }

                /**
                 * Debug classification result to given printer
                 * @tparam Printer
                 * @param printer
                 */
                template<class Printer>
                void printTo(Printer &printer) {
                    printer.print("EdgeImpulse classification results\n");
                    printer.print("----------------------------------\n");
                    printer.print(" > Class scores\n");

                    for (uint8_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
                        printer.print("    > ");
                        printer.print(getLabelOf(i));
                        printer.print(": ");
                        printer.print(getProbaOf(i));
                        printer.print("\n");
                    }

#if EI_CLASSIFIER_HAS_ANOMALY == 1
                    printer.print("    > Anomaly: ");
                    printer.print(getAnomalyScore());
                    printer.print("\n");
#endif

                    printer.print(" > Timing\n");
                    printer.print("    > DSP: ");
                    printer.print(getDspTiming());
                    printer.print(" ms\n");
                    printer.print("    > Classification: ");
                    printer.print(getClassificationTiming());
                    printer.print(" ms\n");

#if EI_CLASSIFIER_HAS_ANOMALY == 1
                    printer.print("    > Anomaly: ");
                    printer.print(getAnomalyTiming());
                    printer.print(" ms\n");
#endif

                    printer.print(" > Error: ");
                    printer.print(isOk() ? "OK" : _errorMessage);
                    printer.print("(");
                    printer.print(_errorCode);
                    printer.print(")\n");
                }

#if EI_CLASSIFIER_HAS_ANOMALY == 1

                    /**
                     * Set max allowed anomaly score
                     */
                    void setMaxAnomalyScore(float score) {
                        _maxAnomaly = score;
                    }

                    /**
                     * Check if current prediction is an anomaly
                     */
                    bool isAnomaly() {
                        return !isOk() || getAnomalyScore() > _maxAnomaly;
                    }

                    /**
                     * Get time spent on anomaly detection
                     * @return
                     */
                    uint16_t getAnomalyTiming() {
                        return _result.timing.anomaly;
                    }

                    /**
                     * Get anomaly score
                     * @return
                     */
                    float getAnomalyScore() {
                        return _result.anomaly;
                    }
#endif

            protected:
                bool _debug;
                int _errorCode;
                float _maxAnomaly;
                String _errorMessage;
                signal_t _signal;
                ei_impulse_result_t _result;
                int8_t _idx;


                /**
                 * Return error
                 * @param errorMessage
                 * @return
                 */
                int8_t error(const char *errorMessage) {
                    _errorMessage = String(errorMessage);

                    return -1;
                }
            };
        }
    }
}