//
// Created by Simone on 27/05/2022.
//

#pragma once


namespace Eloquent {
    namespace TinyML {
        namespace Voting {
            /**
             * Create a voting mechanism that outputs a "strong" prediction
             * when N out of M votes are the same
             */
             template<uint16_t votes>
            class Quorum {
            public:

                /**
                 * Constructor
                 */
                Quorum() : _vote(-1) {
                    clear();
                    atLeastMajority();
                }

                /**
                 * Reset voting
                 */
                void clear() {
                    _i = 0;

                    for (int i = 0; i < votes; i++)
                        _votes[i] = -1;
                }

                /**
                 * Emit a "strong" prediction when at least 50% of votes are the same
                 */
                void atLeastMajority() {
                    atLeast(ceil(votes / 2));
                }

                /**
                 * Emit a "strong" prediction when at least the given number of votes are the same
                 * @param quorum
                 */
                void atLeast(uint16_t quorum) {
                    _quorum = quorum;
                }

                /**
                 * Add vote
                 * @param vote
                 * @return
                 */
                int8_t vote(uint8_t vote) {
                    uint16_t quorum = _quorum;

                    _votes[_i] = vote;
                    _i = (_i + 1) % votes;

                    for (int i = 0; i < votes; i++) {
                        if (_votes[i] == vote) {
                            quorum -= 1;

                            if (quorum == 0)
                                return (_vote = vote);
                        }
                    }

                    return (_vote = -1);
                }

                /**
                 * Test if last vote was stable
                 * @return
                 */
                bool isStable() {
                    return _vote >= 0;
                }

            protected:
                int8_t _votes[votes];
                uint16_t _i;
                uint16_t _quorum;
                int8_t _vote;
            };
        }
    }
}