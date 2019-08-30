#pragma once

namespace Eloquent {

    typedef int StateID;

    class State {
    public:
        /**
         * Get state ID
         * @return
         */
        virtual StateID id() = 0;

        /**
         * Do something while in this state
         * @return
         */
        virtual StateID run() = 0;

        /**
         * Do something when you first enter this state
         */
        virtual void enter() {

        }

        /**
         * Do something when you leave this state
         */
        virtual void leave() {

        }
    };

    class OOFSM {
    public:
        OOFSM(State* states[], uint8_t numStates) {
            _count = numStates;
            _states = states;
            _current = states[0];
        }

        void loop() {
            StateID nextID;

//            Serial.print("$state: ");
//            Serial.println(_current == NULL ? 0 : _current->id());

            if (_current != NULL)
                nextID = _current->run();

            if (nextID) {
                for (uint8_t i = 0; i < _count; i++) {
                    if (_states[i]->id() == nextID) {
                        _current->leave();
                        _current = _states[i];
                        _current->enter();
                        break;
                    }
                }
            }
        }

    protected:
        uint8_t _count;
        State *_current;
        State **_states;
    };
}


#define StateHandler(state) int __stateHandler__##state(StateContext* context = 0)