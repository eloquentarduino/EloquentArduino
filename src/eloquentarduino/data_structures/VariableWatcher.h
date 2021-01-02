#pragma once


namespace eloquent {
    namespace data {

        template<typename T>
        class VariableWatcher {
        public:

            /**
             * Update current value
             * @param current
             */
            void update(T current) {
                _old = _current;
                _current = current;
            }

            /**
             * Test if value changed
             * @return
             */
            bool changed() {
                return _current != _old;
            }

        protected:
            T _old;
            T _current;
        };
    }
}