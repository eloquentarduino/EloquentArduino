#include <ArduinoUnit.h>
#include <EloquentArduino.h>
#include <eloquentarduino/data_structures/NdQueue.h>


using namespace Eloquent::DataStructures;


test(append_one) {
    float x[] = {1, 2, 3, 4, 5};
    NdQueue<5, 1> queue;

    queue.append(x);

    assertEqual(queue.X[0], 1);
    assertEqual(queue.X[1], 2);
    assertEqual(queue.X[2], 3);
    assertEqual(queue.X[3], 4);
    assertEqual(queue.X[4], 5);
}

test(append_two) {
        float x1[] = {1, 2, 3, 4, 5};
        float x2[] = {6, 7, 8, 9, 0};
        NdQueue<5, 2> queue;

        queue.append(x1);
        queue.append(x2);

        assertEqual(queue.X[5], 6);
        assertEqual(queue.X[6], 7);
        assertEqual(queue.X[7], 8);
        assertEqual(queue.X[8], 9);
        assertEqual(queue.X[9], 0);
}

test(append_overflow) {
        float x1[] = {1, 2, 3, 4, 5};
        float x2[] = {6, 7, 8, 9, 0};
        NdQueue<5, 1> queue;

        queue.append(x1);
        queue.append(x2);

        assertEqual(queue.X[0], 6);
        assertEqual(queue.X[1], 7);
        assertEqual(queue.X[2], 8);
        assertEqual(queue.X[3], 9);
        assertEqual(queue.X[4], 0);
}

test(append_linearize) {
        float x1[] = {1, 2, 3, 4, 5};
        float x2[] = {6, 7, 8, 9, 0};
        float x3[] = {11, 12, 13, 14, 15};
        NdQueue<5, 2> queue;

        queue.append(x1);
        queue.append(x2);
        queue.append(x3);

        assertEqual(queue.X[0], 6);
        assertEqual(queue.X[1], 7);
        assertEqual(queue.X[2], 8);
        assertEqual(queue.X[3], 9);
        assertEqual(queue.X[4], 0);
        assertEqual(queue.X[5], 11);
        assertEqual(queue.X[6], 12);
        assertEqual(queue.X[7], 13);
        assertEqual(queue.X[8], 14);
        assertEqual(queue.X[9], 15);
}


void setup() {
    Serial.begin(115200);
}


void loop() {
    Test::run();
}