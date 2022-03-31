#include <ArduinoUnit.h>
#include <EloquentArduino.h>
#include <eloquentarduino/data_structures/Queue.h>


using namespace Eloquent::DataStructures;


test(append_one) {
    float x = 1;
    Queue<5> queue;

    queue.append(x);

    assertEqual(queue.X[0], x);
}

test(append_two) {
    float x1 = 1;
    float x2 = 2;
    Queue<5> queue;

    queue.append(x1);
    queue.append(x2);

    assertEqual(queue.X[0], x1);
    assertEqual(queue.X[1], x2);
}

test(append_overflow) {
    float x1 = 1;
    float x2 = 2;
    float x3 = 3;

    Queue<2> queue;

    queue.append(x1);
    queue.append(x2);
    queue.append(x3);

    assertEqual(queue.X[0], x2);
    assertEqual(queue.X[1], x3);
}


void setup() {
    Serial.begin(115200);
}


void loop() {
    Test::run();
}