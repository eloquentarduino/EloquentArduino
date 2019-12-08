#include <ArduinoUnit.h>
#include <eDataStructures.h>


using namespace Eloquent::DataStructures;


test(exists) {
        HashMap<int, int, 10> hashmap;

        hashmap.put(0, 10);
        hashmap.put(1, 20);

        assertTrue(hashmap.exists(0));
        assertTrue(hashmap.exists(1));
        assertFalse(hashmap.exists(2));
}


test(get) {
        HashMap<int, int, 10> hashmap;

        hashmap.put(0, 10);
        hashmap.put(1, 20);

        assertEqual(hashmap.get(0), 10);
        assertEqual(hashmap.get(1), 20);
        assertEqual(hashmap.get(2), 0);
}

test(get_string) {
        HashMap<String, int, 10> hashmap;

        hashmap.put("abc", 10);
        hashmap.put("xyz", 20);

        assertEqual(hashmap.get("abc"), 10);
        assertEqual(hashmap.get("xyz"), 20);
        assertEqual(hashmap.get("foo"), 0);
}


test(prevents_overflow) {
        HashMap<int, int, 2> hashmap;

        hashmap.put(0, 10);
        hashmap.put(1, 20);
        hashmap.put(2, 30);

        assertEqual(hashmap.get(0), 10);
        assertEqual(hashmap.get(1), 20);
        assertFalse(hashmap.exists(2));
}


void setup() {
    Serial.begin(115200);
}


void loop() {
    Test::run();
}