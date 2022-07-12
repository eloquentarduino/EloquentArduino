//
// Created by Simone on 24/05/2022.
//

#pragma once


namespace eloquent {
    namespace math {

        /**
         * Stop condition of variadic min
         * @tparam T
         * @param a
         * @return
         */
        template<typename T>
        T least(T a) {
            return a;
        }

        /**
         * Variadic min
         * @tparam T
         * @tparam Types
         * @param a
         * @param others
         * @return
         */
        template<typename T, typename... Types>
        T least(T a, Types... others) {
            T b = eloquent::math::least(others...);

            return a < b ? a : b;
        }

        /**
         * Stop condition of variadic max
         * @tparam T
         * @param a
         * @return
         */
        template<typename T>
        T greatest(T a) {
            return a;
        }

        /**
         * Variadic max
         * @tparam T
         * @tparam Types
         * @param a
         * @param others
         * @return
         */
        template<typename T, typename... Types>
        T greatest(T a, Types... others) {
            T b = eloquent::math::greatest(others...);

            return a > b ? a : b;
        }

        /**
         * Get min of array
         * @tparam T
         * @param array
         * @param length
         * @return
         */
        template<typename T>
        T arrayMin(T *array, size_t length) {
            T m = array[0];

            for (size_t i = 1; i < length; i++)
                if (array[i] < m)
                    m = array[i];

            return m;
        }

        /**
         * Get max of array
         * @tparam T
         * @param array
         * @param length
         * @return
         */
        template<typename T>
        T arrayMax(T *array, size_t length) {
            T m = array[0];

            for (size_t i = 1; i < length; i++)
                if (array[i] > m)
                    m = array[i];

            return m;
        }

        /**
         * Array reduce
         * @tparam T
         * @tparam U
         * @tparam Callback
         * @param callback
         * @param array
         * @param size
         * @param initialValue
         * @return
         */
        template<typename T, typename U, typename Callback>
        U arrayReduce(Callback callback, T *array, size_t size, U initialValue) {
            for (size_t i = 0; i < size; i++)
                initialValue = callback(initialValue, array[i]);

            return initialValue;
        }

        /**
         * Get mean value of array
         * @tparam T
         * @param array
         * @param size
         * @return
         */
        template<typename T>
        float arrayMean(T *array, size_t size) {
            if (size == 0)
                return 0;

            return eloquent::math::arrayReduce([](float sum, T x) {
                return sum + x;
            }, array, size, 0) / size;
        }


        /**
         * Get count of items passing the given filter
         * @tparam T
         * @tparam Filter
         * @param array
         * @param length
         * @param filter
         * @return
         */
        template<typename T, typename Filter>
        size_t arrayCountWhere(T *array, size_t length, Filter filter) {
            size_t count = 0;

            for (size_t i = 0; i < length; i++)
                if (filter(array[i]))
                    count += 1;

            return count;
        }

        /**
         * Constrain value into given range
         * @tparam T
         * @param x
         * @param low
         * @param high
         * @return
         */
         template<typename T>
        T constrainRange(T x, float low, float high) {
            if (low == high)
                return x;

            return x < low ? low : (x > high ? high : x);
        }

        /**
         * Map value from given range to new range
         * @param x
         * @param l
         * @param h
         * @param m
         * @param M
         * @return
         */
        float map(float x, float l, float h, float m, float M) {
            if (l == h || m == M)
                return x;

            return (x - l) / (h - l) * (M - m) + m;
        }

        /**
         * Constrain + map
         * @param x
         * @param l
         * @param h
         * @param m
         * @param M
         * @return
         */
        float mapConstrain(float x, float l, float h, float m, float M) {
            return eloquent::math::map(eloquent::math::constrainRange(x, l, h), l, h, m, M);
        }

        /**
         * Convert byte to hex string
         * @param b
         * @param str
         */
        void byteToHex(uint8_t b, char *str) {
            const char alphabet[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

            str[0] = alphabet[b >> 4];
            str[1] = alphabet[b & 0b1111];
            str[2] = '\0';
        }
    }
}