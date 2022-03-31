#pragma once

#include "Voting.h"


namespace Eloquent {
    namespace DataStructures {
        /**
         * Output a robust value based on the combination of two cascading voting
         * @tparam votes
         */
        template<uint8_t shortTermVotes, uint8_t longTermVotes>
        class LongShortTermVoting {
        public:
            
            /**
             * 
             * @param shortQuorum 
             * @param longQuorum
             */
            LongShortTermVoting(float shortQuorum, float longQuorum) :
                _shortQuorum(shortQuorum),
                _longQuorum(longQuorum) {
                
            }
                

            /**
             * Reset state
             */
            void clear() {
                _shortTerm.clear();
                _shortTerm.clear();
            }

            /**
             * Add vote to voting system
             */
            void vote(uint8_t vote) {
                _shortTerm.vote(vote);
                
                // when the short term has an output, vote for the long term
                if (_shortTerm.agree(_shortQuorum)) {
                    _longTerm.vote(_shortTerm.decision());
                }
            }

            /**
             * Test if quorum was achieved
             */
            bool agree() {
                _decision = 255;

                if (_longTerm.agree(_longQuorum) && _longTerm.decision() == _shortTerm.decision()) {
                    _decision = _longTerm.decision();
                    
                    return true;
                }

                return false;
            }

            /**
             * Get robust decision, if any
             */
            uint8_t decision() {
                return _decision;
            }

        protected:
            uint8_t _decision;
            float _shortQuorum;
            float _longQuorum;
            Voting<shortTermVotes> _shortTerm;
            Voting<longTermVotes> _longTerm;
        };
    }
}