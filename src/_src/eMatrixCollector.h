#pragma once


namespace Eloquent {

    template<int rows, int axes>
    class MatrixCollector {
    public:
        MatrixCollector() {
            smoothing = 0;
            batchRows = 0;
            batchIndex = 0;
            collectorIndex = 0;
        }

        void setBatchSize(uint8_t batchRows) {
            this->batchRows = batchRows;
        }
        
        void setSmoothing(float smoothing) {
            this->smoothing = smoothing;
        }

        /**
         *
         * @return
         */
        bool begin() {
            return true;
        }

        float* push(float *row) {
            uint8_t cIndex = collectorIndex % rows;

            // accumulate to collector
            if (batchIndex == 0) {
                for (uint8_t ax = 0; ax < axes; ax++)
                    buffer[cIndex][ax] = row[ax];
            }
            else {
                for (uint8_t ax = 0; ax < axes; ax++)
                    buffer[cIndex][ax] = buffer[cIndex][ax] * (1 - smoothing) + row[ax] * smoothing;
            }

            batchIndex += 1;

            // on buffer full, take action
            if (batchIndex == batchRows) {
                batchIndex = 0;
                collectorIndex += 1;

                return buffer[cIndex];
            }

            return NULL;
        }

        void linearizeTo(float *linearizeBuffer) {
            for (int i = 0; i < rows; i++) {
                for (int ax = 0; ax < axes; ax++) {
                    linearizeBuffer[i * axes + ax] = buffer[(collectorIndex + i) % rows][ax];
                }
            }
        }

        /**
         * Get how many rows filled up after $rows
         * @return
         */
        uint8_t overflowed() {
            return collectorIndex > rows ? collectorIndex - rows : 0;
        }

    protected:
        uint8_t batchRows;
        uint8_t batchIndex;
        uint8_t collectorIndex;
        float smoothing;
        float buffer[rows][axes];
    };
}