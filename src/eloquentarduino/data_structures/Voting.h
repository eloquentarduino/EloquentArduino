#pragma once


namespace Eloquent {
    namespace DataStructures {
        /**
         * Output a robust value when a given number of votes agree
         * @tparam votes
         * @tparam quorum
         */
        template<uint8_t votes, uint8_t quorum>
        class MajorityVoting {
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
             */
            bool hasMajority() {
                _decision = 255;

                if (_idx < votes)
                    return false;

                bool majority = false;

                for (uint8_t i = 0; i < votes - quorum; i++) {
                    uint8_t vote = _votes[i];
                    uint8_t count = 1;

                    for (uint8_t j = i + 1; j < votes; j++)
                        if (_votes[j] == vote)
                            count += 1;

                    if (count >= quorum) {
                        _decision = vote;
                        majority = true;
                        break;
                    }
                }

                return majority;
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