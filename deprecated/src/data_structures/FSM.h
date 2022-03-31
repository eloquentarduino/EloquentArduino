#pragma once

#include <Arduino.h>

namespace Eloquent {
    namespace DataStructures {

        /**
         *
         */
        class State {
        public:
            /**
             * What to do in this state
             * @return
             */
            virtual int stay() = 0;

            /**
             * What to do when entering this state
             */
            virtual void enter() {

            }

            /**
             * What to do when leaving this state
             */
            virtual void leave() {

            }
        };

        /**
         *
         */
        class Transition {
        public:
            Transition(State *from, int trigger, State *to) {
                this->from = from;
                this->to = to;
                this->trigger = trigger;
            }

            /**
             * Append transition next in the chain
             * @param next
             */
            void chain(Transition *next) {
                if (this->next == 0)
                    this->next = next;
                else
                    this->next->chain(next);
            }

            /**
             * Get matching transition, if any
             * @param from
             * @param trigger
             * @return
             */
            Transition* match(State *from, int trigger) {
                if (this->from == from && this->trigger == trigger)
                    return this;

                if (next == 0)
                    return 0;

                return next->match(from, trigger);
            }

            State* getTo() {
                return to;
            }

        protected:
            int trigger;
            State *from, *to;
            Transition *next;
        };


        /**
         *
         */
        class FSM {
        public:
            FSM(State& start) {
                current = &start;
                transition = 0;
            }

            /**
             * Add transition
             * @param from
             * @param trigger
             * @param to
             */
            void add(State& from, int trigger, State& to) {
                Transition *transition = new Transition(&from, trigger, &to);

                if (this->transition == 0)
                    this->transition = transition;
                else
                    this->transition->chain(transition);
            }

            /**
             * Run FSM
             */
            void loop() {
                int trigger = current->stay();

                Serial.print("trigger = ");
                Serial.println(trigger);

                // no transition is necessary
                if (trigger == 0) {
                    Serial.println("trigger = 0");
                    return;
                }

                // no transition has been registered
                if (transition == 0) {
                    Serial.println("transition = 0");

                    return;
                }

                Transition *next = transition->match(current, trigger);

                // no matching transition found
                if (next == 0) {
                    Serial.println("next = 0");

                    return;
                }

                // do transition
                current->leave();
                current = next->getTo();
                current->enter();
            }

        protected:
            State *current;
            Transition *transition;
        };
    }
}