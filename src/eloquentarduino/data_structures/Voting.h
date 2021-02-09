#pragma once


namespace Eloquent {
    namespace DataStructures {
        /**
         * Output a robust value when a given number of votes agree
         * @tparam votes
         */
        template<uint8_t votes>
        class Voting {
        public:

            /**
             * Reset state
             */
            void clear() {
                _idx = 0;

                for (uint8_t i = 0; i < votes; i++)
                    _votes[i] = 0;
            }

            /**
             * Add vote to voting system
             */
            void vote(uint8_t vote) {
                _votes[_idx % votes] = vote;
                _idx += 1;
            }

            /**
             * Test if quorum was achieved
             * @param quorum how many votes should agree (if < 1, it is considered as a percent)
             * @param row how many votes "in row" should agree
             */
            bool agree(float quorum, uint8_t row = 0) {
                _decision = 255;

                if (_idx < votes)
                    return false;

                if (quorum < 0)
                    return false;

                if (quorum < 1)
                    quorum *= votes;

                bool agree = false;

                for (uint8_t i = 0; i < votes - quorum; i++) {
                    uint8_t vote = _votes[i];
                    uint8_t count = 1;

                    for (uint8_t j = i + 1; j < votes; j++)
                        if (_votes[j] == vote)
                            count += 1;

                    if (count >= quorum) {
                        _decision = vote;
                        agree = true;
                        break;
                    }
                }

                // check votes "in row"
                if (row > 0) {
                    for (uint8_t i = votes - row; i < votes; i++) {
                        if (_votes[i] != _decision) {
                            _decision = 255;
                            agree = false;
                            break;
                        }
                    }
                }

                return agree;
            }

            /**
             * Get robust decision, if any
             */
            uint8_t decision() {
                return _decision;
            }

        protected:
            uint8_t _votes[votes] = {0};
            uint8_t _idx = 0;
            uint8_t _decision;
        };
    }
}