#include <ArduinoUnit.h>
#include <eDataStructures.h>


using namespace Eloquent::DataStructures;


/**
 * The Array class needs 2 template arguments:
 *  1. value datatype
 *  2. max number of entries
 */

test(subscript_set) {
        Array<int, 10> array(0);

        array[0] = 10;
        array[1] = 20;

        assertEqual(array[0], 10);
        assertEqual(array[1], 20);
}

test(push_int) {
    Array<int, 10> array(0);

    array.push(10);
    array.push(20);

    assertEqual(array[0], 10);
    assertEqual(array[1], 20);
    // if the key doesn't exists, 0 is returned
    assertEqual(array[2], 0);
}

test(push_string) {
    Array<String, 10> array("");

    array.push("abc");
    array.push("Hello world");

    assertTrue(array[0].equals("abc"));
    assertTrue(array[1].equals("Hello world"));
    assertTrue(array[2].equals(""));
}

test(prevents_overflow) {
    Array<int, 2> array(0);

    array.push(10);
    array.push(20);
    // this will be ignored
    array.push(30);

    assertEqual(array[0], 10);
    assertEqual(array[1], 20);
    // if you push when the max number of entries
    // has been reached, it is ignored
    assertEqual(array.length(), 2);
}

test(index_of) {
    Array<int, 2> array(0);

    array[0] = 10;
    array[1] = 20;

    assertEqual(array.indexOf(10), 0);
    assertEqual(array.indexOf(20), 1);
    assertEqual(array.indexOf(30), sqrt(-1));
}

test(get_min) {
    Array<int, 5> array(0);

    array[0] = 20;
    array[1] = 30;
    array[2] = 40;
    array[3] = 50;
    array[4] = 10;

    assertEqual(array.getMin(), 10);
}

test(get_max) {
    Array<int, 5> array(0);

    array[0] = 20;
    array[1] = 30;
    array[2] = 40;
    array[3] = 50;
    array[4] = 10;

    assertEqual(array.getMax(), 50);
}

test(get_sum) {
    Array<int, 5> array(0);

    array[0] = 10;
    array[1] = 20;
    array[2] = 30;
    array[3] = 40;
    array[4] = 50;

    assertEqual(array.getSum(), 150);
}

test(get_argmin) {
    Array<int, 5> array(0);

    array[0] = 20;
    array[1] = 30;
    array[2] = 40;
    array[3] = 50;
    array[4] = 10;

    assertEqual(array.argmin(), 4);
}

test(get_argmax) {
    Array<int, 5> array(0);

    array[0] = 20;
    array[1] = 30;
    array[2] = 40;
    array[3] = 50;
    array[4] = 10;

    assertEqual(array.argmax(), 3);
}


void setup() {
    Serial.begin(115200);
}


void loop() {
    Test::run();
}